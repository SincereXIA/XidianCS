package Sort;

import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdStats;

public class DrawGraph {
    private double[] listNow;
    private double Yscale;
    DrawGraph(Comparable[] list){
        StdDraw.setCanvasSize(800,300);
        StdDraw.clear(StdDraw.BLACK);
        double[] drawList = new  double[list.length];
        for (int i=0;i<list.length;i++){
            drawList[i] = Double.parseDouble(list[i].toString());
        }
        this.listNow = drawList;
        StdDraw.setXscale(0, drawList.length*2);
        double max = StdStats.max(drawList);
        StdDraw.setYscale(0, max);
        this.Yscale = max*2;
        StdDraw.setPenColor(StdDraw.GRAY);
        //StdDraw.setPenRadius(1);
        for (int i = 0; i<list.length; i++){
            StdDraw.line(i*2,0,i*2,drawList[i]);
        }
    }
    public void isSorted(Comparable[] a, int lo, int hi){
        for (int i = lo + 1; i <= hi; i++){
            StdDraw.setPenColor(StdDraw.BLACK);
            StdDraw.line(i*2,0,i*2,Yscale);
            StdDraw.setPenColor(StdDraw.GRAY);
            StdDraw.line(i*2,0,i*2,Double.parseDouble(a[i].toString()));
        }
    }
    public void exch (Object[] list, int  i, int j){
        StdDraw.setPenColor(StdDraw.RED);
        double di = Double.parseDouble(list[i].toString());
        double dj = Double.parseDouble(list[j].toString());
        StdDraw.line(i*2,0,i*2,di);
        StdDraw.line(j*2,0,j*2,dj);

        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.line(i*2,0,i*2,Yscale);
        StdDraw.line(j*2,0,j*2,Yscale);

        StdDraw.setPenColor(StdDraw.GRAY);
        StdDraw.line(i*2,0,i*2,dj);
        StdDraw.line(j*2,0,j*2,di);
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
        StdDraw.setPenColor(StdDraw.GRAY);
        for (int i = 0; i<list.length; i++){
            StdDraw.filledRectangle(i*2,drawList[i],1,drawList[i]);
        }
    }
}
