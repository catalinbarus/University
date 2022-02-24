package first;

/** Clasa care implementeaza execute si afiseaza un
 * mesaj la output.
 **/
public class OutTask implements Task {

    String message;

    public OutTask(String message) {
        this.message = message;
    }
    public void execute() {
        System.out.println(this.message);
    }
}
