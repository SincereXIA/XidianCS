import java.util.*;

public class BinarySearch implements Search {
    ArrayList<Node> array;

    public BinarySearch(String s) {
        array = new ArrayList<>();
        int count = 1;
        int prepos = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == ' ' || s.charAt(i) == '\n' || s.charAt(i) == 13) {
                if (s.substring(prepos, i).length() != 0) {
                    array.add(new Node(s.substring(prepos, i), count));
                    count++;
                }
                prepos = i + 1;
            }
        }
        if (prepos + 1 < s.length() && s.substring(prepos, s.length()).length() != 0) {
            array.add(new Node(s.substring(prepos, s.length()), count));
        }
        array.sort(Comparator.naturalOrder());
    }

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

        HashSet<Integer> set = new HashSet<>();
        for (int q1 = 0; q1 < ysplit.size(); q1++) {
            int ll = 0;
            int lr = array.size();
            int rl = 0;
            int rr = array.size();
            String s1 = ysplit.get(q1);
            while (ll < lr) {
                int mid = (ll + lr) / 2;
                if (array.get(mid).s.compareTo(s1) >= 0) {
                    lr = mid;
                } else {
                    ll = mid + 1;
                }
            }
            while (rl < rr) {
                int mid = (rl + rr) / 2;
                if (array.get(mid).s.compareTo(s1) <= 0) {
                    rl = mid + 1;
                } else {
                    rr = mid;
                }
            }
            HashSet<Integer> settemp = new HashSet<>();
            boolean found = false;
            for (int i = lr; i <= rl; i++) {
                if(i>=0&&i<array.size()){
                    if (q1 == 0) {
                        if (array.get(i).s.compareTo(s1) == 0) {
                            settemp.add(array.get(i).pos);
                            found = true;
                        }
                    } else {
                        if (set.contains(array.get(i).pos - 1)) {
                            if (array.get(i).s.compareTo(s1) == 0) {
                                settemp.add(array.get(i).pos);
                                found = true;
                            }
                        }
                    }
                }
            }
            if (!found) {
                return -1;
            }
            set = settemp;
        }
        int min = Integer.MAX_VALUE;
        for (int i : set) {
            min = Math.min(min, i);
        }
        return min - ysplit.size() + 1;
    }
}
