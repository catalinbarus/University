package dataprocessing;

import storage.DataRepository;
import storage.SensorData;

public class BasicStepCountStrategy implements StepCountStrategy {

    DataRepository repo = new DataRepository();

    public BasicStepCountStrategy(DataRepository repo) {
        this.repo = repo;
    }

    @Override
    public int getTotalSteps() {
        int sum = 0;
        for (SensorData data : repo.getData()) {
            sum = sum + data.getStepsCount();
        }

        return sum;
    }

    @Override
    public String getStrategyDescription() {
        return "Basic Strategy: ";
    }

}
