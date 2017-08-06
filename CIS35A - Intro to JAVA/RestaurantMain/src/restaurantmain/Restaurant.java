/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package restaurantmain;

public class Restaurant {

    int itemNumber;
    int totalPrice;
    
    /*Restaurant() {
        itemNumber = 0;
        totalPrice = 0;
    }*/

    int totalItem() {
        return itemNumber;
    }

    void placeOrder(int orderPrice) {
        if (orderPrice > 0) {
            itemNumber += 1;
            totalPrice += orderPrice;
        }
    }

    int totaPrice() {
        return totalPrice;
    }
}
