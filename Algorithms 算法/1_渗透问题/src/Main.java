import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;
import java.util.Random;

public class Main {
    private static void test(int size){
        long seed1 = System.nanoTime();
        Random seedRandom = new Random(seed1);
        Percolation map = new Percolation(size);
        while (!map.percolates()){
            int x = seedRandom.nextInt(size);
            int y = seedRandom.nextInt(size);
            map.open(x,y);
        }
        int opensize = map.openSize();
        StdOut.println(opensize);
        map.painter.printResult("open:" + map.openSize() + "  " + (float) opensize / (size*size) *100 +"%");
    }

    public static void main(String[] args){
        test(150);
    }
}
