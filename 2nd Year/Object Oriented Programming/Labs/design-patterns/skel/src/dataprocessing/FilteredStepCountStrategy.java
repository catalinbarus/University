package dataprocessing;

import storage.DataRepository;
import storage.SensorData;
import java.util.concurrent.TimeUnit;

public class FilteredStepCountStrategy implements StepCountStrategy {

    DataRepository repo = new DataRepository();
    private static final int MAX_DIFF_STEPS_CONSECUTIVE_RECORDS = 1000;
    private static final long TIME_FOR_MAX_DIFF = TimeUnit.SECONDS.toMillis(1);

    public FilteredStepCountStrategy(DataRepository repo) {
        this.repo = repo;
    }


    @Override
    public int getTotalSteps() {
        int sum = 0;
        for (SensorData data : repo.getData()) {
            if (data.getStepsCount() > 0
                    && (data.getStepsCount() < MAX_DIFF_STEPS_CONSECUTIVE_RECORDS
                    && data.getTimestamp() > TIME_FOR_MAX_DIFF)) {
                sum = sum + data.getStepsCount();
            }
        }

        return sum;
    }

    @Override
    public String getStrategyDescription() {
        return "Filtered Strategy: ";
    }
}
