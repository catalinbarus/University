package entities.humaninstances;

import java.util.ArrayList;

/* Class used for a distributor */
public class InstanceDistributor {

    // Using a static block for the Singleton Design Pattern
    public static InstanceDistributor instance;
    static {
        instance = new InstanceDistributor();
    }

    private long id;
    private long contractLength;
    private long budget;
    private long infrastructureCost;
    private long productionCost;
    private long contractprice;
    private boolean isBankrupt;
    private ArrayList<Contract> contracts;
    private String producerStrategy;
    private long energyNeededKW;

    public InstanceDistributor(final long id, final long contractLength, final long budget,
                               final long infrastructureCost, final long productionCost,
                               final long contractprice, final boolean isBankrupt,
                               final ArrayList<Contract> contracts, final String producerStrategy,
                               final long energyNeededKW) {

        this.id = id;
        this.contractLength = contractLength;
        this.budget = budget;
        this.infrastructureCost = infrastructureCost;
        this.productionCost = productionCost;
        this.contractprice = contractprice;
        this.isBankrupt = isBankrupt;
        this.contracts = contracts;
        this.producerStrategy = producerStrategy;
        this.energyNeededKW = energyNeededKW;
    }

    public InstanceDistributor() {

        this.id = 0;
        this.contractLength = 0;
        this.budget = 0;
        this.infrastructureCost = 0;
        this.productionCost = 0;
        this.contractprice = 0;
        this.isBankrupt = false;
        this.contracts = null;
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
    public long getContractLength() {
        return contractLength;
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
    public long getInfrastructureCost() {
        return infrastructureCost;
    }

    /**
     *
     */
    public long getProductionCost() {
        return productionCost;
    }

    /**
     *
     */
    public ArrayList<Contract> getContracts() {
        return contracts;
    }

    /**
     *
     */
    public long getContractprice() {
        return contractprice;
    }

    /**
     *
     */
    public void setContractprice(final long contractprice) {
        this.contractprice = contractprice;
    }

    /**
     *
     */
    public void setBudget(final long budget) {
        this.budget = budget;
    }

    /**
     *
     */
    public void setInfrastructureCost(final long infrastructureCost) {
        this.infrastructureCost = infrastructureCost;
    }

    /**
     *
     */
    public void setProductionCost(final long productionCost) {
        this.productionCost = productionCost;
    }

    /**
     *
     */
    public boolean isBankrupt() {
        return isBankrupt;
    }

    /**
     *
     */
    public void setBankrupt(final boolean bankrupt) {
        isBankrupt = bankrupt;
    }

    /**
     *
     */
    public static InstanceDistributor getInstance() {
        return instance;
    }

    /**
     *
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     *
     */
    public void setContractLength(long contractLength) {
        this.contractLength = contractLength;
    }

    /**
     *
     */
    public void setContracts(ArrayList<Contract> contracts) {
        this.contracts = contracts;
    }

    /**
     *
     */
    public void setProducerStrategy(String producerStrategy) {
        this.producerStrategy = producerStrategy;
    }

    /**
     *
     */
    public void setEnergyNeededKW(long energyNeededKW) {
        this.energyNeededKW = energyNeededKW;
    }

    /**
     *
     */
    public String getProducerStrategy() {
        return producerStrategy;
    }

    /**
     *
     */
    public long getEnergyNeededKW() {
        return energyNeededKW;
    }

    @Override
    public String toString() {
        return "InstanceDistributor{"
                + "id="
                + id
                + ", contractLength="
                + contractLength
                + ", budget="
                + budget
                + ", infrastructureCost="
                + infrastructureCost
                + ", productionCost="
                + productionCost
                + ", contractprice="
                + contractprice
                + ", isBankrupt="
                + isBankrupt
                + ", contracts="
                + contracts
                + ", producerStrategy='"
                + producerStrategy
                + '\''
                + ", energyNeededKW="
                + energyNeededKW
                + '}';
    }
}

