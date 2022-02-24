package entities.displayinstances;

import java.util.ArrayList;

/* Class used for displaying the final status of the print format */
public class FinalPrint {

    private ArrayList<FinalConsumers> consumers;
    private ArrayList<FinalDistributors> distributors;

    public FinalPrint(final ArrayList<FinalConsumers> consumers,
                      final ArrayList<FinalDistributors> distributors) {
        this.consumers = consumers;
        this.distributors = distributors;
    }

    /**
     *
     */
    public ArrayList<FinalConsumers> getConsumers() {
        return consumers;
    }

    /**
     *
     */
    public ArrayList<FinalDistributors> getDistributors() {
        return distributors;
    }
}

