import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.TreeSet;

// Task 7
public class ExtendedHashSet extends LinkedHashSet<Integer> {

    @Override
    public boolean add(Integer integer) {
        if(integer % 2 == 0) {
            return super.add(integer);
        }

        return false;
    }

    public static void main(String[] args) {

        ExtendedHashSet extended = new ExtendedHashSet();
        extended.add(3);
        extended.add(6);
        extended.add(7);
        extended.add(8);
        extended.add(10);
        extended.add(14);
        extended.add(44);
        System.out.println(extended);

        /**
         * When I switched LinkedHashSet with either HashSet or TreeSet I did not notice any
         * changes regarding the insertion order of the elements.
         */
        Iterator<Integer> iterator = extended.iterator();
        while(iterator.hasNext()) {
            System.out.println(iterator.next());
        }
    }
}
