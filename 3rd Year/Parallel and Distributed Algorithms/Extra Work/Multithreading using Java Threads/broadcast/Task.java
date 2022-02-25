package broadcast;

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

        int indxCur = id;
        while(indxCur < array_size) {
            Testapd.array[indxCur] = Testapd.numberToBroadcast;
            indxCur += nr_threads;
        }

        try {
            Testapd.barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        if(id == 0){
            for(int i = 0; i < array_size; i++) {
                System.out.print(Testapd.array[i] + " ");
            }
            System.out.print("\n");
        }


    }
}
