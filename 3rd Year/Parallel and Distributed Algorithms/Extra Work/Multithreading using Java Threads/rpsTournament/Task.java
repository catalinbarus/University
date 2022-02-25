package rpsTournament;

import java.util.Random;

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

    public String element(Integer a){
        if(a == 0) {
            return "piatra";
        }
        if(a == 1) {
            return "hartie";
        }
        return "foarfeca";
    }

    public boolean decideWinner(Integer a, Integer b) {
        if(a == b) {
            return false;
        }
        if(a == 0 && b == 1) {
            return false;
        }

        if(a == 1 && b == 2) {
            return false;
        }

        if(a == 2 && b == 0) {
            return false;
        }

        return true;
    }


    public Integer randomNr() {
        //0 = piatra
        //1 = hartie
        //2 = foarfeca
        Random random = new Random();
        Integer var = random.nextInt(3);
        return var;
    }

    @Override
    public void run() {

        int nrRunde = 0;
        int d = 1;

        while(d < array_size) {
            nrRunde ++;
            //---------------------------------------------------------
            Testapd.array[id] = randomNr();
            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
            //---------------------------------------------------------

            Testapd.temp[id] = Testapd.array[id];

            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

            //---------------------------------------------------------

            if (id - d >= 0) {

                if((id + 1) % (d * 2) == 0) {
                    System.out.println("Threadul " + Testapd.winners[id - d] + " care a ales " + element(Testapd.temp[id - d])
                            + " se bate cu threadul " + Testapd.winners[id] + " care a ales " + element(Testapd.array[id]));

                }

                if (decideWinner(Testapd.temp[id - d], Testapd.array[id])) {
                    Testapd.array[id] = id - d;
                    Testapd.winners[id] = id - d;
                } else {
                    Testapd.array[id] = id;
                    Testapd.winners[id] = id;
                }



            }

            try {
                Testapd.barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

            d = 2 * d;
        }

        if (id == 0) {
            /*for (int i = 0; i < array_size; i++) {
                System.out.print(Testapd.array[i] + " ");
            }*/
            System.out.println("Threadul " + Testapd.array[array_size -1] + " a castigat dupa " + nrRunde + " runde");
            System.out.print("\n");
        }

    // 1 --- 5, 3, 7, 0
    // 2 --- 5
    }
}
