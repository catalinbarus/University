package rankSort;

import java.util.concurrent.BrokenBarrierException;

public class Task extends Thread {

    int id;
    int array_size;
    int nr_threads;

    public Task(int id, int array_size, int nr_threads) {
        this.id = id;
        this.array_size = array_size;
        this.nr_threads = nr_threads;
    }

    @Override
    public void run() {
        int start = (int) (id * (double) array_size / nr_threads);
        int end = (int) Math.min((id + 1) * (double) array_size / nr_threads, array_size);

        for (int i = 0; i < array_size; i++) {

            try {
                // shared space is locked
                Testapd.semaphore.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            for (int j = start; j < end; j++) {
                if (Testapd.initial_array[j] < Testapd.initial_array[i]) {
                    Testapd.rank_array[i]++;
                }
            }

            Testapd.semaphore.release();

            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }

        if (id == 0) {
            System.out.println("Rank-uri:");
            for (int i = 0; i < array_size; i++) {
                System.out.println(Testapd.rank_array[i] + " ");
            }
        }

        for (int i = start; i < end; i++) {
            Testapd.sorted_array[i] = Testapd.initial_array[Testapd.rank_array[i]];
        }

        try {
            Testapd.barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        if (id == 0) {
            System.out.println("Implementare paralela:");
            for (int i = 0; i < array_size; i++) {
                System.out.print(Testapd.sorted_array[i] + " ");
            }
            System.out.print("\n");
        }
    }
}
