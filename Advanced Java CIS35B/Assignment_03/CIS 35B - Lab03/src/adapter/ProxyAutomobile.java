package adapter;

import exception.AutoException;
import model.*;
import util.*;

public abstract class ProxyAutomobile {
    private static Automobile autoObj;

    // Given a text file name, buildAuto() builds an instance of Automobile.
    public void buildAuto(String filename) {
        try {
            FileIO fileIO = new FileIO();
            autoObj = fileIO.readFile(filename);
        } catch (AutoException ae) {
            autoObj = ae.fix();
        }
    }

    // printAuto() searches and prints the properties of a given Automobile.
    public void printAuto(String modelname) {
        System.out.println("Properties of " + modelname + " are:");
        autoObj.print();
    }

    // updateOptionSetName() searches the model for a given OptionSet and sets
    // the name of OptionSet to newName.
    public void updateOptionSetName(String modelname, String optionSetName,
            String newName) {
        autoObj.updateOptionSetName(optionSetName, newName);
    }

    // updateOptionPrice() searches the Model for a given OptionSet and Option
    // name, and sets the price to newPrice.
    public void updateOptionPrice(String modelname, String optionSetName,
            String optionName, float newprice) {
        autoObj.updateOptionPrice(optionSetName, optionName, newprice);
    }

    // fix() fixes the error encountered and returns the fixed Automobile
    // object.
    public Automobile fix(int errno) {
        AutoException ae = new AutoException(errno);
        return ae.fix();
    }
}
