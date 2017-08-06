/*
This class is used for some calculation.
 */
package classpractice;

import java.util.Scanner;

public class Calculater{

    int num1, num2, sum = 0;
    
    void sum() {
    Scanner in = new  Scanner(System.in);
    
    System.out.println("Please enter 2 integers: ");
    System.out.print("Integer 1: ");
    num1 = in.nextInt();
    System.out.print("Integer 2: ");
    num2 = in.nextInt();
    
    sum = num1+num2;
    System.out.println("Sum = " + sum);
    }
    
}
