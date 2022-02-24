package entities.humaninstances;

import java.util.ArrayList;

/* Class used for keeping the monthly updates */
public class MonthlyTurnUpdates {

    private ArrayList<InstanceConsumer> newconsumers;
    private ArrayList<InstanceDistributor> distributorchanges;
    private ArrayList<InstanceProducer> producerchanges;

    public MonthlyTurnUpdates(final ArrayList<InstanceConsumer> newconsumers,
                              final ArrayList<InstanceDistributor> distributorchanges,
                              final ArrayList<InstanceProducer> producerchanges) {
        this.newconsumers = newconsumers;
        this.distributorchanges = distributorchanges;
        this.producerchanges = producerchanges;
    }

    /**
     *
     */
    public ArrayList<InstanceConsumer> getNewconsumers() {
        return newconsumers;
    }

    /**
     *
     */
    public ArrayList<InstanceDistributor> getDistributorchanges() {
        return distributorchanges;
    }

    /**
     *
     * @return
     */
    public ArrayList<InstanceProducer> getProducerchanges() {
        return producerchanges;
    }

    @Override
    public String toString() {
        return "MonthlyTurnUpdates{"
                + "newconsumers="
                + newconsumers
                + ", distributorchanges="
                + distributorchanges
                + ", producerchanges="
                + producerchanges
                + '}';
    }
}

