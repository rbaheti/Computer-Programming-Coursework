package lab09;

import java.util.ArrayList;

public class BinarySearch {
    public int Search(ArrayList<Product> productArr,int searchValue, int low, int high){
        if(low > high){
            return -1;
        }
        int mid = (low+high)/2;
        Product product = productArr.get(mid);
        
        if(product.productId == searchValue) {
            return mid;
        }
        else if(product.productId < searchValue) {
            return Search(productArr, searchValue, mid+1, high);
        }
        else {
         return Search(productArr, searchValue, low, mid-1);   
        }
    }
}
