package Task2;

import Task1.MyHashMap;
import com.sun.tools.javac.jvm.Gen;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

public class Test {

    /** Metoda generica ce returneaza suma elementelor din colectie **/
    public static <Generic extends Sumabil> Generic addAll(Collection<Generic> elements) {

        Iterator iterator = elements.iterator();
        Generic elem = (Generic) iterator.next();

        for ( ; iterator.hasNext();) {

            elem.addValue((Generic)iterator.next());
        }
        return elem;
    }
    public static void main(String[] args) {

        Collection<Sumabil> vectorcollection = new ArrayList<Sumabil>();
        Collection<Sumabil> matrixcollection = new ArrayList<Sumabil>();
        MyVector3 vector1 = new MyVector3(2, 5, 1);
        MyMatrix matrix1 = new MyMatrix(4, 4);
        MyMatrix display = new MyMatrix(4, 4);

        /** Printeaza vectorul cu valorile de la initializare **/
        System.out.println(vector1);

        vectorcollection.add(vector1);
        addAll(vectorcollection);

        /** Printeaza vectorul dupa ce a fost adaugata inca odata o instanta de tipul MyVector3 **/
        System.out.println(vectorcollection);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix1.mymatrix[i][j] = 2;
            }
        }

        /** Printeaza matricea cu valorile de la initializare **/
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                System.out.print(matrix1.mymatrix[i][j]);
                System.out.print(" ");
            }
            System.out.print("\n");
        }

        System.out.print("\n");

        matrixcollection.add(matrix1);

        Sumabil sum = addAll(matrixcollection);

        display = (MyMatrix) sum;

        System.out.println((MyMatrix) sum);



        /** Printeaza matricea dupa ce a fost adaugata inca odata o instanta de tipul MyMatrix **/
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                System.out.print(display.mymatrix[i][j]);
                System.out.print(" ");
            }
            System.out.print("\n");
        }

        System.out.println("\n");


    }
}
