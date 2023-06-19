public class LinkedList<T extends Comparable> implements MyContainer<T>
{
    protected Node head;
    protected int size;

    public LinkedList()
   {
        head = null;
        size = 0;
    }


    public void insert(T obj)
   {
        // because it's unsorted just insert at the head
        head = new Node(obj, null, head);
        size++;
    }


    public int getSize()
   {
        return size;
    }

  
    public boolean isEmpty()
   {
        return size == 0;
    }


    public T remove(int idx)
   {
        Node found = moveTo(idx);
        return removeNode(found);
    }


    public T removeNode(Node node)
   {
        T res = null;
        if(node != null)
       {
            if(head == node)
           {
                // update head node first
                head = head.next;
            }

            // now remove node and adjust size
            res = node.data;
            node.remove();
            size--;

        }

        return res;
    }


    public T get(int idx)
   {
        Node found = moveTo(idx);
        T res = null;
        if(found != null)
       {
            res = found.data;
        }

        return res;
    }


    public int find(T obj)
   {
        int res = -1;
        Node curr = head;
        for(int idx = 0; idx < size; idx++, curr = curr.next)
       {
            if(curr.data.equals(obj))
           {
                res = idx;
                break;
            }
        }

        return res;
    }


    public T min()
   {
        Node minNode = getMinNode();
        T res = null;
        if(minNode != null)
       {
            res = minNode.data;
        }

        return res;
    }

 
    public T removeMin()
   {
        Node minNode = getMinNode();
        return removeNode(minNode);
    }


    protected Node getMinNode()
   {
        if(head == null)
       {
            return null;
        }

        Node minNode = head;
        T minVal = head.data;
        Node curr = head.next;
        while(curr != null)
       {
            if(curr.data.compareTo(minVal) < 0)
           {
                minVal = curr.data;
                minNode = curr;
            }

            curr = curr.next;
        }

        return minNode;
    }


    protected Node moveTo(int idx)
   {
        if(idx < 0 || idx >= size)
       {
            return null;
        }

        Node curr = head;
        for(; idx > 0; idx--)
       {
            curr = curr.next;
        }

        return curr;
    }

    protected class Node
   {
        T data;
        Node next;
        Node prev;


        public Node(T newData, Node left, Node right)
       {
            data = newData;
            next = right;
            if(right != null)
           {
                right.prev = this;
            }

            prev = left;
            if(left != null)
           {
                left.next = this;
            }
        }

        public Node(T newData)
       {
            this(newData, null, null);
        }


        public void remove()
       {
            if(next != null)
           {
                next.prev = prev;
            }

            if(prev != null)
           {
                prev.next = next;
            }
        }
    }

	public int compareTo(Object o) {

		return 0;
	}
}