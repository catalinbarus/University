package fourth;

public class DangerousAlbum extends Album {

    /** Metoda ce verifica daca un numar este prim. **/
    boolean prime(int n) {
        if(n < 2) return false;

        for(int i = 2; i*i <= n; i++)
        {
            if(n % i == 0) return false;
        }

        return true;
    }

    /** Implementarea metodei abstracte addSong. **/
    public void addSong(Song song) {
        if(prime(song.id) == true) {
            this.songs.add(song);
        }
    }
}
