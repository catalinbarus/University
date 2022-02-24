package fourth;

import java.util.ArrayList;

public abstract class Album {

    ArrayList<Song> songs = new ArrayList();

    /** Metoda abstracta implementata in clasele aferente. **/
    abstract void addSong(Song song);

    /** Metode neabstracte. **/
    void removeSong(Song song) {
        this.songs.remove(song);
    }

    @Override
    public String toString() {
        return "Album{" +
                "songs=" + songs +
                '}';
    }
}
