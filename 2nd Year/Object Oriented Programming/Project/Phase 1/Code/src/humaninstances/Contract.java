package humaninstances;

/* Class used for a contract */
public class Contract {

    private long clientId;
    private long currentprice;
    private long remaindermonths;
    private boolean isDelayed;

    public Contract(long clientId, long currentprice, long remaindermonths, boolean isDelayed) {
        this.clientId = clientId;
        this.currentprice = currentprice;
        this.remaindermonths = remaindermonths;
        this.isDelayed = isDelayed;
    }

    /**
     *
     */
    public long getClientId() {
        return clientId;
    }

    /**
     *
     */
    public long getCurrentprice() {
        return currentprice;
    }

    /**
     *
     */
    public long getRemaindermonths() {
        return remaindermonths;
    }

    /**
     *
     */
    public void setCurrentprice(final long currentprice) {
        this.currentprice = currentprice;
    }

    /**
     *
     */
    public void setRemaindermonths(final long remaindermonths) {
        this.remaindermonths = remaindermonths;
    }

    public boolean isDelayed() {
        return isDelayed;
    }

    public void setDelayed(boolean delayed) {
        isDelayed = delayed;
    }

    @Override
    public String toString() {
        return "Contract{" +
                "clientId=" + clientId +
                ", currentprice=" + currentprice +
                ", remaindermonths=" + remaindermonths +
                ", isDelayed=" + isDelayed +
                '}';
    }
}
