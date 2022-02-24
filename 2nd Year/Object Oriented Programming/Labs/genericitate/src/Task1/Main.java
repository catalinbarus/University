package Task1;

public class Main {

    @Override
    public int hashCode() {
        return super.hashCode();
    }

    /** Testarea tabelei de dispersie **/
    public static void main(String[] args) {

        MyHashMap<Integer, String> map = new MyHashMap<Integer, String>(5);

        map.put(5, "Test");
        map.put(100, "POO Test");
        map.put(55, "Another test");
        map.put(21, "Yet another test");
        map.put(98, "Test.");


        System.out.println(map);
        System.out.println(map.get(55));
        System.out.println(map.get(100));



    }
}
