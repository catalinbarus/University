package rankSort;

import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

public class Testapd {

    public static int[] initial_array;
    public static int[] rank_array;
    public static int[] sorted_array;
    public static CyclicBarrier barrier;
    public static Semaphore semaphore = new Semaphore(1);

    public static void main(String[] args) {

        int array_size = Integer.parseInt(args[0]);
        int nr_threads = Integer.parseInt(args[1]);
        System.out.println(array_size);
        System.out.println(nr_threads);

        initial_array = new int[array_size];
        rank_array = new int[array_size];
        sorted_array = new int[array_size];

        for (int i = 0; i < array_size; i++) {
            initial_array[i] = array_size - i + 5;
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

