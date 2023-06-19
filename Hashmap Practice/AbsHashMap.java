import java.lang.reflect.Array;
import java.util.ArrayList;

public abstract class AbsHashMap {
    int cap;
    int entryNum;
    ArrayList<Entry>[] bucketsAL;
    public AbsHashMap(int cap) {
        this.cap = cap;
        bucketsAL = new ArrayList[cap];
        for (int i = 0; i < cap; i++) {
            bucketsAL[i] = new ArrayList<Entry>();
        }
    }

    public int hashFunction(int k){
        return k % this.cap;
    }

    abstract String get(int k);

    abstract String put(int k, String v);

    abstract String remove(int k);

    abstract int size();

    abstract boolean isEmpty();



}
