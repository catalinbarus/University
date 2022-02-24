package storage;

import dataprocessing.StepCountStrategy;

import java.util.Observable;
import java.util.Observer;

public class DataAggregator implements Observer {

    private SensorData dataRecord;
    private StepCountStrategy strategy;

    public DataAggregator(StepCountStrategy strategy) {
        this.strategy = strategy;
    }

    public void showData() {
        System.out.println(this.strategy.getStrategyDescription()
                + this.strategy.getTotalSteps()
                + " steps");
    }

    @Override
    public void update(Observable o, Object data) {
        this.dataRecord = (SensorData) data;
    }



}
