package Lab3;

public class Baravelli extends CandyBox {

    float radius, height;

    /** Constructor fara parametrii **/
    public Baravelli() {
    }

    /** Constructor cu parametrii care foloseste si constructorul din CandyBox **/
    public Baravelli(float radius, float height) {
        super("Chocolate", "Welsh");
        this.radius = radius;
        this.height = height;
    }

    /** Metoda printDim(), folosind downcasting **/
    void printDim() {
        System.out.println("  Height: " + this.height);
        System.out.println("  Radius: " + this.radius);
    }

    void printBaravelliDim() {
        System.out.println("  Height: " + this.height);
        System.out.println("  Radius: " + this.radius);
    }

    /** Suprascrierea metodei getVolume() **/
    @Override
    float getVolume() {
        float basesurface;
        basesurface = 3.14f * radius*radius;
        return basesurface * this.height;
    }

    @Override
    public String toString() {
        return "The " +
                this.getOrigin() + " " +
                this.getFlavor() + " has volume " +
                this.getVolume();
    }
}
