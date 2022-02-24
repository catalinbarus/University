package displayinstances;

/* Class used for displaying the final status of the contracts */
public class FinalContracts {

    private long consumerId;
    private long price;
    private long remainedContractMonths;

    public FinalContracts(final long consumerId, final long price,
                          final long remainedContractMonths) {
        this.consumerId = consumerId;
        this.price = price;
        this.remainedContractMonths = remainedContractMonths;
    }

    public FinalContracts() {

    }


    /**
     *
     */
    public long getConsumerId() {
        return consumerId;
    }

    /**
     *
     */
    public long getPrice() {
        return price;
    }

    /**
     *
     */
    public long getRemainedContractMonths() {
        return remainedContractMonths;
    }

    @Override
    public String toString() {
        return "FinalContracts{"
                + "consumerId="
                + consumerId
                + ", price="
                + price
                + ", remainedContractMonths="
                + remainedContractMonths
                + '}';
    }
}
