package countcharfromstring;

import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class CountCharFromString {

    public static void main(String[] args) {
        System.out.println("Please enter characters from 'A' to 'E' upto 10  times or less");
        System.out.println("Please enter any other number or character, once done");

        char ch[] = new char[100];
        int count[][] = new int[3][26];
        char mychar[][] = new char[3][26];

        Scanner in = new Scanner(System.in);
        String line = in.nextLine();
        for (int i = 0; i < line.length(); i++) {
            ch[i] = line.charAt(i);
            if (ch[i] >= 'A' && ch[i] <= 'Z') {
                count[0][ch[i] - 'A']++;
                mychar[0][ch[i] - 'A'] = ch[i];
            } else if (ch[i] >= 'a' && ch[i] <= 'z') {
                count[1][ch[i] - 'a']++;
                mychar[1][ch[i] - 'a'] = ch[i];
            } else if (ch[i] >= '0' && ch[i] <= '9') {
                count[2][ch[i] - '0']++;
                mychar[2][ch[i] - '0'] = ch[i];
            } else {
                continue;
            }
        }

        for (int i = 0; i < 26; i++) {
            if (count[0][i] > 0) {
                System.out.println(mychar[0][i] + ": " + count[0][i]);
            }
        }

        for (int i = 0; i < 26; i++) {
            if (count[1][i] > 0) {
                System.out.println(mychar[1][i] + ": " + count[1][i]);
            }
        }

        for (int i = 0; i < 26; i++) {

            if (count[2][i] > 0) {
                System.out.println(mychar[2][i] + ": " + count[2][i]);
            }
        }
        
            public void SimpleReadFile(String filename) throws IOException {
        FileReader freader = new FileReader(filename);

        int character;
        character = freader.read();
        while (character != -1) {
            System.out.print((char) character);
            character = freader.read();
        }
        freader.close();  // Close to unlock.
    }
    }

}
