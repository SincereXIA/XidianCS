import Sort.*;


public class Main {
    public static void main(String args[]){
        //SortTest.generateRandom(10000);
        //StdOut.println(SortTest.runTest(SortTest.randomList));
        SortTest st = new SortTest();
        st.runTests(10000);

        Integer[] randomList = SortTest.generateRandom(100);
        Insertion insertion = new Insertion(randomList);
        insertion.sort();


        randomList = SortTest.generateRandom(1000);
        Merge merge = new Merge(randomList);
        merge.sort();

        randomList = SortTest.generateRandom(1000);
        Quick quick = new Quick(randomList);
        quick.sort();

        randomList = SortTest.generateRandom(600);
        Quick3way quick3way = new Quick3way(randomList);
        quick3way.sort();
    }
}
