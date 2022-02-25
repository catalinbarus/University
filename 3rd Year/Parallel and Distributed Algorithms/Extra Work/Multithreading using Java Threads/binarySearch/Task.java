package binarySearch;

import java.util.concurrent.BrokenBarrierException;

public class Task extends Thread {

    int id;
    int array_size;
    int numberToFind;
    int nr_threads;

    public Task(int id, int array_size, int numberToFind, int nr_threads) {
        this.id = id;
        this.array_size = array_size;
        this.numberToFind = numberToFind;
        this.nr_threads = nr_threads;
    }

    @Override
    public void run() {
        int start = (int) (id * (double) array_size / nr_threads);
        int end = (int) Math.min((id + 1) * (double) array_size / nr_threads, array_size);

        if (id == nr_threads - 1) {
            end = end - 1;
        }

        try {
            Testapd.semaphore.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        if (numberToFind < Testapd.array[end]) {

            if (Testapd.array[end] < Testapd.upperBound) {
                Testapd.upperBound = Testapd.array[end];
                Testapd.rightThread = id;
            }
        }

        Testapd.semaphore.release();

        try {
            Testapd.barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        if (Testapd.rightThread == -1) {

            try {
                Testapd.semaphore.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            if (numberToFind == Testapd.array[end]) {
                Testapd.upperBound = Testapd.array[end];
                Testapd.rightThread = id;
            }

            Testapd.semaphore.release();
        }

        if (id == Testapd.rightThread) {

            if (numberToFind == Testapd.array[end]) {
                System.out.println("Found " + numberToFind + " in subarray " + (id + 1));
                System.exit(0);
            }

            for (int i = start; i < end; i++) {
                if (Testapd.array[i] == numberToFind) {
                    System.out.println("Found " + numberToFind + " in subarray " + (id + 1));
                    System.exit(0);
                }
            }
            System.out.println("Number " + numberToFind + " not found.");
        }

        if (id == 0) {
            if (Testapd.rightThread == -1) {
                System.out.println("Number " + numberToFind + " not found.");
            }
        }
    }
}
