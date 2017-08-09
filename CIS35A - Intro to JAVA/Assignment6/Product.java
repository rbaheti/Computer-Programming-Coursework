package lab07;

public class Product implements Comparable<Product> {
    double productPrice;
    String productName;
    
    public Product(String name, double price) {
        productPrice = price;
        productName = name;
    }
    
    public int compareTo(Product prod) {
        return productName.compareTo(prod.productName);
    }
    
    public String toString() {
        return productName + " " + productPrice;
    }
}