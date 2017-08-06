
package treemapexample;

public class Product {
    double productPrice;
    String productName;
    
    public Product(String name, double price) {
        productPrice = price;
        productName = name;
    }
    
    double getProductPrice() {
        return productPrice;
    }
    
    String getProductName() {
        return productName;
    }
}
