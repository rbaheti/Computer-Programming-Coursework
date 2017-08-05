package model;

import java.io.*;
import java.util.ArrayList;

public class OptionSet implements Serializable {
    private ArrayList<Option> optsList;
    private String            name;
    private Option            choice;

    // default constructor
    public OptionSet() {
        name = "";
        choice = null;
        optsList = new ArrayList<Option>();
    }

    // parameterized constructor
    public OptionSet(String name, int size) {
        this.name = name;
        choice = null;
        optsList = new ArrayList<Option>();
    }

    // OptionSet getters:
    protected ArrayList<Option> getOpts() {
        return optsList;
    }
    
    protected ArrayList<String> getOptNames() {
        ArrayList<String> names = new ArrayList<String>();
        for (int i = 0; i < optsList.size(); ++i) {
            Option opt = optsList.get(i);
            names.add(opt.getName());
        }
        return names;
    }

    protected String getName() {
        return name;
    }

    // getOptionChoice() returns user choice
    protected Option getOptionChoice() {
        return choice;
    }

    // getChoicePrice() returns user choice price
    protected float getChoicePrice() {
        return choice.getPrice();
    }

    // OptionSet setters:
    protected void setOpt(ArrayList<Option> optsList) {
        this.optsList = optsList;
    }

    protected void setName(String name) {
        this.name = name;
    }

    // setOptionChoice() sets user choice for given option name
    protected void setOptionChoice(String optionName) {
        for (int i = 0; i < optsList.size(); ++i) {
            Option opt = optsList.get(i);
            if (opt.getName().equalsIgnoreCase(optionName)) {
                choice = opt;
            }
        }
    }

    // addOption() adds new Option to the OptionSet
    protected void addOption(Option option) {
        optsList.add(option);
    }

    // findOption() finds option by optionName in the OptionSet
    protected Option findOption(String optionName) {
        for (int i = 0; i < optsList.size(); ++i) {
            Option opt = optsList.get(i);
            if (opt.getName().equalsIgnoreCase(optionName)) {
                return opt;
            }
        }
        return null;
    }

    // deleteOption()
    protected boolean deleteOption(String OptionName) {
        Option opt = findOption(OptionName);
        // if option not found, return false
        if (opt == null)
            return false;

        ArrayList<Option> newOptionList = new ArrayList<Option>();
        for (int i = 0; i < optsList.size() - 1; ++i) {
            Option optInList = optsList.get(i);
            if (optInList != opt)
                newOptionList.set(i, optInList);
        }
        optsList = newOptionList;
        return true;
    }
    
    protected float getOptionPrice(String OptionName) {
        Option opt = findOption(OptionName);
        // if option not found, return false
        if (opt == null) {
            return 0;
        }
        
        return opt.getPrice();
    }

    public String toString() {
        StringBuffer stringBuffer = new StringBuffer();
        stringBuffer.append("OptionSet Name: ").append(name);
        String str = stringBuffer.toString();
        return str;
    }

    // print() prints automotive object's attributes
    protected void print() {
        System.out.println(toString());
        for (int i = 0; i < optsList.size(); ++i) {
            Option opt = optsList.get(i);
            opt.print();
        }
    }

    // updateOptionPrice updates price of given Option Name
    protected void updateOptionPrice(String optionName, float newprice) {
        for (int i = 0; i < optsList.size(); ++i) {
            Option opt = optsList.get(i);
            if (opt.getName().equalsIgnoreCase(optionName)) {
                opt.setPrice(newprice);
            }
        }
    }

    // Inner class Option
    public class Option implements Serializable {
        private String name;
        private float  price;

        // default constructor
        public Option() {
            name = "NULL";
            price = 0;
        }

        // Option class getters
        protected String getName() {
            return name;
        }

        protected float getPrice() {
            return price;
        }

        // Option class setters
        protected void setName(String name) {
            this.name = name;
        }

        protected void setPrice(Float price) {
            this.price = price;
        }

        // toString() converts buffered string to a string
        public String toString() {
            StringBuffer stringBuffer = new StringBuffer();
            stringBuffer.append("Option Name: ").append(name)
                    .append(", Price: $").append(price);
            String str = stringBuffer.toString();
            return str;
        }

        // print() prints Option object's attributes
        protected void print() {
            System.out.println(toString());
        }
    }
}
