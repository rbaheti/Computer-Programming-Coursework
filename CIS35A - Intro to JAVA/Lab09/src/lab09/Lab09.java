package lab09;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Lab09 {

    ArrayList<Product> products = new ArrayList<Product>();

    public void ReadFile(String filename) throws IOException {
        File fread = new File(filename);
        FileReader freader = new FileReader(fread);
        BufferedReader buff_reader = new BufferedReader(freader);

        String line;
        line = buff_reader.readLine();

        while (line != null) {
            String temp[];
            temp = line.split(",");
            Product product = new Product(Integer.parseInt(temp[0]),
                    temp[1], temp[2], temp[3],
                    Integer.parseInt(temp[4]),
                    temp[5].charAt(0),
                    Double.parseDouble(temp[6]));

            products.add(product);

            line = buff_reader.readLine();
        }

        SelectionSort sort_obj = new SelectionSort();
        sort_obj.Sort(products, 0, products.size()-1);
        
        System.out.println("Please enter the Product ID you want to search: ");
        int searchValue;
         Scanner input = new Scanner(System.in);
         searchValue = input.nextInt();
        
        BinarySearch search_obj = new BinarySearch();
        int index = search_obj.Search(products, searchValue, 0, products.size()-1);
        
        Product product = products.get(index);
        System.out.println("Searched Product details are: "
                    + product.GetProductId() + " "
                    + product.GetISBN() + " "
                    + product.GetProductName() + " "
                    + product.GetAuthorName() + " "
                    + product.GetYearPublished() + " "
                    + product.GetPhysicalForm() + " "
                    + product.Getprice() + " ");
        
         /*for (int i = 0; i < products.size(); i++) {
            Product product = products.get(i);

            System.out.println("Product details: "
                    + product.GetProductId() + " "
                    + product.GetISBN() + " "
                    + product.GetProductName() + " "
                    + product.GetAuthorName() + " "
                    + product.GetYearPublished() + " "
                    + product.GetPhysicalForm() + " "
                    + product.Getprice() + " ");
        }*/
    }

    public static void main(String[] args) {

        Lab09 frw = new Lab09();
        try {
            frw.ReadFile("Product.txt");
        } catch (IOException e) {
        }
    }

}
