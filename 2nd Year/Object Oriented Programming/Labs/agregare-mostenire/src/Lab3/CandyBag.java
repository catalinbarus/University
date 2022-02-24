package Lab3;
import java.util.ArrayList;

public class CandyBag extends CandyBox {

    /** Initializarea ArrayList-ului si a cutiilor cu bomboane **/
    ArrayList<CandyBox> bag = new ArrayList<>(5);

    Lindt lindt1 = new Lindt(3, 4, 5);
    Lindt lindt2 = new Lindt(2, 5, 6);

    Baravelli baravelli1 = new Baravelli(2, 5);

    ChocAmor chocamor1 = new ChocAmor(4);
    ChocAmor chocamor2 = new ChocAmor(2);

    /** Un constructor separat pentru adaugarea cutiilor in ArrayList **/
    public CandyBag(){
        bag.add(lindt1);
        bag.add(lindt2);
        bag.add(baravelli1);
        bag.add(chocamor1);
        bag.add(chocamor2);
    }
}
