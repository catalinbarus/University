package odd_even_TranspositionSort;

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

        int start_odd_phase, start_even_phase;

        if (start % 2 == 0) {
            start_even_phase = start;
            start_odd_phase = start + 1;

        } else {
            start_even_phase = start + 1;
            start_odd_phase = start;

        }

        for (int i = 0; i < array_size; i++) {

            // Incepem faza para
            for (int even_idx = start_even_phase; even_idx < end && (even_idx < array_size - 1); even_idx += 2) {

                if(Testapd.array[even_idx] > Testapd.array[even_idx + 1]) {
                    int aux = Testapd.array[even_idx];
                    Testapd.array[even_idx] = Testapd.array[even_idx + 1];
                    Testapd.array[even_idx + 1] = aux;
                }

            }

            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

            // Incepem faza impara
            for (int odd_idx = start_odd_phase; odd_idx < end && (odd_idx < array_size - 1); odd_idx += 2) {

                if(Testapd.array[odd_idx] > Testapd.array[odd_idx + 1]) {
                    int aux = Testapd.array[odd_idx];
                    Testapd.array[odd_idx] = Testapd.array[odd_idx + 1];
                    Testapd.array[odd_idx + 1] = aux;
                }
            }

            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }

        if (id == 0) {
            for (int i = 0; i < array_size; i++) {
                System.out.print(Testapd.array[i] + " ");
            }
            System.out.print("\n");
        }
    }
}
