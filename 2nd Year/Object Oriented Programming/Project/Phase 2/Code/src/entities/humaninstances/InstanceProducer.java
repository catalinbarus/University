package entities.humaninstances;

public class InstanceProducer {

    private long id;
    private String energyType;
    private long maxDistributors;
    private double priceKW;
    private long energyPerDistributor;
    private boolean isRenewable;
    private long distributorCapacity;

    /**
     *
     */
    public InstanceProducer(final long id, final String energyType, final long maxDistributors,
                            final double priceKW, final long energyPerDistributor,
                            final boolean isRenewable, final long distributorCapacity) {
        this.id = id;
        this.energyType = energyType;
        this.maxDistributors = maxDistributors;
        this.priceKW = priceKW;
        this.energyPerDistributor = energyPerDistributor;
        this.isRenewable = isRenewable;
        this.distributorCapacity = distributorCapacity;
    }

    /**
     *
     */
    public InstanceProducer() {
        this.priceKW = 0.00;
        this.energyPerDistributor = 0;
        this.isRenewable = false;
        this.distributorCapacity = 0;
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
    public String getEnergyType() {
        return energyType;
    }

    /**
     *
     */
    public long getMaxDistributors() {
        return maxDistributors;
    }

    /**
     *
     */
    public double getPriceKW() {
        return priceKW;
    }

    /**
     *
     */
    public long getEnergyPerDistributor() {
        return energyPerDistributor;
    }

    /**
     *
     */
    public boolean isRenewable() {
        return isRenewable;
    }

    /**
     *
     */
    public long getDistributorCapacity() {
        return distributorCapacity;
    }

    @Override
    public String toString() {
        return "InstanceProducer{"
                + "id="
                + id
                + ", energyType='"
                + energyType
                + '\''
                + ", maxDistributors="
                + maxDistributors
                + ", priceKW="
                + priceKW
                + ", energyPerDistributor="
                + energyPerDistributor
                + ", isRenewable="
                + isRenewable
                + ", distributorCapacity="
                + distributorCapacity
                + '}';
    }
}
