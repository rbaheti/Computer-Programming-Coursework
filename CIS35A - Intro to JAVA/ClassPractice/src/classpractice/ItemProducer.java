package classpractice;
import java.util.Random;

public class ItemProducer {

    int total;
    
    int GetProducts() {
        Random randomGenerator = new Random();
        int randomInt = randomGenerator.nextInt(11);
        System.out.println("Produced " + randomInt + " products.");
        total += randomInt;
        return randomInt;
    }

    int TotalItemsProduced() {
        return total;
    }
}
