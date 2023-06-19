
public abstract class MyPQ<K extends Comparable, V>
{
    protected MyContainer<Pairs<K, V>> container;

    public void insert(K key, V val)
   {
        container.insert(new Pairs(key, val));
    }


    public Pairs<K, V> min()
   {
        return container.min();
    }


    public Pairs<K, V> removeMin()
   {
        return container.removeMin();
    }

    public int size()
   {
        return container.getSize();
    }

    public boolean isEmpty()
   {
        return container.isEmpty();
    }
}