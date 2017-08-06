/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import javax.swing.JApplet;

/**
 *
 * @author RASHMI
 */
public class NewJApplet extends JApplet {

    /**
     * Initialization method that will be called after the applet is loaded into
     * the browser.
     */
    		javax.swing.JTextField t = new javax.swing.JTextField(15);
		javax.swing.ButtonGroup g = new javax.swing.ButtonGroup();
		javax.swing.JRadioButton
                    rb1 = new javax.swing.JRadioButton("one", false),
                    rb2 = new javax.swing.JRadioButton("two", false),
                    rb3 = new javax.swing.JRadioButton("three", false);

    public void init() {
        g.add(rb1);
        g.add(rb2);
        g.add(rb3);
	java.awt.Container cp = getContentPane();
	cp.add(t);
	cp.add(rb1);
	cp.add(rb2);
	cp.add(rb3);    
        // TODO start asynchronous download of heavy resources
    }
    
    public static void main(String[] args) 
	  {
		  	JApplet applet = new NewJApplet();
		  	javax.swing.JFrame frame = new javax.swing.JFrame("Radio Buttons");
		  	frame.setDefaultCloseOperation(javax.swing.JFrame.EXIT_ON_CLOSE);
			frame.getContentPane().add(applet);
			frame.setSize(200, 100);
			applet.init();
			applet.start();
                        System.out.println("here");
			frame.setVisible(true);
	  }

    // TODO overwrite start(), stop() and destroy() methods
}
