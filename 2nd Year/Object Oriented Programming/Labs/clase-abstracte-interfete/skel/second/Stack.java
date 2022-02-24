package second;

import java.util.ArrayList;
import first.*;

public class Stack implements Container {

    public ArrayList<Task> getTasks() {
        return stack;
    }

    ArrayList<Task> stack = new ArrayList<>();

    public Task pop() {
        if(this.stack.size() != 0) {
            Task last = this.stack.get(this.stack.size() - 1);
            this.stack.remove(this.stack.size() - 1);
            return last;
        }
        return null;

    }

    public void push(Task task) {
        this.stack.add(task);
    }

    public int size() {
        return this.stack.size();
    }

    public boolean isEmpty(){
        if(this.stack.size() == 0) {
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
