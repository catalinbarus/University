package humaninstances;

import java.util.ArrayList;

/* Class used for keeping the monthly updates */
public class MonthlyTurnUpdates {

    private ArrayList<InstanceConsumer> newconsumers;
    private ArrayList<InstanceDistributor> distributorchanges;

    public MonthlyTurnUpdates(final ArrayList<InstanceConsumer> newconsumers,
                              final ArrayList<InstanceDistributor> distributorchanges) {
        this.newconsumers = newconsumers;
        this.distributorchanges = distributorchanges;
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

    @Override
    public String toString() {
        return "MonthlyTurnUpdates{"
                + "newconsumers="
                + newconsumers
                + ", distributorchanges="
                + distributorchanges
                + '}';
    }
}
