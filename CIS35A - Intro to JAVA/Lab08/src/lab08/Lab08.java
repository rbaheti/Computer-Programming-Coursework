package lab08;

import static java.lang.Thread.sleep;

class Tunnel {

    synchronized void GoingThroughTunnel(int num) {
        System.out.println("Train " + num + " entered in the tunnel");
        try {
            sleep(1000);
        } catch (Exception e) {
        }
        System.out.println("Train " + num + " exited the tunnel");
    }
}

class Train extends Thread {

    int num;
    Tunnel t;

    Train(Tunnel t, int num) {
        this.t = t;
        this.num = num;
    }

    public void run() {
        t.GoingThroughTunnel(num);
    }
}

public class Lab08 {

    public static void main(String[] args) {
        Tunnel tunnel_obj = new Tunnel();
        Train train_obj[] = new Train[10];
        for (int i = 0; i < 10; ++i) {
            train_obj[i] = new Train(tunnel_obj, i + 1);
        }
        for (int i = 0; i < 10; ++i) {
            train_obj[i].start();
        }

    }
}
