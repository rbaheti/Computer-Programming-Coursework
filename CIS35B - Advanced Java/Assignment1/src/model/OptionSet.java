package model;

import java.io.*;

public class OptionSet implements Serializable {
    private Option opts[];
    private String name;
    private int    nextInsertPosition;

    // default constructor
    public OptionSet() {
        opts = null;
        name = "";
        nextInsertPosition = 0;
    }

    // parameterized constructor
    public OptionSet(String name, int size) {
        opts = new Option[size];
        this.name = name;
        nextInsertPosition = 0;
    }

    // OptionSet getters:
    protected Option[] getOpts() {
        return opts;
    }

    protected String getName() {
        return name;
    }

    // OptionSet setters:
    protected void setOpt(Option[] opts) {
        this.opts = opts;
    }

    protected void setName(String name) {
        this.name = name;
    }

    // addOption() adds new Option to the OptionSet
    protected void addOption(Option option) {
        opts[nextInsertPosition] = option;
        nextInsertPosition++;
    }

    // findOption() finds option by optionName in the Option set
    protected Option findOption(String optionName) {
        for (int i = 0; i < opts.length; ++i) {
            if (opts[i].getName().equalsIgnoreCase(optionName)) {
                opts[i].print();
                return opts[i];
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

        Option[] newOptions = new Option[opts.length - 1];
        for (int i = 0; i < opts.length - 1; ++i) {
            if (opts[i] != opt)
                newOptions[i] = opts[i];
        }
        opts = newOptions;
        return true;
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
        for (int i = 0; i < opts.length; ++i) {
            opts[i].print();
        }
    }

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
