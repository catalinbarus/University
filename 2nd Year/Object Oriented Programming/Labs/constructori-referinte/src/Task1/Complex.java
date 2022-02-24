package Task1;

public class Complex {
    private int real;
    private int imaginary;

    /** Getter si Setter pentru variabila real **/

    public int getReal() {
        return real;
    }

    public void setReal(int real) {
        this.real = real;
    }

    /** Getter si Setter pentru variabila imaginary **/

    public int getImaginary() {
        return imaginary;
    }

    public void setImaginary(int imaginary) {
        this.imaginary = imaginary;
    }

    /** Primul Constructor **/
    public Complex(int real, int imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    /** Al doilea Constructor **/
    public Complex() {
        this(0, 0);
    }

    /** Al treilea Constructor (Copy Constructor) **/
    public Complex(Complex complex) {
        this.real = complex.real;
        this.imaginary = complex.imaginary;
    }

    /** Functia addWithComplex **/
    void addWithComplex(Complex complex) {
        this.real += complex.real;
        this.imaginary += complex.imaginary;
    }

    /** Functia showNumber **/
    void showNumber(Complex complex) {
        System.out.println(complex.real + " " + "+" + " " + "i" + complex.imaginary);
    }

}
