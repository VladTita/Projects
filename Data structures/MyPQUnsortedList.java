
public class MyPQUnsortedList<K extends Comparable, V> extends MyPQ<K, V>
{
    public MyPQUnsortedList()
   {
        container = new LinkedList<Pairs<K, V>>();
    }
}