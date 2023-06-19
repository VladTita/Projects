
public interface MyContainer<T> extends Comparable
{

    public void insert(T obj);


    public int getSize();


    public boolean isEmpty();


    public T remove(int remIdx);


    public T get(int idx);


    public int find(T obj);


    public T min();


    public T removeMin();
}