public class Node implements Comparable<Node> {
    public String s;
    public int pos;
    public Node(String s,int pos){
        this.s = s;
        this.pos = pos;
    }
    public int compareTo(Node other){
        if(s.compareTo(other.s) == 0)
            return pos - other.pos;
        return s.compareTo(other.s);
    }
}
