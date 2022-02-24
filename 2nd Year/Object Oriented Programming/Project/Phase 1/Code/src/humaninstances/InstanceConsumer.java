package humaninstances;

/* Class used for a consumer */
public class InstanceConsumer {

    // Using a static block for the Singleton Design Pattern
    public static InstanceConsumer instance;
    static {
        instance = new InstanceConsumer();
    }


    private long id;
    private long budget;
    private long monthlyIncome;
    private boolean isBankrupt;
    private long warnings;
    private long debt;
    private long remainderMonths;
    private long currentcontract;

    public InstanceConsumer(final long id, final long budget, final long monthlyIncome,
                            final boolean isBankrupt, final long warnings, final long debt,
                            final long remainderMonths, final long currentcontract) {

        this.id = id;
        this.budget = budget;
        this.monthlyIncome = monthlyIncome;
        this.isBankrupt = isBankrupt;
        this.warnings = warnings;
        this.debt = debt;
        this.remainderMonths = remainderMonths;
        this.currentcontract = currentcontract;
    }

    public InstanceConsumer() {
        this.warnings = 0;
        this.currentcontract = 0;
        this.remainderMonths = 0;
        this.debt = 0;
        this.isBankrupt = false;
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
    public long getMonthlyIncome() {
        return monthlyIncome;
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
    public boolean isBankrupt() {
        return isBankrupt;
    }

    /**
     *
     */
    public long getWarnings() {
        return warnings;
    }

    /**
     *
     */
    public long getRemainderMonths() {
        return remainderMonths;
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
    public void setWarnings(final long warnings) {
        this.warnings = warnings;
    }

    /**
     *
     */
    public void setRemainderMonths(final long remainderMonths) {
        this.remainderMonths = remainderMonths;
    }

    /**
     *
     */
    public long getDebt() {
        return debt;
    }

    /**
     *
     */
    public void setDebt(final long debt) {
        this.debt = debt;
    }

    /**
     *
     */
    public long getCurrentcontract() {
        return currentcontract;
    }

    /**
     *
     */
    public void setCurrentcontract(long currentcontract) {
        this.currentcontract = currentcontract;
    }

    /**
     *
     */
    public void setId(final long id) {
        this.id = id;
    }


    /**
     *
     */
    public static InstanceConsumer getInstance() {
        return instance;
    }

    /**
     *
     */
    public void setMonthlyIncome(final long monthlyIncome) {
        this.monthlyIncome = monthlyIncome;
    }

    /**
     *
     */
    @Override
    public String toString() {
        return "InstanceConsumer{"
                + "id="
                + id
                + ", budget="
                + budget
                + ", monthlyIncome="
                + monthlyIncome
                + ", isBankrupt="
                + isBankrupt
                + ", warnings="
                + warnings
                + ", debt="
                + debt
                + ", remainderMonths="
                + remainderMonths
                + ", currentcontract="
                + currentcontract
                + '}';
    }
}
