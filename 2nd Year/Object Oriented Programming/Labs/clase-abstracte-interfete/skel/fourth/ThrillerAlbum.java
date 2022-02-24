package fourth;

public class ThrillerAlbum extends Album {

    /** Implementarea metodei abstracte addSong. **/
    public void addSong(Song song) {
        if(song.composer == "Michael Jackson" && song.id %2 == 0) {
            this.songs.add(song);
        }
    }
}
