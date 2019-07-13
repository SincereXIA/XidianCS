import edu.princeton.cs.algs4.Draw;
import edu.princeton.cs.algs4.Insertion;
import edu.princeton.cs.algs4.Merge;
import edu.princeton.cs.algs4.Quick;
import edu.princeton.cs.algs4.Quick3way;
import edu.princeton.cs.algs4.MergeBU;

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Stopwatch;
import edu.princeton.cs.algs4.StdRandom;
import org.omg.PortableInterceptor.INACTIVE;

import java.util.LinkedHashMap;
import java.util.Map;


public class SortTest {
    public static Integer[] randomList;
    /**
     * 产生 size 大小的随机数组
     * @param size
     */
    public static Integer[] generateRandom(int size){
        randomList = new Integer[size];
        for (int j = 0; j<size;j++){
            randomList[j] = StdRandom.uniform(size/10);
        }
        StdRandom.shuffle(randomList);
        return randomList;
    }

    /**
     * 对 list 数组元素进行一次排序测试
     * @param list
     */
    public static LinkedHashMap<String,Double> runTest(Comparable[] list){
        Comparable[] tlist = list.clone();
        LinkedHashMap<String,Double> result = new LinkedHashMap<>();
        Runtime run = Runtime.getRuntime();
        Stopwatch w1  = new Stopwatch();
        Insertion.sort(tlist);
        result.put("IS",w1.elapsedTime());
        run = Runtime.getRuntime();
        StdOut.println(run.totalMemory()-run.freeMemory());


        tlist = list.clone();
        Stopwatch w2  = new Stopwatch();
        Merge.sort(tlist);
        result.put("TDM",w2.elapsedTime());
        run = Runtime.getRuntime();
        StdOut.println(run.totalMemory()-run.freeMemory());

        tlist = list.clone();
        Stopwatch w3  = new Stopwatch();
        MergeBU.sort(tlist);
        result.put("BUM",w3.elapsedTime());
        run = Runtime.getRuntime();
        StdOut.println(run.totalMemory()-run.freeMemory());

        tlist = list.clone();
        Stopwatch w4  = new Stopwatch();
        Quick.sort(tlist);
        result.put("RQ",w4.elapsedTime());
        run = Runtime.getRuntime();
        StdOut.println(run.totalMemory()-run.freeMemory());

        tlist = list.clone();
        Stopwatch w5  = new Stopwatch();
        Quick3way.sort(tlist);
        result.put("DQ3P",w5.elapsedTime());
        run = Runtime.getRuntime();
        StdOut.println(run.totalMemory()-run.freeMemory());
        return result;
    }

    public  void runTests(int size){

        TestResult rec = new TestResult();
        for(int i = 0; i<10;i++){
            generateRandom(size);
            rec.recordResult(runTest(randomList));
        }
        rec.printResult();
    }

}
