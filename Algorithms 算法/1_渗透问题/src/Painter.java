import edu.princeton.cs.algs4.StdDraw;

import java.awt.*;

public class Painter {
    private int size;
    public Painter(int size){
        this.size = size;
//        for (int i = 0; i<size; i++){
//            for (int j = 0; j<size;j++){
//                printBlock(i,j);
//            }
//        }
        StdDraw.clear(Color.BLACK);
    }

    public void printBlock(int x, int y){
        StdDraw.setPenColor(Color.BLACK);
        StdDraw.filledSquare(1.0/size*x + 1.0/size/2, 1-(1.0/size*y) - 1.0/size/2, (1.0/size/2));
    }

    public void printOpen(int x, int y){
        StdDraw.setPenColor(Color.WHITE);
        StdDraw.filledSquare(1.0/size*x + 1.0/size/2, 1-(1.0/size*y) - 1.0/size/2, (1.0/size/2));

    }

    public void printFull(int x, int y){
        StdDraw.setPenColor(Color.CYAN);
        StdDraw.filledSquare(1.0/size*x + 1.0/size/2, 1-(1.0/size*y) - 1.0/size/2, (1.0/size/2));

    }

    public void printResult(String rs){
        StdDraw.setPenColor(Color.RED);
        StdDraw.setFont(new Font("TimesRoman",Font.BOLD,16));
        StdDraw.text(0.5,0.5, "Percolates!!");
        StdDraw.text(0.5,0.3, rs);
    }
}
