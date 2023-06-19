import java.util.ArrayList;

public class HashMapDriver {

    public static void main(String[] args){
        experimentinterpret();
    }

    public static void validate(){
        ArrayList<Entry> entriesAL= new ArrayList<Entry>();
        int entryNum = 50;
        for (int i = 0; i < entryNum; i ++){
            entriesAL.add(new Entry());}
        MyHashMap hashMap = new MyHashMap(100);
        for (int i = 0; i < entriesAL.size(); i ++){
            hashMap.put(entriesAL.get(i).getKey(), entriesAL.get(i).getValue());}
        for (int i = 0; i < entriesAL.size(); i ++){
            hashMap.get(entriesAL.get(i).getKey());}
        for (int i = 0; i < 25; i ++){
            hashMap.remove(entriesAL.get(i).getKey());}
        for (int i = 0; i < entriesAL.size(); i ++){
            hashMap.get(entriesAL.get(i).getKey());}
    }

    public static void experimentinterpret(){
        MyHashMap hashMap = new MyHashMap(100);
        int entryNum = 150;
        ArrayList<Entry> entriesAL= new ArrayList<Entry>();
        for (int i = 0; i < entryNum; i ++){
            entriesAL.add(new Entry());
        }
        for (int i = 0; i < entriesAL.size(); i++){
            hashMap.put(entriesAL.get(i).getKey(), entriesAL.get(i).getValue());
        }
    }
}
