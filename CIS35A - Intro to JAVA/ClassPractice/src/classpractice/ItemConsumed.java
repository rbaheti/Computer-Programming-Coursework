package classpractice;

public class ItemConsumed {
    int total;
    
    void ConsumeProducts(int consumeValue) {
      System.out.println("Consumed " + consumeValue + " products.");
      total += consumeValue;
    }

    int TotalItemsConsumed() {
        return total;
    }
}
