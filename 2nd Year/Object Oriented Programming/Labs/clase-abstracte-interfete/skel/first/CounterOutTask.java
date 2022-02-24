package first;

/** Clasa care implementeaza execute si afiseaza valoarea unui
 * contor global dupa fiecare implementare.
 **/
public class CounterOutTask implements Task {

    public static int counter = 0;

    public CounterOutTask() {
        counter++;
    }

    public void execute() {
        System.out.println(counter);
    }
}
