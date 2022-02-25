package sumePrefix;

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

        int d = 1;

        while(d < array_size) {
            Testapd.temp[id] = Testapd.array[id];

            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

            if (id - d >= 0) {
                Testapd.array[id] = Testapd.temp[id - d] + Testapd.array[id];
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
                System.out.print(Testapd.array[i] + " ");
            }
            System.out.print("\n");
        }


    }
}
