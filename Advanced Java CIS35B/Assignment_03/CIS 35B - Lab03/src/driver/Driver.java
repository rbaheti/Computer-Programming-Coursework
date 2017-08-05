package driver;

import model.Automobile;
import model.AutomobileStore;
import util.FileIO;
import adapter.BuildAuto;
import adapter.CreateAuto;
import adapter.UpdateAuto;
import exception.AutoException;

public class Driver {
    public static void main(String[] args) {
        Automobile autoObj;
        try {
            FileIO fileIO = new FileIO();
            autoObj = fileIO.readFile("defaultFile.txt");
        } catch (AutoException ae) {
            autoObj = ae.fix();
        }
        
        System.out.println("Testing user automobile choice:");
        
        autoObj.setOptionChoice("transmission", "standard");
        System.out.println("Choice Name: " + autoObj.getOptionChoice("Transmission"));
        autoObj.setOptionChoice("Power Moonroof", "yes");
        System.out.println("Choice Price: " + autoObj.getOptionChoicePrice("transmission"));
        
        System.out.println("Total Price: " + autoObj.getTotalPrice());
        
        AutomobileStore autoStore = new AutomobileStore();
        autoStore.addAuto("Focus Wagon ZTW", autoObj);
        Automobile autoTest = autoStore.getAuto("Focus Wagon ZTW");
        if(autoTest != null)
            System.out.println("Base price of Focus Wagon ZTW is: " + autoTest.getBasePrice());
        else
            System.out.println("Focus Wagon ZTW model does not exists in the system.");
        
        Automobile autoTest2 = autoStore.getAuto("Honda Accord");
        if(autoTest2 != null)
            System.out.println("Base price is: " + autoTest.getBasePrice());
        else
            System.out.println("Honda Accord model does not exists in the system.");
    }
}
