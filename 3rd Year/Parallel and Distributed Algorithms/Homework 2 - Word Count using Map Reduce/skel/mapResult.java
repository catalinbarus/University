import java.util.ArrayList;
import java.util.HashMap;

public class mapResult {
    public String fileName;
    public HashMap<Integer, Integer> nrAppearances;
    public ArrayList<String> maximums;

    @Override
    public String toString() {
        return "mapResult{" +
                "fileName='" + fileName + '\'' +
                ", nrAppearances=" + nrAppearances +
                ", maximums=" + maximums +
                '}';
    }

    public mapResult(String fileName, HashMap<Integer, Integer> nrAppearances, ArrayList<String> maximums) {
        this.fileName = fileName;
        this.nrAppearances = nrAppearances;
        this.maximums = maximums;
    }
}
