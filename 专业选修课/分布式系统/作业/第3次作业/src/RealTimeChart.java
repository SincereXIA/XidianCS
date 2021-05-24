import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.StandardChartTheme;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.data.time.Millisecond;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;

import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;
import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * 实时绘图
 */
class RealTimeChartListener implements MessageListener {
    public void onMessage(Message message) {
        try {
            Double num = (Double) ((ObjectMessage)message).getObject();
            RealTimeChart.timeSeries.add(new Millisecond(), num);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


public class RealTimeChart extends ChartPanel {

    private static final long serialVersionUID = 1L;
    public static TimeSeries timeSeries ;
    static RealTimeChart chart;



    public RealTimeChart(String chartContent, String title, String yAxisName) {
        super(createChart(chartContent, title, yAxisName));
    }

    private static JFreeChart createChart(String chartContent, String title, String yAxisName) {
        timeSeries = new TimeSeries(chartContent, org.jfree.data.time.Millisecond.class);
        TimeSeriesCollection timeseriescollection = new TimeSeriesCollection(timeSeries);
        JFreeChart jfreechart = ChartFactory.createTimeSeriesChart(title, "时间(秒)", yAxisName, timeseriescollection, true, true, false);
        ValueAxis valueaxis = jfreechart.getXYPlot().getDomainAxis();
        valueaxis.setAutoRange(true);
        valueaxis.setFixedAutoRange(3000D);

        return jfreechart;
    }


    public static void main() {
        // 设置显示样式，避免中文乱码
        StandardChartTheme standardChartTheme = new StandardChartTheme("CN");
        standardChartTheme.setExtraLargeFont(new Font("微软雅黑", Font.BOLD, 20));
        standardChartTheme.setRegularFont(new Font("微软雅黑", Font.PLAIN, 15));
        standardChartTheme.setLargeFont(new Font("微软雅黑", Font.PLAIN, 15));
        ChartFactory.setChartTheme(standardChartTheme);
        JFrame frame = new JFrame("随机信号分析系统");
        RealTimeChart realTimeChart = new RealTimeChart("随机信号动态折线图", "随机信号曲线", "信号值");
        chart = realTimeChart;
        frame.getContentPane().add(realTimeChart, new BorderLayout().CENTER);
        frame.pack();
        frame.setVisible(true);
        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent windowevent) {
                System.exit(0);
            }
        });
    }
}