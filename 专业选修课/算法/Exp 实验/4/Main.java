import java.util.*;

public class Main {
    public static void main(String[] args) {
        FileRead in = new FileRead(args[0]);
        String s = in.data();
        System.out.println(s);
        Search vs = new ViolenceSearch();
        Search bs = new BinarySearch(s);
        Scanner sin = new Scanner(System.in);
        while (sin.hasNext()) {
            String w = sin.nextLine();
            System.out.println("violence:"+vs.search(s, w));
            System.out.println("binary:"+bs.search(s,w));
        }
    }
}
