import java.util.Random;

public class Entry {
    private int key;
    private String value;

    public Entry(int k, String  val){
        key = k;
        value = val;
    }

    public Entry(int k){
        Random random = new Random();
        key = k;
        this.value = random.ints(97, 123).limit(7).collect(StringBuilder::new, StringBuilder::appendCodePoint, StringBuilder::append).toString();
    }


    public Entry(String val){
        Random random = new Random();
        this.key = random.nextInt(5000) + 1;
        value = val;
    }


    public Entry(){
        Random rand = new Random();
        this.key = rand.nextInt(5000) + 1;
        this.value = rand.ints(97, 123).limit(7).collect(StringBuilder::new, StringBuilder::appendCodePoint, StringBuilder::append).toString();
    }


    public static int hashCode(int k){
        int h = 0;
        String temp = Integer.toString(k);
        int[] arr = new int[temp.length()];
        for (int i = 0; i < temp.length(); i++)
        {
            arr[i] = temp.charAt(i) - '0';
        }
        int f = 1;
        for (int i = 0; i < arr.length; i++){
            h += f * arr[i];
            f *= 7;
        }
        return h;
    }

    public void setValue(String  val) {
        value = val;
    }

    public int getKey() {
        return this.key;
    }

    public String getValue() {
        return this.value;
    }
}
