package displayinstances;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;
import humaninstances.InstanceConsumer;

/* Class used for displaying the final status of the clients */
@JsonPropertyOrder({ "id", "isBankrupt", "budget"})
public class FinalConsumers {

    private long id;
    private boolean isBankrupt;
    private long budget;

    public FinalConsumers(final long id, final boolean isBankrupt, final long budget) {
        this.id = id;
        this.isBankrupt = isBankrupt;
        this.budget = budget;
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
    @JsonProperty("isBankrupt")
    public boolean isBankrupt() {
        return isBankrupt;
    }

    /**
     *
     */
    public long getBudget() {
        return budget;
    }

    @Override
    public String toString() {
        return "FinalConsumers{"
                + "id="
                + id
                + ", isBankrupt="
                + isBankrupt
                + ", budget="
                + budget
                + '}';
    }
}
