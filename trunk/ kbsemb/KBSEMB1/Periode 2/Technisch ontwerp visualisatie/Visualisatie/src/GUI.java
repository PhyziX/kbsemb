
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Gerhard
 */
public class GUI extends JFrame implements ActionListener{
    private JButton button1;
    private JButton button2;
    private JButton button3;
    private JButton button4;
    private JButton button5;
    private Panel p;

    public GUI(){
        //JFrame frame = new JFrame("Visualization Robot");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Visualization Robot");
        //Display the window.
        setLayout(null);
        p = new Panel();
        p.setSize(190,700);
		p.setLayout(null);
        button1 = new JButton("Connect to Robot");
        button2 = new JButton("Start Visualization");
        button3 = new JButton("Stop Visualization");
        button4 = new JButton("Clear Visualization");
        button5 = new JButton("Close Visualization");
        button1.setBounds(20,20,150,30);
        button2.setBounds(20,60,150,30);
        button3.setBounds(20,100,150,30);
        button4.setBounds(20,140,150,30);
        button5.setBounds(20,450,150,30);
        button5.addActionListener(this);
        p.add(button1);
        p.add(button2);
        p.add(button3);
        p.add(button4);
        p.add(button5);
        getContentPane().add(p,BorderLayout.WEST);
        PaintPanel p1 = new PaintPanel();
        p1.setBackground(Color.WHITE);
        p1.setBounds(190, 0, 500, 500);
        getContentPane().add(p1,BorderLayout.CENTER);
        pack();
        setSize(705, 535);
        setVisible(true);
    }

    public static void main(String[] args) {
        GUI gui = new GUI();
    }

    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == button5){
            System.exit(0);
        }
    }
}
