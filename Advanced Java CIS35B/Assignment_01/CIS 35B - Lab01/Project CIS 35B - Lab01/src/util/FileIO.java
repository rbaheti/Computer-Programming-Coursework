package util;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.*;

import model.Automotive;

public class FileIO {
    
    // read a file and store its attributes in Automotive object
    public Automotive readFile(String fileName) {
        Automotive automotive = null;
        try {
            FileReader file = new FileReader(fileName);
            BufferedReader buff = new BufferedReader(file);
            boolean eof = false;

            // read and store base price in automotive object
            if (!eof) {
                String line = buff.readLine();
                if (line == null)
                    eof = true;
                else {
                    String[] retval = line.split(":");
                    float basePrice = Float.parseFloat(retval[1]);
                    automotive = new Automotive("Focus Wagon ZTW", basePrice,
                            5);
                }
            }
            while (!eof) {
                final String line = buff.readLine();
                if (line == null)
                    eof = true;
                else {
                    final String[] lineParts = line.split(":");
                    String[] options = lineParts[1].split(";");
                    automotive.addOptionSet(lineParts[0].trim(),
                            options.length);
                    for (int i = 0; i < options.length; ++i) {
                        String[] optionAttributes = options[i].split(",");
                        automotive.addOption(lineParts[0].trim(),
                                optionAttributes[0].trim(),
                                Float.parseFloat(optionAttributes[1]));
                    }
                }
            }
            buff.close();
        } catch (IOException e) {
            System.out.println("Error -- " + e.toString());
        }
        return automotive;
    }

    // serialize Automotive object in a file
    public void serializeAuto(Automotive automotive) {
        try {
            FileOutputStream fileOut = new FileOutputStream("auto.ser");
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(automotive);
            out.close();
            fileOut.close();
            System.out.println("Serialized data is saved in auto.ser");
        } catch (IOException i) {
            i.printStackTrace();
        }
    }

    // deserialize Automotive object from given file
    public Automotive deserializeAuto(String fileName) {
        Automotive automotive = null;
        try {
            FileInputStream fileIn = new FileInputStream(fileName);
            ObjectInputStream in = new ObjectInputStream(fileIn);
            automotive = (Automotive) in.readObject();
            in.close();
            fileIn.close();
            return automotive;
        } catch (IOException i) {
            i.printStackTrace();
            return null;
        } catch (ClassNotFoundException c) {
            System.out.println("Automotive class not found");
            c.printStackTrace();
            return null;
        }
    }
}
