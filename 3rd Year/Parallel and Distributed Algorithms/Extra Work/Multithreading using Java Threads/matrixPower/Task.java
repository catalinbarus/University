package matrixPower;

import java.util.concurrent.BrokenBarrierException;

public class Task extends Thread {

    int id;
    int matrixLen;
    int nr_threads;
    int power;

    public Task(int id, int matrixLen, int nr_threads, int power) {
        this.id = id;
        this.matrixLen = matrixLen;
        this.nr_threads = nr_threads;
        this.power = power;
    }

    @Override
    public void run() {

        int start = (int) (id * (double) matrixLen / nr_threads);
        int end = (int) Math.min((id + 1) * (double) matrixLen / nr_threads, matrixLen);

        if (id == 0) {
            for (int i = 0; i < matrixLen; i++) {

                for (int j = 0; j < matrixLen; j++) {

                    System.out.print(Testapd.matrix[i][j] + " ");
                }
                System.out.print("\n");
            }
        }

        int step = 1;

        while (step < power) {

            if (id == 0) {
                for (int idx1 = 0; idx1 < matrixLen; idx1++) {
                    for (int idx2 = 0; idx2 < matrixLen; idx2++) {
                        Testapd.result[idx1][idx2] = 0;
                    }
                }
            }

            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

            for (int i = 0; i < matrixLen; i++) {
                for (int j = 0; j < matrixLen; j++) {

                    long helper_sum = 0;

                    // Incrementam toata suma de pe for-ul interior intr-un helper
                    // pentru ca aceasta sa nu se piarda
                    if (step == 1) {
                        for (int k = start; k < end; k++) {
                            helper_sum += Testapd.matrix[i][k] * Testapd.matrix[k][j];
                        }
                    }

                    else {
                        for (int k = start; k < end; k++) {
                            helper_sum += Testapd.matrix_copy[i][k] * Testapd.matrix[k][j];
                        }

                    }

                    try {
                        Testapd.barrier.await();
                    } catch (InterruptedException | BrokenBarrierException e) {
                        e.printStackTrace();
                    }

                    // Pentru a ne asigura ca matricea c la un
                    // anumit moment de timp primeste o singura valoare
                    // ce nu va fi suprascrisa, blocam executia cu un mutex
                    try {
                        Testapd.semaphore.acquire();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                    Testapd.result[i][j] += helper_sum;

                    Testapd.semaphore.release();

                    try {
                        Testapd.barrier.await();
                    } catch (InterruptedException | BrokenBarrierException e) {
                        e.printStackTrace();
                    }
                }
            }

            if (id == 0) {
                for (int idx1 = 0; idx1 < matrixLen; idx1++) {
                    for (int idx2 = 0; idx2 < matrixLen; idx2++) {
                        Testapd.matrix_copy[idx1][idx2] = Testapd.result[idx1][idx2];
                    }
                }
            }

            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

            step++;
        }

        try {
            Testapd.barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        if (id == 0) {

            for (int i = 0; i < matrixLen; i++) {
                for (int j = 0; j < matrixLen; j++) {

                    System.out.print(Testapd.result[i][j] + " ");
                }
                System.out.print("\n");
            }
        }
    }
}
