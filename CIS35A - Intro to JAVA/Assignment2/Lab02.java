// This program reads from a file and splits the data in the file.
// Then it sorts the price of the products in ascending order.

package lab02;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class Lab02 {

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

    public Lab02() {
        products = new ArrayList<Product>();

        try {
            ReadFile("Products.txt");
        } catch (IOException e) {
        }
    }

    public void SortList() {
        Collections.sort(products, new ProductComparer());
    }

    public void PrintList() {
        for (int i = 0; i < products.size(); i++) {
            System.out.print(products.get(i).getProductName() + " ");
            System.out.println(products.get(i).getProductPrice());
        }
    }

    public static void main(String[] args) {
        Lab02 a = new Lab02();
        System.out.println("UNSORTED LIST IS: ");
        System.out.println();
        a.PrintList();
        a.SortList();
        System.out.println();
        System.out.println();
        System.out.println("SORTED LIST IS: ");
        System.out.println();
        a.PrintList();
    }
}
