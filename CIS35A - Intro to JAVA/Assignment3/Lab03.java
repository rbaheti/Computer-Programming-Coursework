/*
 This program is the example of inheritance and also uses ArrayList
 */
package lab03;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Lab03 {

    ArrayList<Item> items = new ArrayList<Item>();

    public void ReadFile(String filename) throws IOException {
        File fread = new File(filename);
        FileReader freader = new FileReader(fread);
        BufferedReader buff_reader = new BufferedReader(freader);

        String line;
        line = buff_reader.readLine();

        while (line != null) {
            String temp[];
            temp = line.split(",");
            if (temp[0].startsWith("4")) {
                String nameParts[] = temp[3].split(" ");
                Book book = new Book(Integer.parseInt(temp[0]),
                        temp[2],
                        Integer.parseInt(temp[4]),
                        Double.parseDouble(temp[7]),
                        nameParts[0],
                        nameParts[1],
                        temp[1],
                        temp[5].charAt(0),
                        Integer.parseInt(temp[6]));
                items.add(book);
            } else if (temp[0].startsWith("7")) {
                DVD dvd = new DVD(Integer.parseInt(temp[0]),
                        temp[2],
                        Integer.parseInt(temp[3]),
                        Double.parseDouble(temp[6]),
                        temp[5],
                        temp[4],
                        temp[1]);
                items.add(dvd);
            }
            line = buff_reader.readLine();
        }
        double bookPrice = 0.0;
        for (int i = 0; i < items.size(); i++) {
            Item item = items.get(i);

            if (item instanceof Book) {
                Book book = (Book)item;
                System.out.println("Book details: " +
                        book.getInventoryNo() + " " +
                        book.getTitle() + " " +
                        book.getYearPublished() + " " +
                        book.getprice() + " " +
                        book.getfirstName() + " " +
                        book.getlastName() + " " +
                        book.getISBNnum() + " " +
                        book.gethardBack() + " " +
                        book.getnumOfPages()); 
                
                bookPrice += book.getprice();
            }   
        }
        
        double dvdPrice = 0;
        for (int i = 0; i < items.size(); i++) {
            Item item = items.get(i);

            if (item instanceof DVD) {
                DVD dvd = (DVD)item;
                System.out.println("DVD details: " +
                        dvd.getInventoryNo() + " " +
                        dvd.getTitle() + " " +
                        dvd.getYearPublished() + " " +
                        dvd.getprice() + " " +
                        dvd.getfirstName() + " " +
                        dvd.getlastName() + " " +
                        dvd.getcatalogNum());
                
                dvdPrice += dvd.getprice();
            }
        }
        System.out.println();
        System.out.println("Total Book price is: " + bookPrice);
        System.out.println("Total DVD price is: " + dvdPrice);
    }
   

    public static void main(String[] args) {

        Lab03 frw = new Lab03();
        try {
            frw.ReadFile("BookMusic.txt");
        } catch (IOException e) {
        }
    }
}
