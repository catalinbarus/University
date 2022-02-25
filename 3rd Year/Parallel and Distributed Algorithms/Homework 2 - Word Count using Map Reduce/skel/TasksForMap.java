public class TasksForMap {

    public String fileName;
    public Integer offsetOfTask;
    public Integer sizeOfTask;

    public TasksForMap(String fileName, Integer offsetOfTask, Integer sizeOfTask) {
        this.fileName = fileName;
        this.offsetOfTask = offsetOfTask;
        this.sizeOfTask = sizeOfTask;
    }

    @Override
    public String toString() {
        return "Task{" +
                "fileName='" + fileName + '\'' +
                ", offsetOfTask=" + offsetOfTask +
                ", sizeOfTask=" + sizeOfTask +
                '}';
    }
}
