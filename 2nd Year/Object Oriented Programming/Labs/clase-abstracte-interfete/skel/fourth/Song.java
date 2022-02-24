package fourth;

public class Song {

    String name;
    int id;
    String composer;

    @Override
    public String toString() {
        return "Song{" +
                "name='" + name + '\'' +
                ", id=" + id +
                ", composer='" + composer + '\'' +
                '}';
    }


    /** Constructor ce initializeaza un cantec. **/
    public Song(String name, int id, String composer) {
        this.name = name;
        this.id = id;
        this.composer = composer;
    }
}
