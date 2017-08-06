/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 *
 * @author RASHMI
 */
public class NewJApplet extends JApplet {

    /**
     * Initialization method that will be called after the applet is loaded into
     * the browser.
     */
    JTextField tfield;
    ButtonGroup bgroup;
    JRadioButton rb1, rb2, rb3;
    ActionListener alistener; 
    
    public void init() {
        tfield = new javax.swing.JTextField(15);
        tfield.setEditable(false);
        
        rb1 = new JRadioButton("1", false);
        rb2 = new JRadioButton("2", false);
        rb3 = new JRadioButton("3", false);
        alistener = new ActionListener() 
        {
            public void actionPerformed(ActionEvent e) 
            {
                tfield.setText("Radio Button #" + ((JRadioButton)e.getSource()).getText());
            }
        };
        rb1.addActionListener(alistener);
	rb2.addActionListener(alistener);
	rb3.addActionListener(alistener);
        
        bgroup = new javax.swing.ButtonGroup();
        bgroup.add(rb1);
        bgroup.add(rb2);
        bgroup.add(rb3);
        
	java.awt.Container cp = getContentPane();
	cp.setLayout(new java.awt.FlowLayout());
        cp.add(tfield);
	cp.add(rb1);
	cp.add(rb2);
	cp.add(rb3);    
        // TODO start asynchronous download of heavy resources
    }
    
    public static void main(String[] args) 
    {
        JApplet applet = new NewJApplet();
	JFrame frame = new javax.swing.JFrame("Radio Buttons");
	frame.setDefaultCloseOperation(javax.swing.JFrame.EXIT_ON_CLOSE);
	frame.getContentPane().add(applet);
	frame.setSize(200, 100);
	applet.init();
	applet.start();
        frame.setVisible(true);
    }

    // TODO overwrite start(), stop() and destroy() methods
}
