//This is the sub-class of super class Item

package lab03;

public class DVD extends Item {
    String catalogNum;
    
    DVD(int inventeryNo, String title, int yearPublished, double price,
          String firstName, String lastName, String catalogNum)
    {
        super(inventeryNo, title, yearPublished, price, firstName, lastName);
        this.catalogNum = catalogNum;
    }
    
    String getcatalogNum() {
        return catalogNum;
    }
}
