package storage;


import java.util.ArrayList;
import java.util.Observable;

/**
 * Persists sensor data. Observable, its observers are notified when data is added it to.
 */
public class DataRepository extends Observable { // TODO make this an Observable

    ArrayList<SensorData> data = new ArrayList<SensorData>();

    public void addData(SensorData dataRecord){
        // TODO
        // store data (e.g. in a List)
        // notifiy observers
        setChanged();
        data.add(dataRecord);
        notifyObservers(dataRecord);
    }

    // TODO implement a method to get the stored data (needed by the strategies)

    public ArrayList<SensorData> getData() {
        return data;
    }
}


