package dataprocessing;

import main.Utils;
import storage.DataRepository;

public class StepCountStrategyFactory {

    public static StepCountStrategy createStrategy(String strategyType,
                                                DataRepository dataRepository) {
        if (strategyType.equals(Utils.BASIC_STRATEGY)) {
            return new BasicStepCountStrategy(dataRepository);
        }

        if (strategyType.equals(Utils.FILTERED_STRATEGY)) {
            return new FilteredStepCountStrategy(dataRepository);
        }

        return null;
    }
}
