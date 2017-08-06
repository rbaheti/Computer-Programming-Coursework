package lab07;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


public class Lab07 {
    
   void ReadFile(String filename) throws IOException {
        File fread = new File(filename);
        FileReader freader = new FileReader(fread);
        BufferedReader buff_reader = new BufferedReader(freader);

        String line;
        line = buff_reader.readLine();

        while (line != null) {
            String temp[];
            temp = line.split(","); // split is the method of the String class
            Product pr = new Product(temp[0], Double.parseDouble(temp[1]));
            // "Double.parseDouble(variable)" converts variable string to double
            products.add(pr);
            line = buff_reader.readLine();
        }
    }
   
   void ReadFileStudents(String filename) throws IOException {
        File fread = new File(filename);
        FileReader freader = new FileReader(fread);
        BufferedReader buff_reader = new BufferedReader(freader);

        String line;
        line = buff_reader.readLine();

        while (line != null) {
            String temp[];
            temp = line.split(","); // split is the method of the String class
            Student stud = new Student(temp[0], temp[1], temp[2], Double.parseDouble(temp[3]));
            // "Double.parseDouble(variable)" converts variable string to double
            students.add(stud);
            line = buff_reader.readLine();
        }
    }
   
      void ReadFileCommonWords(String filename) throws IOException {
        File fread = new File(filename);
        FileReader freader = new FileReader(fread);
        BufferedReader buff_reader = new BufferedReader(freader);

        String line;
        line = buff_reader.readLine();

        while (line != null) {
            CommonWord cwords = new CommonWord(line);
            // "Double.parseDouble(variable)" converts variable string to double
            commonWords.add(cwords);
            line = buff_reader.readLine();
        }
    }

    ArrayList<Product> products;
    ArrayList<Student> students;
    ArrayList<CommonWord> commonWords;

    public Lab07() {
        products = new ArrayList<Product>();
        students = new ArrayList<Student>();
        commonWords = new ArrayList<CommonWord>();

        try {
            ReadFile("UProducts.txt");
            ReadFileStudents("Students.txt");
            ReadFileCommonWords("CommonWords.txt");
        } catch (IOException e) {
        }
    }

    public static void main(String[] args) {
        Lab07 lab_07 = new Lab07();
        
        BubbleSort bsort = new BubbleSort();
        System.out.println("UNSORTED LIST IS: ");
        System.out.println();
        
        Object product_array[] = lab_07.products.toArray();
        bsort.Display(product_array);
        
        bsort.Sort(product_array);
        
        System.out.println();
        System.out.println();
        System.out.println("SORTED LIST IS: ");
        System.out.println();
        bsort.Display(product_array);
        
        // Printing Students data:
        System.out.println("UNSORTED STUDENTS LIST IS: ");
        System.out.println();
        
        Object student_array[] = lab_07.students.toArray();
        bsort.Display(student_array);
        
        bsort.Sort(student_array);
        
        System.out.println();
        System.out.println();
        System.out.println("SORTED STUDENT LIST IS: ");
        System.out.println();
        bsort.Display(student_array);
        
        // Printing Students data:
        System.out.println("UNSORTED COMMON WORDS LIST IS: ");
        System.out.println();
        
        Object Words_array[] = lab_07.commonWords.toArray();
        bsort.Display(Words_array);
        
        bsort.Sort(Words_array);
        
        System.out.println();
        System.out.println();
        System.out.println("SORTED COMMON WORDS LIST IS: ");
        System.out.println();
        bsort.Display(Words_array);
    }
}