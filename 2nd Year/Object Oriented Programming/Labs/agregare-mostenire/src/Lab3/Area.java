package Lab3;

public class Area {

    CandyBag candybag = new CandyBag();
    int number;
    String street;

   public Area() {

    }

    /** Constuctor ce initializeaza Area cu parametrii ceruti **/
    public Area(CandyBag candybag, int number, String street) {
        this.candybag = candybag;
        this.number = number;
        this.street = street;
    }

    /** Metoda ce afiseaza mesajul de la multi ani impreuna cu toate
     * cutiile de bomboane
     **/
    void getBirthdayCard() {
        System.out.println("Adresa destinatar: " + this.street + this.number);
        System.out.println("\n");
        System.out.println("Happy Birthday!" + "\n");

        for(int i = 0; i<this.candybag.bag.size(); i++) {

            System.out.println(this.candybag.bag.get(i));
            this.candybag.bag.get(i).printDim();
        }
    }
}
