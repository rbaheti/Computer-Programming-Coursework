package lab10;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Lab10 {

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

    ArrayList<Product> products;

    public Lab10() {
        products = new ArrayList<Product>();
        try {
            ReadFile("UProducts.txt");
        } catch (IOException e) {
        }
    }

    public void Display(Object[] unsorted) {
        for (Object i : unsorted) {
            System.out.println(i + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Lab10 lab_10 = new Lab10();
        
        SetSorting bsort = new SetSorting();
        
        Object product_array[] = lab_10.products.toArray();
        
        bsort.Sort(product_array);

        System.out.println("SORTED LIST IS: ");
        System.out.println();
        bsort.Display(product_array);    
    }
}