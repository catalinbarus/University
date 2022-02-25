package producer_consumer;

import java.util.LinkedList;
import java.util.concurrent.Semaphore;

public class Semaphores {

    static Object LOCK = new Object();

    static LinkedList<Integer> list = new LinkedList<Integer>();
    static Semaphore sem = new Semaphore(0);
    static Semaphore mutex = new Semaphore(1);

    static class Consumer extends Thread {
        String name;
        public Consumer(String name) {
            this.name = name;
        }
        public void run() {
            try {

                while (list.getFirst() < 10 && !list.isEmpty()) {
                    sem.acquire(1);
                    mutex.acquire();
                    System.out.println("Consumer \""+name+"\" read: "+list.removeFirst());
                    mutex.release();
                }
            } catch (Exception x) {
                x.printStackTrace();
            }
        }
    }

    static class Producer extends Thread {
        public void run() {
            try {

                int N = 0;

                while (N <= 10) {
                    mutex.acquire();
                    list.add(N++);
                    mutex.release();
                    sem.release(1);
                    Thread.sleep(500);
                }
            } catch (Exception x) {
                x.printStackTrace();
            }
        }
    }

    public static void main(String [] args) {

        Thread[] threads = new Thread[3];

        threads[0] = new Producer();
        threads[1] = new Consumer("Alice");
        threads[2] = new Consumer("Bob");

        for (int i = 0; i < 3; i++) {
            threads[i].start();
        }

        for (int i = 0; i < 3; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }


    }
}
