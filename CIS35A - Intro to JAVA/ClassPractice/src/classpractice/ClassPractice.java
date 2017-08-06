/*
 This program calculates the total number of items produced by the producer 
 and consumed by the consumer.
 */
package classpractice;

import java.util.*;

public class ClassPractice {

    public static void main(String[] args) {
        //Calculater calci = new Calculater();
        //calci.sum();

        ItemProducer produce = new ItemProducer();
        ItemConsumed consume = new ItemConsumed();
        
        for (int i = 0; i < 10; i++) {
            int numProduced = produce.GetProducts();
            consume.ConsumeProducts(numProduced);
        }
        System.out.println("Total items produced: " + produce.TotalItemsProduced());
        System.out.println("Total items Consumed: " + consume.TotalItemsConsumed());
    }

}
