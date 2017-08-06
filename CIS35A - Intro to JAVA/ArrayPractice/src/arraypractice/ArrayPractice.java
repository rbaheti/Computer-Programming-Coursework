package arraypractice;
import java.util.*;
import java.io.*;

public class ArrayPractice {
    
    public static void main(String[] args) {
        
        int arr[] = new int[10];
        System.out.println("Please enter 10 numbers into an array:");
        Scanner in = new Scanner(System.in);
        
        for(int i = 0; i < 10; i++)
        {
            arr[i] = in.nextInt();
            System.out.print(" ");
        }
        
        System.out.println();
    }
    
}
