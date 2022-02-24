package Task1;

import java.util.ArrayList;

public class MyHashMap<Key, Value> {

    int dim;

    class HashEntry<key, value> {

        Key key;
        Value value;

        /** Clasa interna cu rol de entry **/
        public HashEntry(Key key, Value value) {
            this.key = key;
            this.value = value;
        }

        @Override
        public String toString() {
            return "HashEntry{" +
                    "key=" + key +
                    ", value=" + value +
                    '}';
        }
    }

    /** Constructor gol ce initializeaza tabela de dispersie cu 10 elemente ca default **/
    public MyHashMap() {
        this(10);
    }

    /** Constructor ce initializeaza tabela de dispersie **/
    public MyHashMap(int dim) {

        this.dim = dim;

        for (int i = 0; i < dim; i++) {
            map.add(i, new ArrayList<HashEntry<Key, Value>>());
        }
    }

    ArrayList<ArrayList<HashEntry<Key, Value>>> map = new ArrayList(dim);

    public int getIndex(Key key) {
        return key.hashCode() % dim;
    }

    /** Implementarea functiei get **/
    public Value get(Key key) {
        int index = getIndex(key);
        ArrayList<HashEntry<Key, Value>> entryList = map.get(index);

        for (HashEntry<Key, Value> entry : entryList) {
            if (entry.key.equals(key)) {
                return entry.value;
            }
        }

        return null;
    }

    /** Implementarea functiei put **/
    public void put(Key key, Value value) {

        int index = getIndex(key);
        ArrayList<HashEntry<Key, Value>> entryList = map.get(index);
        HashEntry<Key, Value> newEntry = new HashEntry<Key, Value>(key, value);
        boolean foundElement = false;

        for (HashEntry<Key, Value> entry : entryList) {
            if(entry.key.equals(newEntry.key)) {
                foundElement = true;
                entry.value = newEntry.value;
            }
        }

        if(!foundElement) {
            entryList.add(newEntry);
        }
    }

    @Override
    public String toString() {
        return "MyHashMap{" +
                "dim=" + dim +
                ", map=" + map +
                '}';
    }
}
