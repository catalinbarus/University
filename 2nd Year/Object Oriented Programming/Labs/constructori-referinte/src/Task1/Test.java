package Task1;

public class Test {
    public static void main(String[] args){

        Complex complex = new Complex(5, 5);
        Complex complex1 = new Complex(complex);

        complex.addWithComplex(complex);

        complex.showNumber(complex1);
        complex.showNumber(complex);

    }
}
