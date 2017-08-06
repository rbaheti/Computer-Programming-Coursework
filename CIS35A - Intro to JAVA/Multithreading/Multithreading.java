package multithreading;

class A extends Thread {

    public void run() {
        for (int i = 0; i < 5; ++i) {
            if (i == 1) {
                yield();
            }
            System.out.println("\t From thread A: i = " + i);
        }
        System.out.println("Exit from A class ");
    }
}

class B extends Thread {

    public void run() {
        for (int i = 0; i < 5; ++i) {
            if (i == 3) {
                stop();
            }
            System.out.println("\t From thread B: i = " + i);
        }
        System.out.println("Exit from B class");
    }
}

class C extends Thread {

    public void run() {
        for (int i = 0; i < 5; ++i) {
            if (i == 2) {
                try {
                    sleep(5000);
                } catch (Exception e) {
                }
            }
            System.out.println("\t From thread C: i = " + i);
        }
        System.out.println("Exit from C class");
    }
}

public class Multithreading {

    public static void main(String[] args) {
        A a = new A();
        B b = new B();
        C c = new C();
        System.out.println("Class A starts");
        a.start();
        System.out.println("Class B starts");
        b.start();
        System.out.println("Class C starts");
        c.start();
    }
}
