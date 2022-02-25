package sum_of_odd_numbers;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

public class Testapd {

    public static int[] array = {6, 4, 13, 10, 11, 14, 2, 8};
    public static ArrayList<Integer> oddNrs = new ArrayList<>();
    public static int[] temp;
    public static int[] bit_array;
    public static int sumOdd = 0;

    public static CyclicBarrier barrier;
    public static Semaphore semaphore = new Semaphore(1);

    public static void main(String[] args) {

        int nr_threads = Integer.parseInt(args[0]);
        int array_size = 8;
        temp = new int[array_size];
        bit_array = new int[array_size];

        for (int i = 0; i < array_size; i++) {
            temp[i] = 0;
            bit_array[i] = 0;
        }

        Thread[] threads = new Thread[nr_threads];
        barrier = new CyclicBarrier(nr_threads);

        for (int i = 0; i < nr_threads; i++) {
            threads[i] = new Task(i, array_size, nr_threads);
        }

        for (var thread : threads) {
            thread.start();
        }

        for (var thread : threads) {

            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

