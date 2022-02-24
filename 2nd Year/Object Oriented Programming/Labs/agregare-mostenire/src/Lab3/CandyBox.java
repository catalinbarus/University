package Lab3;

public class CandyBox {

    private String flavor;
    private String origin;

    /** Getter si Setter pentru campul flavor **/
    public String getFlavor() {
        return flavor;
    }

    public void setFlavor(String flavor) {
        this.flavor = flavor;
    }

    /** Getter si Setter pentru campul origin **/
    public String getOrigin() {
        return origin;
    }

    public void setOrigin(String origin) {
        this.origin = origin;
    }

    /** Constructor fara parametrii **/
    public CandyBox() {
    }

    /** Constructor ce initializeaza toate campurile **/
    public CandyBox(String flavor, String origin) {
        this.flavor = flavor;
        this.origin = origin;
    }

    float getVolume(){
        return 0;
    }

    /** Metoda printDim(), folosita in downcasting **/
    void printDim() {
    }

    @Override
    public String toString() {
        return "CandyBox{" +
                "flavor='" + flavor + '\'' +
                ", origin='" + origin + '\'' +
                '}';
    }

    /** Pentru metoda equals() generata, am ales variabilele origin si flavor
     *  pentru criteriul de comparatie, fiind singurii identificatori din
     *  clasa CandyBox.
     **/

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof CandyBox)) return false;
        CandyBox candyBox = (CandyBox) o;
        return flavor.equals(candyBox.flavor) &&
                origin.equals(candyBox.origin);
    }
}
