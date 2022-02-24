package second;

import java.util.ArrayList;
import first.*;

public class Queue implements Container {

    public ArrayList<Task> getTasks() {
        return queue;
    }

    ArrayList<Task> queue = new ArrayList<>();

    public Task pop() {
        if(this.queue.size() != 0) {
            Task first = this.queue.get(0);
            this.queue.remove(0);
            return first;
        }
        return null;

    }

    public void push(Task task) {
        this.queue.add(task);
    }

    public int size() {
        return this.queue.size();
    }

    public boolean isEmpty(){
        if(this.queue.size() == 0) {
            return true;
        }

        return false;
    }

    public void transferFrom(Container container) {

        int no_elements = container.size();
        for(int i = 0; i < no_elements; i++) {
            this.push(container.pop());
        }
    }
}
