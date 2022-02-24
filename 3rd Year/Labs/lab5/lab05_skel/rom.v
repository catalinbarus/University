module rom #(
        parameter   DATA_WIDTH = 16,
        parameter   ADDR_WIDTH = 8          // 2 * 1024 bytes of ROM
    )(
        input  wire                  clk,
        input  wire [ADDR_WIDTH-1:0] addr,  // here comes the program counter
        output  reg [DATA_WIDTH-1:0] data   // here goes the instruction
    );

    reg [DATA_WIDTH-1:0] value;

    
    always @* begin
        case (addr)
				/*	 ldi 	r16, 10 		*/
		0:		value = 16'b1110000000001010;
		/*	 push 	r16 		*/
		1:		value = 16'b1001001100001111;
		/*	 ldi 	r17, 2 		*/
		2:		value = 16'b1110000000010010;
		/*	 push 	r17 		*/
		3:		value = 16'b1001001100011111;
		/*	 rcall 	addition 		*/
		4:		value = 16'b1101000000000001;
		/*	 pop 	r16 		*/
		5:		value = 16'b1001000100001111;
		/*	 pop 	r17 		*/
		6:		value = 16'b1001000100011111;
		/*	 pop 	r16 		*/
		7:		value = 16'b1001000100001111;
		/*	 add 	r16, r17 		*/
		8:		value = 16'b0000111100000001;
		/*	 push 	r16 		*/
		9:		value = 16'b1001001100001111;
		/*	 ret 	 		*/
		10:		value = 16'b1001010100001000;
		
			default:		value = 16'b0000000000000000;
        endcase
    end

    always @(negedge clk) begin
        data <= value;
    end

endmodule
