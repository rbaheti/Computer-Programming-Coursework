package driver;

import model.Automobile;
import adapter.BuildAuto;

public class Driver {
    public static void main(String[] args) {

        BuildAuto a1 = new BuildAuto();
        a1.buildAuto("FordZTW.txt");
        {
            // Test case 1.
            System.out.println();
            String[] inputs1 = { "Focus Wagon ZTW", "Transmission", "automatic",
                    "default" };
            a1.edit(1 /* update name */, inputs1, true /* synchronized */);

            String[] inputs2 = { "Focus Wagon ZTW", "Transmission", "automatic",
                    "non-standard" };
            a1.edit(1 /* update name */, inputs2, true /* synchronized */);

            try {
                Thread.sleep(2000);
            } catch (InterruptedException ie) {
            }
            System.out.println(
                    inputs1[1] + " OptionSet contains these options now:");
            Automobile auto = a1.getAuto("Focus Wagon ZTW");
            auto.printOptionSet(inputs1[1]);
        }
        {
            // Test case 2.
            System.out.println();
            String[] inputs1 = { "Focus Wagon ZTW", "Color",
                    "Fort Knox Gold Clearcoat Metallic", "Gold" };
            a1.edit(1 /* update name */, inputs1, false /* non-synchronized */);

            String[] inputs2 = { "Focus Wagon ZTW", "Color",
                    "Fort Knox Gold Clearcoat Metallic", "Gold Metallic" };
            a1.edit(1 /* update name */, inputs2, false /* non-synchronized */);

            try {
                Thread.sleep(2000);
            } catch (InterruptedException ie) {
            }
            System.out.println(
                    inputs1[1] + " OptionSet contains these options now:");
            Automobile auto = a1.getAuto("Focus Wagon ZTW");
            auto.printOptionSet(inputs1[1]);
        }
        {
            // Test case 3.
            System.out.println();
            String[] inputs1 = { "Focus Wagon ZTW", "Transmission", "standard",
                    "-1000" };
            a1.edit(2 /* update price */, inputs1, true /* synchronized */);

            String[] inputs2 = { "Focus Wagon ZTW", "Transmission", "standard",
                    "-1500" };
            a1.edit(2 /* update price */, inputs2, true /* synchronized */);

            try {
                Thread.sleep(2000);
            } catch (InterruptedException ie) {
            }
            System.out.println(
                    inputs1[1] + " OptionSet contains these options now:");
            Automobile auto = a1.getAuto("Focus Wagon ZTW");
            auto.printOptionSet(inputs1[1]);
        }
    }
}
