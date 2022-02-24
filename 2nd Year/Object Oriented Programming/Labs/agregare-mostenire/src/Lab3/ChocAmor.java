package Lab3;

public class ChocAmor extends CandyBox {

    float length;

    /** Constructor fara parametrii **/
    public ChocAmor() {
    }

    /** Constructor cu parametrii care foloseste si constructorul din CandyBox **/
    public ChocAmor(float length) {
        super("Milk", "British");
        this.length = length;
    }

    /** Metoda printDim(), folosind downcasting **/
    void printDim() {
        System.out.println("  Length: " + this.length);
    }

    void printChocAmorDim() {
        System.out.println("  Length: " + this.length);
    }

    /** Suprascrierea metodei getVolume() **/
    @Override
    float getVolume() {
        return this.length * this.length * this.length;
    }

    @Override
    public String toString() {
        return "The " +
                this.getOrigin() + " " +
                this.getFlavor() + " has volume " +
                this.getVolume();
    }
}
