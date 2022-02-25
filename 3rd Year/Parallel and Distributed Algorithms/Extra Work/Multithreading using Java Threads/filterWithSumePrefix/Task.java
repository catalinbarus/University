package filterWithSumePrefix;

import java.sql.SQLOutput;
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

        for (int i = start; i < end; i++) {

            if (Testapd.array[i] >= 10) {
                Testapd.bit_array[i] = 1;

            }
        }

        try {
            Testapd.barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        if (id == 0) {
            for (int i = 0; i < array_size; i++) {
                System.out.print(Testapd.bit_array[i] + " ");
            }
            System.out.print("\n");
        }

        int d = 1;

        while(d < array_size) {
            Testapd.temp[id] = Testapd.bit_array[id];

            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

            if (id - d >= 0) {
                Testapd.bit_array[id] = Testapd.temp[id - d] + Testapd.bit_array[id];
            }

            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

            d = 2 * d;
        }

        if (id == 0) {
            for (int i = 0; i < array_size; i++) {
                System.out.print(Testapd.bit_array[i] + " ");
            }
            System.out.print("\n");

            int nextNumber = 0;
            for (int i = 0; i < array_size; i++) {
                if (Testapd.bit_array[i] > nextNumber) {
                    nextNumber = Testapd.bit_array[i];
                    System.out.print(Testapd.array[i] + " ");
                }
            }
            System.out.print("\n");
        }
    }
}
