package fileloader;

import entities.humaninstances.InstanceConsumer;
import entities.humaninstances.InstanceDistributor;
import entities.humaninstances.InstanceProducer;
import entities.humaninstances.MonthlyTurnUpdates;

import java.util.ArrayList;


/* Class used for parsing the json data */
public class Data {

    private final long numOfTurns;
    private final ArrayList<InstanceConsumer> inputconsumers;
    private final ArrayList<InstanceDistributor> inputdistributors;
    private final ArrayList<InstanceProducer> inputproducers;
    private final ArrayList<MonthlyTurnUpdates> inputmonthlyupdates;

    public Data(final long numOfTurns, final ArrayList<InstanceConsumer> inputconsumers,
                final ArrayList<InstanceDistributor> inputdistributors,
                final ArrayList<InstanceProducer> inputproducers,
                final ArrayList<MonthlyTurnUpdates> inputmonthlyupdates) {

        this.numOfTurns = numOfTurns;
        this.inputconsumers = inputconsumers;
        this.inputdistributors = inputdistributors;
        this.inputproducers = inputproducers;
        this.inputmonthlyupdates = inputmonthlyupdates;
    }

    /**
     *
     */
    public long getNumOfTurns() {
        return numOfTurns;
    }

    /**
     *
     */
    public ArrayList<InstanceConsumer> getInputconsumers() {
        return inputconsumers;
    }

    /**
     *
     */
    public ArrayList<InstanceDistributor> getInputdistributors() {
        return inputdistributors;
    }

    /**
     *
     */
    public ArrayList<InstanceProducer> getInputproducers() {
        return inputproducers;
    }

    /**
     *
     */
    public ArrayList<MonthlyTurnUpdates> getInputmonthlyupdates() {
        return inputmonthlyupdates;
    }
}
