package Sort;

import edu.princeton.cs.algs4.Draw;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdStats;

import java.util.Comparator;
import java.util.List;

public class DrawGraph_old {
    private double[] listNow;
    private double Yscale;
    DrawGraph_old(Comparable[] list){
        StdDraw.setCanvasSize(600,600);
        StdDraw.clear(StdDraw.BLACK);
        double[] drawList = new  double[list.length];
        for (int i=0;i<list.length;i++){
            drawList[i] = Double.parseDouble(list[i].toString());
        }
        this.listNow = drawList;
        StdDraw.setXscale(0, drawList.length*2);
        double max = StdStats.max(drawList);
        StdDraw.setYscale(0, max*2);
        this.Yscale = max*2;
        StdDraw.setPenColor(StdDraw.WHITE);
        for (int i = 0; i<list.length; i++){
            StdDraw.filledRectangle(i*2,drawList[i],1,drawList[i]);
        }
    }
    public void isSorted(Comparable[] a, int lo, int hi){
        for (int i = lo + 1; i <= hi; i++){
            StdDraw.setPenColor(StdDraw.BLACK);
            StdDraw.filledRectangle(i*2,Yscale,1,Yscale);
            StdDraw.setPenColor(StdDraw.WHITE);
            StdDraw.filledRectangle(i*2,Double.parseDouble(a[i].toString()),1,Double.parseDouble(a[i].toString()));
        }
    }
    public void exch (Object[] list, int  i, int j){
        StdDraw.setPenColor(StdDraw.RED);
        double di = Double.parseDouble(list[i].toString());
        double dj = Double.parseDouble(list[j].toString());
        StdDraw.filledRectangle(i*2,di,1,di);
        StdDraw.filledRectangle(j*2,dj,1,dj);

        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.filledRectangle(i*2,Yscale,1.3,Yscale);
        StdDraw.filledRectangle(j*2,Yscale,1.3,Yscale);

        StdDraw.setPenColor(StdDraw.WHITE);
        StdDraw.filledRectangle(i*2,dj,1.1,dj);
        StdDraw.filledRectangle(j*2,di,1.1,di);
    }
    public static void columnChart(Comparable[] list){
        StdDraw.clear(StdDraw.BLACK);
        double[] drawList = new  double[list.length];
        for (int i=0;i<list.length;i++){
            drawList[i] = Double.parseDouble(list[i].toString());
        }
        StdDraw.setXscale(0, drawList.length);
        double max = StdStats.max(drawList);
        StdDraw.setYscale(0, max*2);
        StdDraw.setPenColor(StdDraw.WHITE);
        for (int i = 0; i<list.length; i++){
            StdDraw.filledRectangle(i*2,drawList[i],1,drawList[i]);
        }
    }
}
