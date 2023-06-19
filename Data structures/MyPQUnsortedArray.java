
public class MyPQUnsortedArray<K extends Comparable, V> extends MyPQ<K, V>
{
    // Simple - just substitute in for the container an Array

    public MyPQUnsortedArray(int initSize)
   {
        container = new Array<Pairs<K, V>>(initSize);
    }

    public MyPQUnsortedArray()
   {
        this(0);
    }
}