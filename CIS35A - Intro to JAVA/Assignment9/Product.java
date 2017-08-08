package lab09;

public class Product {

    int productId;
    String ISBN;
    String productName;
    String author;
    int yearPublished;
    char physicalForm;
    double price;

    Product(int productId, String ISBN, String productName, String author,
            int yearPublished, char physicalForm, double price) {
        this.productId = productId;
        this.ISBN = ISBN;
        this.productName = productName;
        this.author = author;
        this.yearPublished = yearPublished;
        this.physicalForm = physicalForm;
        this.price = price;
    }

    int GetProductId() {
        return productId;
    }

    String GetISBN() {
        return ISBN;
    }

    String GetProductName() {
        return productName;
    }
    
    String GetAuthorName() {
        return author;
    }

    int GetYearPublished() {
        return yearPublished;
    }

    char GetPhysicalForm() {
        return physicalForm;
    }
    
    double Getprice() {
        return price;
    }
}
