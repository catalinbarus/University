package Lab4;
import java.util.Random;

public class PasswordMaker {

    public static final int MAGIC_NUMBER = 30;
    public static final String MAGIC_STRING = "1qmrA9Lfvxc0OPzHyu4n";

    private String name;

    /** Getter si Setter pentru stringul name. **/
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    /** Constructorul care primeste stringul name. **/
    public PasswordMaker(String name) {
        this.name = name;
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
        String length_of_name = String.valueOf(name.length());

        /* Numar random din intervalul [0, 100] */
        int rand_int = rand.nextInt(101);

        return random_string.next() + length_of_name + rand_int;
    }

    /** Testare **/
    public static void main(String[] args) {

        PasswordMaker pass = new PasswordMaker("Name");

        System.out.println(pass.getPassword());

        System.out.println(pass.getPassword().length());
    }


}
