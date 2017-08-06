import java.util.Scanner;
        
//package lab0;

public class Lab0 {
    
    public double BodyMassIndex(double height, double weight)
    {
        double bmi = (weight * 703)/(height * height);
        return bmi;
    }

    public static void main(String[] args) {
        
        double height, weight, bmi;
        Scanner in = new Scanner(System.in);
        
        System.out.println("Please enter you height in inches: ");
        height = in.nextDouble();
        
        System.out.println("Please enter you weight in pounds: ");
        weight = in.nextDouble();
        
        Lab0 value = new Lab0();
        bmi = value.BodyMassIndex(height, weight);
        
        System.out.println("Your Body Mass Index is: " + bmi);
    }
    
}
