package matrixPower;

import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

public class Testapd {

    public static long[][] matrix;
    public static long[][] matrix_copy;
    public static long[][] result;

    public static CyclicBarrier barrier;
    public static Semaphore semaphore = new Semaphore(1);

    public static void main(String[] args) {

        int matrixLen = Integer.parseInt(args[0]);
        int nr_threads = Integer.parseInt(args[1]);
        int power = Integer.parseInt(args[2]);

        matrix = new long[matrixLen][matrixLen];
        matrix_copy = new long[matrixLen][matrixLen];
        result = new long[matrixLen][matrixLen];

        for (int i = 0; i < matrixLen; i++) {
            for (int j = 0; j < matrixLen; j++) {
                matrix[i][j] = 1 + i * matrixLen + j;
                matrix_copy[i][j] = 1 + i * matrixLen + j;
                result[i][j] = 0;
            }
        }

        Thread[] threads = new Thread[nr_threads];
        barrier = new CyclicBarrier(nr_threads);

        for (int i = 0; i < nr_threads; i++) {
            threads[i] = new Task(i, matrixLen, nr_threads, power);
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

