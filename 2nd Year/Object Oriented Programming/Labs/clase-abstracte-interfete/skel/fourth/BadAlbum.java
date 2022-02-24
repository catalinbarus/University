package fourth;

public class BadAlbum extends Album {

    /** Metoda ce verifica daca un numar este palindrom. **/
    boolean palindrome(int n) {

        int copy = n;
        int reverse = 0;

        while(n != 0) {
            reverse = reverse * 10 + n % 10;
            n = n / 10;
        }

        if(reverse == copy) return true;
        return false;
    }


    /** Implementarea metodei abstracte addSong. **/
    public void addSong(Song song) {
        if(palindrome(song.id) == true && song.name.length() == 3) {
            this.songs.add(song);
        }

    }
}
