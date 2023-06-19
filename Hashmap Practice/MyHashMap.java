public class MyHashMap extends AbsHashMap {
    int collisions = 0;
    
    public MyHashMap(int cap) {
        super(cap); }

    @Override
    int size() {
        return this.entryNum; }

    @Override
    boolean isEmpty() {
        return this.entryNum != 0; }

    @Override
    String get(int k) {
        long start = System.nanoTime();
        long end,total;
        int index = hashFunction(Entry.hashCode(k));
        for (int i = 0; i < bucketsAL[index].size(); i++){
            if (bucketsAL[index].get(i).getKey() == k){
                end   = System.nanoTime();
                total = end - start;
                System.out.println("Runtime for method get: "+total+" nanoseconds");
                return bucketsAL[index].get(i).getValue();
            }
        }
        end   = System.nanoTime();
        total = end - start;
        System.out.println("Runtime for method get: "+total+" nanoseconds");
        return null;
    }

    @Override
    String put(int k, String v) {
        long start = System.nanoTime();
        long end, total;
        int index = hashFunction(Entry.hashCode(k));
        System.out.println("Index for "+k+": "+index);
        for (int i = 0; i < bucketsAL[index].size(); i++){
            if (bucketsAL[index].get(i).getKey() == k){
                String oldV = bucketsAL[index].get(i).getValue();
                bucketsAL[index].get(i).setValue(v);
                System.out.println("\nSize: "+this.cap+"\nNum of elements: "+this.size()+"\nCollisions: "+collisions+"\nNum of elements in bucket");
                end   = System.nanoTime();
                total = end - start;
                System.out.println("Runtime for method put: "+total+" nanoseconds");
                return oldV;
            } else {
                collisions++;
            }
        }
        bucketsAL[index].add(new Entry(k, v));
        this.entryNum++;
        System.out.println("\nSize: "+this.cap+"\nNum of elements: "+this.size()+"\nCollisions: "+collisions+"\nNum of elements in bucket: "+bucketsAL[index].size());
        end   = System.nanoTime();
        total = end - start;
        System.out.println("Runtime for method put: "+total+" nanoseconds");
        return null;
    }

    @Override
    String remove(int k) {
        long start = System.nanoTime();
        long end,total;
        int index = hashFunction(Entry.hashCode(k));
        System.out.println(index);
        for (int i = 0; i < bucketsAL[index].size(); i++){
            if (bucketsAL[index].get(i).getKey() == k){
                String removedEntryValue = bucketsAL[index].get(i).getValue();
                bucketsAL[index].remove(bucketsAL[index].get(i));
                end   = System.nanoTime();
                total = end - start;
                System.out.println("Runtime for method remove: "+total+" nanoseconds");
                return removedEntryValue;
            }
        }

        end   = System.nanoTime();
        total = end - start;
        System.out.println("Runtime for method remove: "+total+" nanoseconds");
        return null;
    }
}
