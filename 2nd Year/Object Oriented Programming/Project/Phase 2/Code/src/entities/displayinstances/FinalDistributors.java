package entities.displayinstances;

import java.util.ArrayList;

/* Class used for displaying the final status of the distributors */
public class FinalDistributors {

    private long id;
    private long budget;
    private boolean isBankrupt;
    private ArrayList<FinalContracts> contracts;

    public FinalDistributors(final long id, final long budget, final boolean isBankrupt,
                             final ArrayList<FinalContracts> contracts) {

        this.id = id;
        this.budget = budget;
        this.isBankrupt = isBankrupt;
        this.contracts = contracts;
    }

    /**
     *
     */
    public long getId() {
        return id;
    }

    /**
     *
     */
    public long getBudget() {
        return budget;
    }

    /**
     *
     */
    public boolean getIsBankrupt() {
        return isBankrupt;
    }

    /**
     *
     */
    public ArrayList<FinalContracts> getContracts() {
        return contracts;
    }

    @Override
    public String toString() {
        return "FinalDistributors{"
                + "id="
                + id
                + ", budget="
                + budget
                + ", isBankrupt="
                + isBankrupt
                + ", contracts="
                + contracts
                + '}';
    }
}
