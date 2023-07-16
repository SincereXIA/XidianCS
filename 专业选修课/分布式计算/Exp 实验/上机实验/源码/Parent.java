import java.io.IOException;
import java.util.ArrayList;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class Parent {

    public static class PeopleMapper
            extends Mapper<LongWritable, Text, Text, Text>{


        public void map(LongWritable key, Text value, Context context
        ) throws IOException, InterruptedException {
            String son = value.toString().split(",")[0];

            String father=value.toString().split(",")[1];

            context.write(new Text(son), new Text("@"+father));
            context.write(new Text(father), new Text(son));
            System.out.println("add!"+ son + father);

        }
    }

    public static class PeopleReducer
            extends Reducer<Text,Text,Text,Text> {


        public void reduce(Text key, Iterable<Text> values,
                           Context context
        ) throws IOException, InterruptedException {
            System.out.print("start to reduce!");

            ArrayList<String> sons = new ArrayList<>();
            ArrayList<String> grandfathers = new ArrayList<>();

            for (Text val1 : values) {
                String people = val1.toString();
                if (people.startsWith("@")){
                    grandfathers.add(people.substring(1));
                }else {
                    sons.add(people);
                }

            }
            for (String son:sons){
                for (String grandfather:grandfathers){
                    context.write(new Text(son), new Text(grandfather));
                }
            }

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
        job.setJarByClass(Parent.class);
        job.setMapperClass(PeopleMapper.class);
        job.setReducerClass(PeopleReducer.class);

        job.setMapOutputValueClass(Text.class);
        job.setMapOutputKeyClass(Text.class);

        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
        for (int i = 0; i < otherArgs.length - 1; ++i) {
            FileInputFormat.addInputPath(job, new Path(otherArgs[i]));
        }
        FileOutputFormat.setOutputPath(job,
                new Path(otherArgs[otherArgs.length - 1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}