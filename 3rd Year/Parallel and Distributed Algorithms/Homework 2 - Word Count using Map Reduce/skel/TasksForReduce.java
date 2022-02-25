import java.util.ArrayList;
import java.util.HashMap;

public class TasksForReduce {

    public String filename;
    public ArrayList<HashMap<Integer, Integer>> wordsCounter;
    public ArrayList<ArrayList<String>> maximumsList;

    public TasksForReduce(String filename, ArrayList<HashMap<Integer, Integer>> wordsCounter, ArrayList<ArrayList<String>> maximumsList) {
        this.filename = filename;
        this.wordsCounter = wordsCounter;
        this.maximumsList = maximumsList;
    }

    @Override
    public String toString() {
        return "TasksForReduce{" +
                "filename='" + filename + '\'' +
                ", wordsCounter=" + wordsCounter +
                ", maximumsList=" + maximumsList +
                '}';
    }
}
