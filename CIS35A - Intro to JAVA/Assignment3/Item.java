/*
 This is the super class
 */
package lab03;

public class Item {
    int inventoryNo;
    String title;
    int yearPublished;
    double price;
    String firstName;
    String lastName;
    
    Item(int inventoryNo, String title, int yearPublished, double price,
          String firstName, String lastName) 
    {
        this.inventoryNo = inventoryNo;
        this.title = title;
        this.yearPublished = yearPublished;
        this.price = price;
        this.firstName = firstName;
        this.lastName = lastName;
    }
    
    int getInventoryNo() {
        return inventoryNo;
    }
    
    String getTitle() {
        return title;
    }
    
    int getYearPublished() {
        return yearPublished;
    }
    
    double getprice() {
        return price;
    }
    
    String getfirstName() {
        return firstName;
    }
    
    String getlastName() {
        return lastName;
    }
}
