package first;
import java.util.Random;

/** Clasa care implementeaza execute si afiseaza un mesaj folosind
 * un numar generat random.
 **/
public class RandomOutTask implements Task {

    Random rand = new Random();
    int number;

    public RandomOutTask() {
        this.number = rand.nextInt(101);
    }

    public void execute() {
        System.out.println("Ana are " + this.number + " mere.");
    }
}
