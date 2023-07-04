import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdStats;

import java.util.ArrayList;
import java.util.Map;
import java.util.LinkedHashMap;
import java.util.List;


public class TestResult {
    LinkedHashMap<String, ArrayList<Double>> results = new LinkedHashMap<>();
    int testTimes;


    /**
     * 记录一次测试结果
     */
    public void recordResult(LinkedHashMap<String,Double> result){
        if (results.isEmpty()){
            for (Map.Entry<String, Double> entry : result.entrySet()) {
                ArrayList<Double> time = new ArrayList<>();
                time.add(entry.getValue());
                results.put(entry.getKey(),time);
            }
        }
        else {
            for (Map.Entry<String, Double> entry : result.entrySet()) {
                results.get(entry.getKey()).add(entry.getValue());
            }
        }
    }

    /**
     * 打印测试结果
     */
    public void printResult(){
        for (Map.Entry<String, ArrayList<Double>> entry : results.entrySet()) {
            StdOut.printf("%4s\t\t",entry.getKey());
            double[] entryTime = new double[entry.getValue().size()];
            int i = 0;
            for (Double time : entry.getValue()){
                StdOut.printf("%.3f\t",time);
                entryTime[i++] = time;
            }
            StdOut.println(StdStats.mean(entryTime));
        }

        StdOut.println(results);

    }
}
