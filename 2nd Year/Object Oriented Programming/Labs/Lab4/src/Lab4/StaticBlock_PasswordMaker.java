package Lab4;
import java.util.Random;

public class StaticBlock_PasswordMaker {

    /** Memoria pentru instance este alocata inca de la inceput, intr-un bloc static. **/
    public static StaticBlock_PasswordMaker instance;
    static{
        instance = new StaticBlock_PasswordMaker();
    }

    String name;

    public static final int MAGIC_NUMBER = 30;
    public static final String MAGIC_STRING = "1qmrA9Lfvxc0OPzHyu4n";

    /** Constructor privat. **/
    private StaticBlock_PasswordMaker() {
        name = "Name";
    }

    /** Metoda statica pentru instanta clasei Singleton. **/
    public static StaticBlock_PasswordMaker getInstance() {
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

        StaticBlock_PasswordMaker static_pass = StaticBlock_PasswordMaker.getInstance();

        System.out.println(static_pass.getPassword());
        System.out.println(static_pass.getPassword().length());
    }

}
