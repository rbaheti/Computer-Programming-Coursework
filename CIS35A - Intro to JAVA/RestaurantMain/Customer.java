
package restaurantmain;

import java.util.Random;

public class Customer {
    int total;
    
    int getOrder(){
        Random randomGenerator = new Random();
        int randomInt = randomGenerator.nextInt(11);
        System.out.println("Placing order for: $" + randomInt);
        total += randomInt;
        return randomInt;
    }
}
