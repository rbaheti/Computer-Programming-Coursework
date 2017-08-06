// This program reads from a file and displays total number of 
// small and capital alphabets and numbers used in the file.

package lab01;

import java.io.*;

public class Lab01 {

    public void ReadFile(String filename) throws IOException {
        File fread = new File(filename);
        FileReader freader = new FileReader(fread);
        BufferedReader buff_reader = new BufferedReader(freader);

        int count[][] = new int[3][26];
        char mychar[][] = new char[3][26];

        String line;
        line = buff_reader.readLine();
        while (line != null) {
            for (int i = 0; i < line.length(); i++) {
                char ch = line.charAt(i);
                if (ch >= 'A' && ch <= 'Z') {
                    count[0][ch - 'A']++;
                    mychar[0][ch - 'A'] = ch;
                } else if (ch >= 'a' && ch <= 'z') {
                    count[1][ch - 'a']++;
                    mychar[1][ch - 'a'] = ch;
                } else if (ch >= '0' && ch <= '9') {
                    count[2][ch - '0']++;
                    mychar[2][ch - '0'] = ch;
                } else {
                    continue;
                }
            }
            line = buff_reader.readLine();
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
        buff_reader.close();
    }

    public static void main(String[] args) {

        Lab01 frw = new Lab01();
        try {
            frw.ReadFile("Speech.txt");
        } catch (IOException e) {
        }
    }

}
