
public class Array<T extends Comparable> implements MyContainer<T>
{
    protected T [] array;

    protected int capacity;

    protected int size;


    public Array(int initSize)
   {
        array = (T[]) new Comparable[initSize];
        capacity = initSize * 2;
        size = initSize;
    }


    public Array()
   {
        this(0);
    }


    public void insert(T obj)
   {
        if(size >= capacity)
       {
            allocateMore();
        }

        array[size] = obj;
        size++;
    }


    public T min()
   {
        int minIdx = getMinIdx();
        if(minIdx == -1)
       {
            return null;
        }
       else
       {
            return array[minIdx];
        }
    }


    public T removeMin()
   {
        int minIdx = getMinIdx();
        if(minIdx == -1)
       {
            return null;
        }
       else
       {
            return remove(minIdx);
        }
    }


    public int getMinIdx()
   {
        T minVal = null;
        int minIdx = -1;
        for(int idx = 0; idx < size; idx++)
       {
            if(array[idx].compareTo(minVal) < 0)
           {
                minVal = array[idx];
                minIdx = idx;
            }
        }

        return minIdx;
    }


    public T remove(int remIdx)
   {
        if(remIdx < 0 || remIdx >= size)
       {
            return null;
        }

        if(size * 4 < capacity)
       {
            allocateLess();
        }

        T res = array[remIdx];
        pushLeft(remIdx);
        return res;
    }

    public int getSize()
   {
        return size;
    }

    public boolean isEmpty()
   {
        return size == 0;
    }

    public T get(int idx)
   {
        if(idx < 0 || idx >= size)
       {
            return null;
        }

        return array[idx];
    }


    public int find(T obj)
   {
        int res = -1;
        for(int idx = 0; idx < size; idx++)
       {
            if(array[idx].equals(obj))
           {
                res = idx;
                break;
            }
        }

        return res;
    }


    protected void allocateMore()
   {
        if(capacity == 0)
       {
            capacity = 2;
        }
       else
       {
            capacity += capacity;
        }


        T [] newArr = (T[]) new Comparable[capacity];
        copyElements(newArr);

        array = newArr;
    }


    protected void allocateLess()
   {
        if(capacity < 2 )
       {
            return;
        }


        capacity /= 2;
        T [] newArr = (T[]) new Comparable[capacity];
        copyElements(newArr);

        array = newArr;

    }


    protected void copyElements(T[] dst) {
        for(int i = 0; i < size; i++) {
            dst[i] = array[i];
        }
    }


    protected void pushLeft(int leftIdx) {
        for(int idx = leftIdx + 1; idx < size; idx++) {
            array[idx - 1] = array[idx];
        }

        size--;
    }


    protected void pushRight(int rightIdx)
   {
        T prevVal = array[rightIdx];
        for(int idx = rightIdx; idx < size; idx++)
       {
            T nextVal = array[idx + 1];
            array[idx + 1] = prevVal;
            prevVal = nextVal;
        }

        size++;
    }


	public int compareTo(Object o) {

		return 0;
	}
}