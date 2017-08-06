//This is the sub-class of super class Item
package lab03;

public class Book extends Item {
     String ISBNnum;
     char hardBack;
     int numOfPages;
 
     Book (int inventeryNo, String title, int yearPublished, double price,
           String firstName, String lastName, String ISBNnum, char hardBack, int numOfPages) 
     {
         super(inventeryNo, title, yearPublished, price, firstName, lastName);
         this.ISBNnum = ISBNnum;
         this.hardBack = hardBack;
         this.numOfPages = numOfPages;          
     }
     
     String getISBNnum() {
        return ISBNnum;
    }
     
     char gethardBack() {
        return hardBack;
    }
     
     int getnumOfPages() {
        return numOfPages;
    }
}
