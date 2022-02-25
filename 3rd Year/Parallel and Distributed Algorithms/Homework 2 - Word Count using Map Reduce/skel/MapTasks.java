import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

// Thread class used that implements the map logic
public class MapTasks extends Thread {
    public int id;

    public MapTasks(int id) {
        this.id = id;
    }

    @Override
    public String toString() {
        return "Thread{" +
                "id=" + id +
                '}';
    }

    @Override
    public void run() {
        int start = (int) (id * (double) Tema2.initialTasks.size() / (Tema2.nrWorkers));
        int end = (int) Math.min((id + 1) * (double) Tema2.initialTasks.size() / (Tema2.nrWorkers), Tema2.initialTasks.size());

        for (int j  = start; j < end; j++) {

            // Get a task from the initial ones
            TasksForMap task = Tema2.initialTasks.get(j);

            // Already build the map result for ease
            mapResult result = new mapResult(task.fileName,new HashMap<Integer, Integer>(),new ArrayList<String>());
            String fileName = "../" + task.fileName;


            try {

                // Read from the corresponding file from the specified offset in the current task
                BufferedReader br = new BufferedReader(new FileReader(fileName));
                br.skip(task.offsetOfTask);

                int max = 0;
                int wordLength = 0;
                String word = "";
                for(int i = 0; i < task.sizeOfTask; i++) {

                    // Read each letter and check if it is a separator or not
                    String letter = Character.toString((char) br.read());
                    if(!Tema2.wordsSeparators.contains(letter) && i != task.sizeOfTask - 1) {

                        wordLength ++;
                        word += letter;
                    } else {

                        // Also check if the last letter was indeed a character
                        if (i == task.sizeOfTask - 1) {

                            if (!Tema2.wordsSeparators.contains(letter)) {
                                wordLength ++;
                                word += letter;
                            }
                        }

                        // Check if the current length is greater than the previously
                        // found maximum
                        if (wordLength > max) {

                            result.maximums.clear();
                            result.maximums.add(word);
                            max = wordLength;

                        } else if (wordLength == max) {

                            result.maximums.add(word);
                        }

                        // Store word length and number of appearances in the map
                        if(result.nrAppearances.get(wordLength) != null) {

                            result.nrAppearances.put(wordLength, result.nrAppearances.get(wordLength) + 1);

                        } else if(wordLength != 0){

                            result.nrAppearances.put(wordLength, 1);
                        }

                        // Reset for next possible word
                        word = "";
                        wordLength = 0;
                    }
                }
            }  catch (IOException e) {
                e.printStackTrace();
            }

            // Make sure each map task is added in the list of results
            try {

                Tema2.semaphore.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            Tema2.mapResults.add(result);

            Tema2.semaphore.release();
        }
    }
}
