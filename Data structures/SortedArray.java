
public class SortedArray<T extends Comparable> extends Array<T>
{
 
    public SortedArray(int initSize)
   {
        super(initSize);
    }

 
    public SortedArray()
   {
        super();
    }


    @Override
    public void insert(T obj)
   {
        // try to insert in a way where the smallest element is at the end
        if(size >= capacity)
       {
            allocateMore();
        }

        int insIdx = size;
        // array is in descending order, so scan for next largest element
        // from right to left
        for(int idx = size - 1; idx >= 0; idx--, insIdx--)
       {
            if(array[idx].compareTo(obj) > 0)
           {
                // found element bigger. therefore, should go here
                break;
            }
        }

        pushRight(insIdx);
        array[insIdx] = obj;
    }


    public int getMinIdx()
   {
        return size - 1;
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
}