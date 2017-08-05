package driver;

import model.Automotive;
import util.FileIO;

public class Driver {
    public static void main(String[] args) {
        FileIO file = new FileIO();
        Automotive FordZTW = file.readFile("FordZTW.txt");
        
        System.out.println("Print attributes before serialization");
        FordZTW.print();
        
        // serialize Automotive object
        file.serializeAuto(FordZTW);
        
        // Deserialize Automotive object and read it into memory
        Automotive newFordXTW = file.deserializeAuto("auto.ser");
        System.out.println("\nNew Automotive attributes are:");
        newFordXTW.print();
        
        System.out.println("\nSeraching Option Set by name 'color':");
        newFordXTW.findOptionSet("color");
        
        System.out.println("\nSeraching Option 'automatic' in Option Set 'transmission':");
        FordZTW.findOption("transmission", "automatic");
    }
}

