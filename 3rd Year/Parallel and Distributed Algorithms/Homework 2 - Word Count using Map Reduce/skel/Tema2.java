import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.concurrent.*;

public class Tema2 {

    // Static variables used for making certain tasks easier
    public static String wordsSeparators = ";:/?~\\.,><`[]{}()!@#$%^&-_+'=*\"| \t\r\n";
    public static ArrayList<TasksForMap> initialTasks = new ArrayList<>();
    public static ArrayList<TasksForReduce> tasksForReduces = new ArrayList<>();
    public static ArrayList<mapResult> mapResults= new ArrayList<>();
    public static ArrayList<finalResults> finalResults = new ArrayList<>();
    public static Semaphore semaphore = new Semaphore(1);
    public static Integer nrWorkers;

    // Function used for getting the corresponding fibonacci sequence number
    // for the length of a word
    public static Integer getFiboSequence(int size) {

        Integer first = 0;
        Integer second = 1;

        ArrayList<Integer> fiboSequence = new ArrayList<>();
        fiboSequence.add(first);
        fiboSequence.add(second);

        for (int i = 0; i < size; i++) {

            Integer nextInSeries = first + second;
            fiboSequence.add(nextInSeries);

            first = second;
            second = nextInSeries;
        }

        return fiboSequence.get(size);
    }


