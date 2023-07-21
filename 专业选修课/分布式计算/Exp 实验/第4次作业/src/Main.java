import wsproxy.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;

public class Main {

    public static void main(String[] args) throws IOException {
        EnglishChinese englishChinese = new EnglishChinese();
        EnglishChineseSoap englishChineseSoap =  englishChinese.getEnglishChineseSoap();
        ArrayOfString result;
        List<String> rs;



        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            try{
                System.out.print("请输入待查询的单词：");
                String word = bufferedReader.readLine();
                result = englishChineseSoap.translatorString(word);
                rs = result.getString();

                System.out.println("-----基本解释----");
                for (String s: rs){
                    System.out.println(s);
                }
                System.out.println("-----近义词汇----");
                result = englishChineseSoap.translatorReferString(word);
                rs = result.getString();
                for (String s: rs){
                    System.out.println(s);
                }

                System.out.println("-----参考例句----");
                result = englishChineseSoap.translatorSentenceString(word);
                rs = result.getString();
                for (String s: rs){
                    System.out.println(s);
                }
                System.out.print("\n\n");

            }catch (Exception e){
                System.out.println("查询出错，请检查输入");
            }
        }

    }

}