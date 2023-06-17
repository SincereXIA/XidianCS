import java.util.*;

public class ViolenceSearch implements Search {
    public int search(String x, String y) {
        ArrayList<String> ysplit = new ArrayList<>();
        int prepos = 0;
        for (int i = 0; i < y.length(); i++) {
            if (y.charAt(i) == ' ' || y.charAt(i) == '\n' || y.charAt(i) == 13) {
                ysplit.add(y.substring(prepos, i));
                prepos = i + 1;
            }
        }
        if (prepos + 1 < y.length()) {
            ysplit.add(y.substring(prepos, y.length()));
        }

        int count = 1;
        prepos = 0;
        int p = 0;
        for (int i = 0; i < x.length(); i++) {
            if (x.charAt(i) == ' ' || x.charAt(i) == '\n' || x.charAt(i) == 13) {
                if (x.substring(prepos, i).length() != 0) {
                    if (x.substring(prepos, i).compareTo(ysplit.get(p)) == 0) {
                        p++;
                        if (p == ysplit.size())
                            return count - ysplit.size() + 1;
                    } else {
                        p = 0;
                    }    
                    count++;
                }
                prepos = i + 1;
            }
        }
        if (x.substring(prepos, x.length()).compareTo(ysplit.get(p)) == 0) {
            p++;
            if (p == ysplit.size())
                return count - ysplit.size() + 1;
        }
        return -1;
    }
}
