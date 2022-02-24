package Lab4;
import java.util.Random;

public class Eager_init_PasswordMaker {

    /** Memoria pentru instance este alocata inca de la inceput. **/
    public static Eager_init_PasswordMaker instance =
            new Eager_init_PasswordMaker();

    /** instanceCount trebuie initializat ca static pentru a nu primi
     *  eroare de compilare in Main. **/
    public static int instanceCount;
    private String name;

    public static final int MAGIC_NUMBER = 30;
    public static final String MAGIC_STRING = "1qmrA9Lfvxc0OPzHyu4n";

    /** Constructor privat. **/
    private Eager_init_PasswordMaker() {
        name = "Name";

    }

    /** Metoda statica pentru instanta clasei Singleton. **/
    public static Eager_init_PasswordMaker getInstance() {
        instanceCount++;
        return instance;
    }

    /** Metoda ce returneaza parola. **/
    public String getPassword() {

        Random rand = new Random();

        /* Stringul cu 10 caractere random din MAGIC_STRING. */
        RandomStringGenerator random_alphabet = new RandomStringGenerator(10, PasswordMaker.MAGIC_STRING);

        /* Stringul de dimensiune MAGIC_NUMBER. */
        RandomStringGenerator random_string =
                new RandomStringGenerator(PasswordMaker.MAGIC_NUMBER, random_alphabet.next());

        /* Lungimea lui name convertita la String. */
        String length_of_name = String.valueOf(instance.name.length());

        /* Numar random din intervalul [0, 100] */
        int rand_int = rand.nextInt(101);

        return random_string.next() + length_of_name + rand_int;
    }

    /** Testare **/
    public static void main(String[] args) {

        Eager_init_PasswordMaker eager = Eager_init_PasswordMaker.getInstance();

        System.out.println(eager.getPassword());
        System.out.println(eager.getPassword().length());

        System.out.println(Eager_init_PasswordMaker.instanceCount + " instances."); // O sa afiseze 1 instanta.

        Eager_init_PasswordMaker eager1 = Eager_init_PasswordMaker.getInstance();
        Eager_init_PasswordMaker eager2 = Eager_init_PasswordMaker.getInstance();
        Eager_init_PasswordMaker eager3 = Eager_init_PasswordMaker.getInstance();

        System.out.println(Eager_init_PasswordMaker.instanceCount + " instances."); // O sa afiseze 3 instante.
    }


}
