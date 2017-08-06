/*
 This program calculates the total no. of orders and their total price in a 
 particular restaurant.
 */
package restaurantmain;

public class RestaurantMain {

    public static void main(String[] args) {
        
        Restaurant restaurant = new Restaurant();
        Customer customer = new Customer();
        
       for (int i = 0; i < 100; i++) {
           int order = customer.getOrder();
           restaurant.placeOrder(order); 
       }
       
       System.out.println("Tatal number of orders placed: " + restaurant.itemNumber);
       System.out.println("Total sale: " + restaurant.totalPrice);
    }
    
}
