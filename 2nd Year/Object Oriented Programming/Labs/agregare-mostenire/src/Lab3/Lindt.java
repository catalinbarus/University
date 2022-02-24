package Lab3;

public class Lindt extends CandyBox {

    float length, width, height;

    /** Constructor fara parametrii **/
    public Lindt() {
    }

    /** Constructor cu parametrii care foloseste si constructorul din CandyBox **/
    public Lindt(float length, float width, float height) {
        super("Raspberry", "Swiss");
        this.length = length;
        this.width = width;
        this.height = height;
    }

    /** Metoda printDim(), folosind downcasting **/
    void printDim() {
        System.out.println("  Length: " + this.length);
        System.out.println("  Height: " + this.height);
        System.out.println("  Width: " + this.width);
    }

    void printLindtDim() {
        System.out.println("  Length: " + this.length);
        System.out.println("  Height: " + this.height);
        System.out.println("  Width: " + this.width);
    }

    /** Suprascrierea metodei getVolume() **/
    @Override
    float getVolume() {
        return this.length * this.width * this.height;
    }

    @Override
    public String toString() {
        return "The " +
                this.getOrigin() + " " +
                this.getFlavor() + " has volume " +
                this.getVolume();
    }
}
