
package lab02;
import java.util.*;

public class ProductComparer implements Comparator<Product> {
    public int compare(Product a, Product b) {
        if(a.getProductPrice() > b.getProductPrice())
            return 1;
        else if(a.getProductPrice() < b.getProductPrice())
            return -1;
        else
            return 0;
    }
}
