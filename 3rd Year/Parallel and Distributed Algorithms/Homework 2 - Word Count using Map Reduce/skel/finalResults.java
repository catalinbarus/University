public class finalResults {

    public String filename;
    public String rank;
    public Integer maximumLength;
    public Integer appearances;

    public finalResults(String filename, String rank, Integer maximumLength, Integer appearances) {
        this.filename = filename;
        this.rank = rank;
        this.maximumLength = maximumLength;
        this.appearances = appearances;
    }

    @Override
    public String toString() {
        return "finalResults{" +
                "filename='" + filename + '\'' +
                ", rank=" + rank +
                ", maximumLength=" + maximumLength +
                ", appearances=" + appearances +
                '}';
    }
}
