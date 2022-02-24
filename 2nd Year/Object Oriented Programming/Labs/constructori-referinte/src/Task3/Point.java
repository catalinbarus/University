package Task3;

public class Point {

    private float x;
    private float y;

    /** Getter si Setter pentru variabila x **/
    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    /** Getter si Setter pentru variabila y **/

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    /** Constructor ce primeste numerele asociate coordonatelor **/
    public Point(float x, float y) {
        this.x = x;
        this.y = y;
    }

    /** Consturctor ce initializeaza coordonatele cu 0 pentru orice variabila de tip Point **/
    public Point(){
        this(0, 0);
    }

    /** Functia changeCoords **/
    void changeCoords(float x, float y) {
        this.x = x;
        this.y = y;
    }

    /** Functie folosita pentru afisarea coorodnatelor unui punct **/
    void showCoords(Point point) {
        System.out.println("(" + point.x + ", " + point.y + ")");
    }
}
