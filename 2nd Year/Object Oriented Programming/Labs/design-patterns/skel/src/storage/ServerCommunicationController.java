package storage;

import java.util.Observable;
import java.util.Observer;
import communication.*;
import main.Utils;

public class ServerCommunicationController implements Observer {

    SensorData dataRecord;
    int id = 1;

    @Override
    public void update(Observable o, Object data) {
        this.dataRecord = (SensorData) data;
    }

    public void getData() {
        ServerMessage message
                = new ServerMessage(dataRecord.getStepsCount(), Utils.getClientId(), dataRecord.getTimestamp());

        System.out.println(message);
    }
}
