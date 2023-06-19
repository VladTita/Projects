
public class SortedLinkedList<T extends Comparable> extends LinkedList<T>
{
    public SortedLinkedList()
   {
        super();
    }


    public void insert(T obj)
   {
        if(head == null || obj.compareTo(head.data) < 0)
       {
            head = new Node(obj, null, head);
        }
       else
       {
            // Walk list s.t we get the first element > obj then
            // insert
            Node curr = head.next, prev = head;
            while(curr != null && curr.data.compareTo(obj) <= 0)
           {
                prev = curr;
                curr = curr.next;
            }

            // insert in a way where
            // prev -> new node -> curr
            // guaranteed that new node isn't at head based on first statement
            new Node(obj, prev, curr);
        }

        size++;
    }


    public Node getMinNode()
   {
        return head;
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
}