    public static void main(String[] args) throws IOException {

        if (args.length < 3) {
            System.err.println("Usage: Tema2 <workers> <in_file> <out_file>");
            return;
        }

        // Parse number of workers and input/output files
        nrWorkers = Integer.parseInt(args[0]);
        String inputFilePath = args[1];
        String outFilePath = args[2];

        Integer size = 0;
        Integer nrFiles = 0;
        ArrayList<String> paths = new ArrayList<>();

        // Read the fragment size and the files used for the map-reduce tasks
        BufferedReader br = new BufferedReader(new FileReader(inputFilePath));
        String line;
        line = br.readLine();
        size = Integer.parseInt(line);

        line = br.readLine();
        nrFiles = Integer.parseInt(line);

        for (int i = 0; i < nrFiles; i++) {
            line = br.readLine();
            paths.add(line);
        }

        // Store the size of every file which will processed later
        ArrayList<Integer> sizeOfFiles = new ArrayList<>();
        for (int i = 0; i < nrFiles; i++) {

            int fileLength = 0;
            String file = Files.readString(Path.of("../" + paths.get(i)));
            fileLength = file.length();

            sizeOfFiles.add(fileLength);
        }

        // Build the initial tasks for each file, taking into account
        // the given fragment size and offset
        for (int i = 0; i < nrFiles; i++) {

            br = new BufferedReader(new FileReader("../" + paths.get(i)));

            int nrChars = 0;
            int totalCharsRead = 0;
            int offset = 0;

            while (totalCharsRead < sizeOfFiles.get(i)) {
                if (nrChars == 0) {
                    offset = totalCharsRead;
                }
                br.read();
                totalCharsRead ++;
                nrChars++;

                if (nrChars == size) {
                   initialTasks.add(new TasksForMap(paths.get(i), offset, nrChars));
                   offset = offset + nrChars;
                   nrChars = 0;
                }
            }
            if(nrChars > 0) {
                initialTasks.add(new TasksForMap(paths.get(i), offset, nrChars));
            }
        }

        // Modify those initial tasks so that they contain full words
        ArrayList<Integer> toBeDeleted = new ArrayList<>();
        int fileCounter = 0;
        for(int i = 0; i < initialTasks.size() - 1; i++) {

            // For each task check the current one and the next one for a possible word
            // that may be incomplete
            if (initialTasks.get(i).fileName.equals(initialTasks.get(i + 1).fileName)) {
                BufferedReader t1 = new BufferedReader(new FileReader("../" + initialTasks.get(i).fileName));
                BufferedReader t2 = new BufferedReader(new FileReader("../" + initialTasks.get(i).fileName));

                t1.skip(initialTasks.get(i + 1).offsetOfTask - 1);
                t2.skip(initialTasks.get(i + 1).offsetOfTask);

                // Start from the last character of the first task and check for further letters
                String lastCharOfT1 = Character.toString((char) t1.read());

                int count = 0;

                if (!wordsSeparators.contains(lastCharOfT1)) {
                    String fstCharOfT2 = Character.toString((char) t2.read());

                    while (!wordsSeparators.contains(fstCharOfT2) && count != initialTasks.get(i + 1).sizeOfTask) {
                        count++;
                        fstCharOfT2 = Character.toString((char) t2.read());

                    }
                }

                initialTasks.get(i).sizeOfTask += count;
                initialTasks.get(i + 1).offsetOfTask += count;
                initialTasks.get(i+1).sizeOfTask -= count;
            } else {
                fileCounter ++;
            }

            // Check if a task was connected entirely to a previous one (needs to be deleted)
            if(initialTasks.get(i+1).offsetOfTask == sizeOfFiles.get(fileCounter)) {
                toBeDeleted.add(i+1);
            }
        }

        // Delete any empty tasks
        int delay = 0;
        for (Integer integer : toBeDeleted) {
            initialTasks.remove((int) integer - delay);
            delay ++;
        }

        // Apply the map logic on the adjusted tasks
        MapTasks[] threads = new MapTasks[nrWorkers];

        for (int i = 0; i < nrWorkers; i++) {
            threads[i] = new MapTasks(i);
        }

        for (var thread : threads) {
            thread.start();
        }

        for (var thread : threads) {

            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Build the tasks which will be processed with the reduce logic
        // by already assigning them the filename
        for (int i = 0; i < nrFiles; i++) {

            tasksForReduces.add(new TasksForReduce(paths.get(i), new ArrayList<HashMap<Integer, Integer>>(),
                    new ArrayList<ArrayList<String>>()));
        }

        // For each result from the map task store it in the corresponding
        // reduce task based on the filename
        for (int i = 0; i < mapResults.size(); i++) {

            for (int j = 0; j < tasksForReduces.size(); j++) {

                if (mapResults.get(i).fileName == tasksForReduces.get(j).filename) {

                    tasksForReduces.get(j).wordsCounter.add(mapResults.get(i).nrAppearances);
                    tasksForReduces.get(j).maximumsList.add(mapResults.get(i).maximums);
                }
            }
        }

        // Apply the reduce logic on the results obtained from the map task
        ReduceTasks[] reduceThreads = new ReduceTasks[nrWorkers];
        for (int i = 0; i < nrWorkers; i++) {
            reduceThreads[i] = new ReduceTasks(i);
        }

        for (var thread : reduceThreads) {
            thread.start();
        }

        for (var thread : reduceThreads) {

            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Sort the final results descending based on the rank
        for (int i = 0; i < finalResults.size() - 1; i++) {

            for (int j = i + 1; j < finalResults.size(); j++) {

                if (Float.parseFloat(finalResults.get(i).rank) < Float.parseFloat(finalResults.get(j).rank)) {

                    Collections.swap(finalResults, i, j);
                }
            }
        }

        // Write the final results to a file
        String finalResultStr = "";

        for (int i = 0; i < finalResults.size(); i++) {

            finalResultStr += finalResults.get(i).filename.substring(12, finalResults.get(i).filename.length());
            finalResultStr += ",";
            finalResultStr += finalResults.get(i).rank + ",";
            finalResultStr += Integer.toString(finalResults.get(i).maximumLength) + ",";
            finalResultStr += Integer.toString(finalResults.get(i).appearances);
            finalResultStr += "\n";

        }

        BufferedWriter writer = new BufferedWriter(new FileWriter(outFilePath));
        writer.write(finalResultStr);
        writer.close();
    }
}
