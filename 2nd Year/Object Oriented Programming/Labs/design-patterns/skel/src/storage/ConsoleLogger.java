package storage;

import communication.ServerMessage;

import java.util.Observable;
import java.util.Observer;

public class ConsoleLogger implements Observer {
    private SensorData dataRecord;

    @Override
    public void update(Observable o, Object data) {
        this.dataRecord = (SensorData) data;
    }

    public void getData() {
        System.out.println("#Logger - Data was added to repo: " + dataRecord);
    }
}
