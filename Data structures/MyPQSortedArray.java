
public class MyPQSortedArray<K extends Comparable, V> extends MyPQ<K, V>
{
    // Simple - just substitute in for the container an Array
    public MyPQSortedArray(int initSize)
   {
        container = new SortedArray<Pairs<K, V>>(initSize);
    }

    public MyPQSortedArray()
   {
        this(0);
    }
}