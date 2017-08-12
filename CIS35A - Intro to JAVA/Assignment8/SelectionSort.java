package lab09;

import java.util.*;

public class SelectionSort {
    public void Sort(ArrayList<Product> productArr, int low, int high) {
        int minIndex;
        int minValue;
        
        if(low < high) {
            minIndex = low;
            Product min_product = productArr.get(low);
            minValue = min_product.productId;
            for(int i = low+1; i < high; ++i){
                Product cur_product = productArr.get(i);
                if(cur_product.productId < minValue){
                    minValue = cur_product.productId;
                    minIndex = i;
                }
            }
            Product productTemp = productArr.get(minIndex);
            productArr.set(minIndex, productArr.get(low));
            productArr.set(low, productTemp);
            Sort(productArr, low + 1, high);
        }   
    }
}
