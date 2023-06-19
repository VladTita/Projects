
public class MyPQSortedList<K extends Comparable, V> extends MyPQ<K, V>
{
    public MyPQSortedList()
   {
        container = new SortedLinkedList<Pairs<K, V>>();
    }
}