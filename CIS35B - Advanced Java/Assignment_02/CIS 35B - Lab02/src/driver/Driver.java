package driver;

import model.Automobile;
import util.FileIO;
import adapter.BuildAuto;
import adapter.CreateAuto;
import adapter.UpdateAuto;

public class Driver {
    public static void main(String[] args) {
        // Try to create Automobile using an input file that contains invalid
        // base price. Verify that program self heals itself and creates
        // Automobile object using defaultFile.txt.
        CreateAuto a1 = new BuildAuto();
        a1.buildAuto("FordZTW.txt");
        a1.printAuto("FordZTW");

        // Test Update Auto methods.
        UpdateAuto b2 = new BuildAuto();
        b2.updateOptionPrice("FordZTW", "transmission", "automatic", 200.0f);
        b2.updateOptionSetName("FordZTW", "transmission", "Semi-Automatic");
        
        System.out.println("\nUpdated Automobile properties are:");
        a1.printAuto("UpdatedFordZTW");
    }
}
