package model;

import java.io.*;

public class Automotive implements Serializable {
    private String    name;
    private float     basePrice;
    private OptionSet opsets[];
    private int       nextInsertPosition;

    // default constructor
    public Automotive() {
        name = "";
        basePrice = 0f;
        opsets = null;
        // initializing counter to 0
        nextInsertPosition = 0;
    }

    // parameterized constructor
    public Automotive(String name, float basePrice, int optionSetSize) {
        opsets = new OptionSet[optionSetSize];
        this.name = name;
        this.basePrice = basePrice;
        // initializing counter to 0
        nextInsertPosition = 0;
    }

    // getters
    public String getName() {
        return name;
    }

    public float getBasePrice() {
        return basePrice;
    }

    public OptionSet getOpsets(int i) {
        return opsets[i];
    }

    // setters
    public void setName(String name) {
        this.name = name;
    }

    public void setBasePrice(float basePrice) {
        this.basePrice = basePrice;
    }

    public void setOpset(OptionSet[] opsets) {
        this.opsets = opsets;
    }

    // toString() converts buffered string to a string
    public String toString() {
        StringBuffer stringBuffer = new StringBuffer();
        stringBuffer.append("Automotive Name: ").append(name)
                .append("Base Price: ").append(basePrice);
        String str = stringBuffer.toString();
        return str;
    }

    // print() prints automotive object's attributes
    public void print() {
        System.out.println(toString());
        for (int i = 0; i < opsets.length; ++i) {
            opsets[i].print();
        }
    }

    // addOptionSet() adds optionSet in the optionSet array
    public void addOptionSet(String str, int length) {
        OptionSet optset = new OptionSet(str, length);
        opsets[nextInsertPosition] = optset;
        nextInsertPosition++;
    }

    // addOption() adds option in the required OptionSet.
    public void addOption(String optionSetName, String optionName,
            float price) {
        for (int i = 0; i < opsets.length; ++i) {
            OptionSet.Option opt = opsets[i].new Option();
            if (opsets[i].getName() == optionSetName) {
                opt.setName(optionName);
                opt.setPrice(price);
                opsets[i].addOption(opt);
                break;
            }
        }
    }

    // findOptionSet() searches for the required optionSet using optionSetName
    // and returns OptionSet object if found else null.
    public OptionSet findOptionSet(String optionSetName) {
        for (int i = 0; i < opsets.length; ++i) {
            if (opsets[i].getName().equalsIgnoreCase(optionSetName)) {
                opsets[i].print();
                return opsets[i];
            }
        }
        return null;
    }

    // findOption() searches for the option in the required optionSet using
    // optionName and returns option object if found else null.
    public OptionSet.Option findOption(String optionSetName,
            String optionName) {
        for (int i = 0; i < opsets.length; ++i) {
            if (opsets[i].getName().equalsIgnoreCase(optionSetName)) {
                return opsets[i].findOption(optionName);
            }
        }
        return null;
    }

    // deleteOptionSet() deletes the required optionset from the option set
    // array
    public boolean deleteOptionSet(String optionSetName) {
        OptionSet opset = findOptionSet(optionSetName);
        if (opset == null)
            return false;

        OptionSet[] newOptset = new OptionSet[opsets.length - 1];
        for (int j = 0; j < opsets.length - 1; ++j) {
            if (opsets[j] != opset) {
                newOptset[j] = opsets[j];
            }
        }
        opsets = newOptset;
        return true;
    }

    // deleteOption() deletes the required option from the optionSetArray
    public boolean deleteOption(String optionSetName, String optionName) {
        OptionSet opset = findOptionSet(optionSetName);
        if (opset != null) {
            return opset.deleteOption(optionName);
        }
        return false;
    }
}
