package assignment1;
import java.util.Scanner;

public class Assignment1 {

    public static void main(String[] args) {
        // TODO code application logic here
        double height, weight, bmi;
        Scanner in = new Scanner(System.in);
        
        System.out.println("Please enter you height in inches: ");
        height = in.nextDouble();
        
        System.out.println("Please enter you weight in pounds: ");
        weight = in.nextDouble();
        
        Assignment0 value = new Assignment0();
        bmi = value.BodyMassIndex(height, weight);
        
        System.out.println("Your Body Mass Index is: " + bmi);
    
    }
    
    public double BodyMassIndex(double height, double weight)
    {
        double bmi = (weight * 703)/(height * height);
        return bmi;
    }
    
}
