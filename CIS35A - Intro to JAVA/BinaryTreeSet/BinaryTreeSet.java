package binarytreeset;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class BinaryTreeSet {

    Set<String> words = null;

    public BinaryTreeSet(String sfile) throws FileNotFoundException {
        words = new HashSet<>(); // HashSet implements Set
        File file = new File(sfile);
        Scanner in = new Scanner(file);
        while (in.hasNext()) {
            String word = in.next();
            long callTime = System.currentTimeMillis();
            words.add(word);
        }
    }

    public void OutputSet() {
        for (String s : words) {
            System.out.println(s);
        }
    }

    public static void main(String[] args) {
        try {
            BinaryTreeSet stest = new BinaryTreeSet("words.txt");
            stest.OutputSet();
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
