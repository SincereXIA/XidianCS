import java.io.IOException;
import java.util.ArrayList;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class Grade {

    public static class StuMapper
            extends Mapper<LongWritable, Text, Text, DoubleWritable>{


        public void map(LongWritable key, Text value, Context context
        ) throws IOException, InterruptedException {
            String[] rs = value.toString().split(",");
            String className = rs[0];
            String SName = rs[1];
            String CName = rs[2];
            boolean isM = rs[3].equals("必修");
            double G = Double.parseDouble(rs[4]);
            if (isM){
                context.write(new Text(SName), new DoubleWritable(G));
            }
            context.write(new Text(className+CName), new DoubleWritable(G));

        }
    }

    public static class StuReducer
            extends Reducer<Text,DoubleWritable,Text,DoubleWritable> {


        public void reduce(Text key, Iterable<DoubleWritable> values,
                           Context context
        ) throws IOException, InterruptedException {
            System.out.print("start to reduce!");

            double num = 0;
            int sum = 0;
            for (DoubleWritable i : values){
                sum += i.get();
                num += 1;
            }
            double rs = (double)sum/num;
            context.write(key, new DoubleWritable(rs));
        }
    }

    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
        if (otherArgs.length < 2) {
            System.err.println("Usage: peopleMatch <in> [<in>...] <out>");
            System.exit(2);
        }
        Job job = Job.getInstance(conf, "peopleMatch");
        job.setJarByClass(Grade.class);
        job.setMapperClass(StuMapper.class);
        job.setReducerClass(StuReducer.class);

        job.setMapOutputValueClass(DoubleWritable.class);
        job.setMapOutputKeyClass(Text.class);

        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(DoubleWritable.class);
        for (int i = 0; i < otherArgs.length - 1; ++i) {
            FileInputFormat.addInputPath(job, new Path(otherArgs[i]));
        }
        FileOutputFormat.setOutputPath(job,
                new Path(otherArgs[otherArgs.length - 1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}