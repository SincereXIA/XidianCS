import java.io.*;

public class FileRead {
    private String fileName;
    private String s;

    public FileRead(String fileName) {
        this.fileName = fileName;
        try{
        InputStream f = new FileInputStream(fileName);
        }catch(IOException e){
            e.printStackTrace();
        }
        int len = 0;
        StringBuffer str = new StringBuffer("");
        File file = new File(fileName);
        try {
            FileInputStream is = new FileInputStream(file);
            InputStreamReader isr = new InputStreamReader(is);
            BufferedReader in = new BufferedReader(isr);
            String line = null;
            while ((line = in.readLine()) != null) {
                if (len != 0) 
                {
                    str.append("\r\n" + line);
                } else {
                    str.append(line);
                }
                len++;
            }
            in.close();
            is.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        s =  str.toString();
    }

    public String data() {
        return s;
    }
}
