`include "defines.vh"
module timer_unit #(
        parameter    DATA_WIDTH = 8
    )(
        input  wire                  clk,        // input clock
        input  wire                  reset,      // reset signal
        input  wire [DATA_WIDTH-1:0] mem_ocr0a,  // OCR0A / OCR0B (Output Compare Register 0, channel A/B)
        input  wire [DATA_WIDTH-1:0] mem_ocr0b,  // OCR0A / OCR0B (Output Compare Register 0, channel A/B)
        input  wire [DATA_WIDTH-1:0] mem_tcnt0,  // value from memory of counter for timer 0 (8 bits)
        input  wire [DATA_WIDTH-1:0] mem_tccr0a, // TCCR0A, TCCR0B (Timer/Counter Control Registers A and B)
        input  wire [DATA_WIDTH-1:0] mem_tccr0b, // TCCR0A, TCCR0B (Timer/Counter Control Registers A and B)
        output reg  [DATA_WIDTH-1:0] tcnt0,      // next value of counter
        output reg                   oc0a,       // output pin channel A
        output reg                   oc0b        // output pin channel B
    );

    // Signals used for prescaling
    wire    clk_t;
    wire    clk_io,      // original clk signal
            clk_io_8,    // clk prescaled with 8    (8   times slower)
            clk_io_64,   // clk prescaled with 64   (64  times slower)
            clk_io_256,  // clk prescaled with 256  (256 times slower)
            clk_io_1024; // clk prescaled with 1024 (1024 times slower)

    wire     [7:0] clk_sources;  // array of clk signals
    reg     [13:0] count;        // helper for prescaler

    always @(posedge clk, posedge reset) begin
        if (reset)
            count <= 0;
        else
            count <= count + 1;
    end

    // TODO 1: Generate prescaled clock sources
    // HINT: Which bit of count is changed every 2^X clk posedges?
    assign clk_io           = clk;
    assign clk_io_8         = count[2]; // clk / 2^3
    assign clk_io_64        = count[5]; // clk / 2^6
    assign clk_io_256       = count[7]; // clk / 2^8
    assign clk_io_1024      = count[9]; // clk / 2^10

    // TODO 1: Fill in array of available clock sources
    // HINT: This array corresponds to table 11-9, page 73, from the datasheet.
    // Remember that the array is defined [7:0], so the first item is actually
    // clk_sources[7].
    assign clk_sources = {
        1'b0, // cs0 == 7 - We don't support this options, so don't change this
        1'b0, // cs0 == 6 - We don't support this options, so don't change this
        clk_io_1024,    // cs0 == 5 - clkI/O / 1024   (From prescaler)
        clk_io_256,    // cs0 == 4 - clkI/O / 256    (From prescaler)
        clk_io_64,    // cs0 == 3 - clkI/O / 64     (From prescaler)
        clk_io_8,    // cs0 == 2 - clkI/O / 8      (From prescaler)
        clk_io,    // cs0 == 1 - clkI/O          (No prescaling)
        0     // cs0 == 0 - No clock source (Timer/Counter stopped)
        };

    // TODO 1: Select the clock source to be used.
    // HINT: Use the array of available clock signals and cs0
    assign clk_t = clk_sources[cs0];

    // Bits in configuration register
    wire            [1:0] com0a; // COM0A[1:0]: Compare Match Output A Mode
    wire            [1:0] com0b; // COM0B[1:0]: Compare Match Output B Mode
    wire            [2:0] wgm0;  // WGM0 [2:0]: Waveform Generation Mode
    wire            [2:0] cs0;   // CS0[2:0]: Clock Select

    // TODO 2: Extract bits from TCCRA0A and TCCR0B.
    // HINT: Use mem_tccr0a and mem_tccr0b
    assign com0a =  mem_tccr0a[7:6];   // datasheet pages: 69
    assign com0b =  mem_tccr0a[5:4];   // datasheet pages: 69
    assign wgm0  =  {mem_tccr0b[3], mem_tccr0a[1:0]};   // datasheet pages: 69, 72
    assign cs0   =  mem_tccr0b[2:0];   // datasheet pages: 72

    wire [5:0]             timer_mode;  // Timer operation mode
    wire [DATA_WIDTH-1:0]  top;         // Value at which counter resets

    // TODO 2: Set timer operation mode
    // HINT: See datasheet page 72 (Table 11-8. Waveform Generation Mode Bit Description)
    assign timer_mode =
        // (who == what) ? `NORMAL :
        // (who == what) ? `CTC :
        // (who == what) ? `FAST_PWM_MAX :
        // (who == what) ? `FAST_PWM_OCR :
		  (wgm0 == 0) ? `NORMAL :
		  (wgm0 == 2) ? `CTC :
		  (wgm0 == 3) ? `FAST_PWM_MAX :
		  (wgm0 == 7) ? `FAST_PWM_OCR :
        `INVALID;

    // TODO 2: Set value at which counter resets
    // HINT: See datasheet page 72 (Table 11-8. Waveform Generation Mode Bit Description)
    assign top =
        // (who == `NORMAL) ? what_value :
        // (who == `CTC) ? what_value :
        // (who == `FAST_PWM_MAX) ? what_value :
        // (who == `FAST_PWM_OCR) ? what_value :
		  (timer_mode == `NORMAL) ? 255 :
		  (timer_mode == `CTC) ? mem_ocr0a :
		  (timer_mode == `FAST_PWM_MAX) ? 255 :
		  (timer_mode == `FAST_PWM_OCR) ? mem_ocr0a :
        0;

    // Counter assignment block.
    always @(posedge clk_t, posedge reset) begin
        if (reset) begin
            tcnt0 <= 0;
        end else begin
            // TODO 2: Increment counter
            // HINT: Use mem_tcnt0 to read the current counter value. The value of TCNT0 should always be read from memory, because instructions can also write to it
            // HINT: Place the result into tcnt0
            if (mem_tcnt0 == top) begin
                // tcnt0 <= ? // What should we do if we have reached TOP?
					 tcnt0 <= 0;
            end else begin
                // tcnt0 <= ? // What should we do if we have not reached TOP?
					 tcnt0 <= mem_tcnt0 + 1;
            end
        end
    end

    // Generate PWM logic on output pins OC0A and OC0B.
    always @(posedge clk_t, posedge reset) begin
        if (reset) begin
            oc0a <= 0;
            oc0b <= 0;
        end else begin
            // TODO 3: Change the value of OC0A and OC0B
            // HINT: This depends on the timer operation mode, COM0A, COM0B,
            // the current counter value and the two compare values. See tables
            // 11-2, 11-3, 11-5 and 11-6 from the datasheet (pages 70-71).
            case (timer_mode)
				
					`NORMAL: begin
						case (com0a)
                      /*2'b00: begin
							 
							 default: ; // Do nothing, OC0A disconnected from timer
								
							 
							 end*/
							 
							 2'b01: begin
							 
								 if (mem_tcnt0 == mem_ocr0a) begin
									oc0a <= ~oc0a;
								 end
							 
							 end
							 
							 2'b10: begin
							   if (mem_tcnt0 == mem_ocr0a) begin
									oc0a <= 0;
								end
							 
							 end
							 
							 2'b11: begin
							 
								if (mem_tcnt0 == mem_ocr0a) begin
									oc0a <= 1;
								end
							 
							 end
                  endcase

                  case (com0b)
						
							/*2'b00: begin
							 
							 default: ; // Do nothing, OC0A disconnected from timer
								
							 
							 end*/
							 
							 2'b01: begin
							 
								 if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= ~oc0b;
								 end
							 
							 end
							 
							 2'b10: begin
							   if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= 0;
								end
							 
							 end
							 
							 2'b11: begin
							 
								if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= 1;
								end
							 
							 end
                      
                  endcase	 
					 end
					 
					 `CTC: begin
					 
						case (com0a)
                      /*2'b00: begin
							 
							 default: ; // Do nothing, OC0A disconnected from timer
								
							 
							 end*/
							 
							 2'b01: begin
							 
								 if (mem_tcnt0 == mem_ocr0a) begin
									oc0a <= ~oc0a;
								 end
							 
							 end
							 
							 2'b10: begin
							   if (mem_tcnt0 == mem_ocr0a) begin
									oc0a <= 0;
								end
							 
							 end
							 
							 2'b11: begin
							 
								if (mem_tcnt0 == mem_ocr0a) begin
									oc0a <= 1;
								end
							 
							 end
                  endcase

                  case (com0b)
						
							/*2'b00: begin
							 
							 default: ; // Do nothing, OC0A disconnected from timer
								
							 
							 end*/
							 
							 2'b01: begin
							 
								 if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= ~oc0b;
								 end
							 
							 end
							 
							 2'b10: begin
							   if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= 0;
								end
							 
							 end
							 
							 2'b11: begin
							 
								if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= 1;
								end
							 
							 end
                      
                  endcase
						 
					 end
					 
					 `FAST_PWM_MAX: begin
					 
						case (com0a)
                      /*2'b00: begin
							 
							 default: ; // Do nothing, OC0A disconnected from timer
								
							 
							 end*/
							 
							 2'b01: begin
							 
								 /*if (wgm0[2] == 0) begin
									//default: ; // Do nothing, OC0A disconnected from timer
								 
								 end*/
								 
								 if (wgm0[2] == 1) begin
									oc0a <= ~oc0a;
								 
								 end
							 
							 end
							 
							 2'b10: begin
							   if (mem_tcnt0 == mem_ocr0a) begin
									oc0a <= 0;
								end
								
								if (mem_tcnt0 == 1) begin
									oc0a <= 1;
								end
								
								
							 
							 end
							 
							 2'b11: begin
							 
								if (mem_tcnt0 == mem_ocr0a) begin
									oc0a <= 1;
								end
								
								if (mem_tcnt0 == 1) begin
									oc0a <= 0;
								end
								
							 end
                  endcase

                  case (com0b)
						
							/*2'b00: begin
							 
							 default: ; // Do nothing, OC0A disconnected from timer
								
							 
							 end*/
							 
							 /*2'b01: begin
							 
								 
							 
							 end*/
							 
							 2'b10: begin
							   if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= 0;
								end
								
								if (mem_tcnt0 == 1) begin
									oc0b <= 1;
								end
								
							 end
							 
							 2'b11: begin
							 
								if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= 1;
								end
								
								if (mem_tcnt0 == 1) begin
									oc0b <= 0;
								end
							 
							 end
                      
                  endcase	
						 
					 end
					 
					 `FAST_PWM_OCR: begin
					 
						case (com0a)
                      /*2'b00: begin
							 
							 default: ; // Do nothing, OC0A disconnected from timer
								
							 
							 end*/
							 
							 2'b01: begin
							 
								 /*if (wgm0[2] == 0) begin
									//default: ; // Do nothing, OC0A disconnected from timer
								 
								 end*/
								 
								 if (wgm0[2] == 1) begin
									oc0a <= ~oc0a;
								 
								 end
							 
							 end
							 
							 2'b10: begin
							   if (mem_tcnt0 == mem_ocr0a) begin
									oc0a <= 0;
								end
								
								if (mem_tcnt0 == 1) begin
									oc0a <= 1;
								end
								
								
							 
							 end
							 
							 2'b11: begin
							 
								if (mem_tcnt0 == mem_ocr0a) begin
									oc0a <= 1;
								end
								
								if (mem_tcnt0 == 1) begin
									oc0a <= 0;
								end
								
							 end
                  endcase

                  case (com0b)
						
							/*2'b00: begin
							 
							 default: ; // Do nothing, OC0A disconnected from timer
								
							 
							 end*/
							 
							 /*2'b01: begin
							 
								 if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= ~oc0b;
								 end
							 
							 end*/
							 
							 2'b10: begin
							   if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= 0;
								end
								
								if (mem_tcnt0 == 1) begin
									oc0b <= 1;
								end
								
							 end
							 
							 2'b11: begin
							 
								if (mem_tcnt0 == mem_ocr0b) begin
									oc0b <= 1;
								end
								
								if (mem_tcnt0 == 1) begin
									oc0b <= 0;
								end
							 
							 end
                      
                  endcase
						 
					 end
					 
                default: begin
                    case (com0a)
                        default: ; // Do nothing, OC0A disconnected from timer
                    endcase

                    case (com0b)
                        default: ; // Do nothing, OC0B disconnected from timer
                    endcase
                end
            endcase
        end
    end

endmodule
