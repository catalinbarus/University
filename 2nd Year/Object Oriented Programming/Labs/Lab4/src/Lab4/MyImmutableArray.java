package Lab4;
import java.util.ArrayList;
import java.util.List;
import java.util.Collection;
import java.util.Collections;

public class MyImmutableArray {

    private final ArrayList<Integer> immutableArray;

    /** Constructorul ce completeaza elementele primite dintr-un array dat ca parametru. **/
    public MyImmutableArray(ArrayList<Integer> array) {

        immutableArray = new ArrayList<>(5);

        int i;

        for(i = 0; i < array.size(); i++)
        {
            immutableArray.add(array.get(i));
        }
    }

    /** Metoda ce ne asigura ca array-ul este immutable. **/
    public ArrayList<Integer> getArray() {
        return new ArrayList<>(immutableArray);
    }

    /** Testare **/
    public static void main(String[] args) {

        ArrayList<Integer> array = new ArrayList<>(5);

        array.add(4);
        array.add(10);
        array.add(5);
        array.add(1);
        array.add(89);

        MyImmutableArray immutable = new MyImmutableArray(array);
        ArrayList<Integer> test = immutable.getArray();

        /** Adaugarea pe pozitia 2 din arraylist nu modifica 5 la 25, deci array-ul este immutable. **/
        test.add(2, 25);

        System.out.println(immutable.getArray());
    }
}
