import java.util.Map;

// Thread class used that implements the reduce logic
public class ReduceTasks extends Thread {

    public Integer id;

    public ReduceTasks(Integer id) {
        this.id = id;
    }

    @Override
    public String toString() {
        return "ReduceTasks{" +
                "id=" + id +
                '}';
    }

    @Override
    public void run() {

        int start = (int) (id * (double) Tema2.tasksForReduces.size() / (Tema2.nrWorkers));
        int end = (int) Math.min((id + 1) * (double) Tema2.tasksForReduces.size() / (Tema2.nrWorkers), Tema2.tasksForReduces.size());

        for (int j = start; j < end; j++) {

            // Get one task from the reduce pool
            TasksForReduce task = Tema2.tasksForReduces.get(j);


            Integer numOfwords = 0;
            Integer fiboSum = 0;

            // Compute the total number of words and also the sum based
            // on the fibonacci sequence
            for (int i = 0; i < task.wordsCounter.size(); i++) {

                for (Map.Entry<Integer, Integer> entry : task.wordsCounter.get(i).entrySet()) {


                    numOfwords += entry.getValue();
                    fiboSum += Tema2.getFiboSequence(entry.getKey() + 1) * entry.getValue();

                }
            }

            // Determine the rank of the document based on the previous computations
            Float rank = fiboSum.floatValue() / numOfwords.floatValue();

            // Determine what is the longest word/words and how many times they appear
            Integer maxLen = 0;
            Integer maximumOccurs = 0;
            for (int i = 0; i < task.maximumsList.size(); i++) {

                for (int k = 0; k < task.maximumsList.get(i).size(); k++) {

                    String currentWord = task.maximumsList.get(i).get(k);

                    if (currentWord.length() > maxLen) {
                        maxLen = currentWord.length();
                        maximumOccurs = 1;
                    }
                    else if (currentWord.length() == maxLen) {
                        maximumOccurs++;
                    }

                }
            }

            // Make sure each reduce task is added in the list of final results
            try {
                Tema2.semaphore.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            Tema2.finalResults.add(new finalResults(task.filename, String.format("%.2f", rank), maxLen, maximumOccurs));

            Tema2.semaphore.release();
        }
    }
}
