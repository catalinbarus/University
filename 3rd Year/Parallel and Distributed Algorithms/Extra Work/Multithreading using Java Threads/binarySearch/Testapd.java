package binarySearch;

import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

public class Testapd {

    public static int[] array
            = {1, 1, 2, 3, 5, 5, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9};


    public static int upperBound;
    public static int rightThread = -1;
    public static CyclicBarrier barrier;
    public static Semaphore semaphore = new Semaphore(1);

    public static void main(String[] args) {

        int array_size = 16;
        int numberToFind = Integer.parseInt(args[0]);
        int nr_threads = Integer.parseInt(args[1]);

        upperBound = array[array_size - 1] + 1;

        Thread[] threads = new Thread[nr_threads];
        barrier = new CyclicBarrier(nr_threads);

        for (int i = 0; i < nr_threads; i++) {
            threads[i] = new Task(i, array_size, numberToFind, nr_threads);
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

