
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
public class GUI extends JFrame implements ActionListener {

    private JButton connectButton,startButton,stopButton,clearButton,closeButton,
                    aButton,bButton,cButton,dButton,eButton,fButton,button1,button2,button3,button4,button5,button6;
    private Panel p;
    private PaintPanel paintPanel;
    private JTextArea console;
    private JScrollPane scrollpane;

    public GUI() {
        //JFrame frame = new JFrame("Visualization Robot");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Visualization Robot");
        //Display the window.
        setLayout(null);
        p = new Panel();
        p.setSize(190, 700);
        p.setLayout(null);
        connectButton = new JButton("Connect to Robot");
        startButton = new JButton("Start Visualization");
        stopButton = new JButton("Stop Visualization");
        clearButton = new JButton("Clear Visualization");
        clearButton.addActionListener(this);
        closeButton = new JButton("Close Visualization");
        connectButton.setBounds(20, 20, 150, 30);
        startButton.setBounds(20, 60, 150, 30);
        stopButton.setBounds(20, 100, 150, 30);
        clearButton.setBounds(20, 140, 150, 30);
        closeButton.setBounds(20, 450, 150, 30);
        closeButton.addActionListener(this);
        p.add(connectButton);
        p.add(startButton);
        p.add(stopButton);
        p.add(clearButton);
        p.add(closeButton);
        console = new JTextArea(10,20);
        console.append("Visualization started...");
        scrollpane = new JScrollPane(console,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        scrollpane.setBounds(20,190,150,240);
        p.add(scrollpane);
        aButton = new JButton("A");
        aButton.setBounds(695,30,100,30);
        aButton.addActionListener(this);
        add(aButton);
        bButton = new JButton("B");
        bButton.setBounds(695,110,100,30);
        bButton.addActionListener(this);
        add(bButton);
        cButton = new JButton("C");
        cButton.setBounds(695,190,100,30);
        cButton.addActionListener(this);
        add(cButton);
        dButton = new JButton("D");
        dButton.setBounds(695,270,100,30);
        dButton.addActionListener(this);
        add(dButton);
        eButton = new JButton("E");
        eButton.setBounds(695,350,100,30);
        eButton.addActionListener(this);
        add(eButton);
        fButton = new JButton("F");
        fButton.setBounds(695,430,100,30);
        fButton.addActionListener(this);
        add(fButton);
        button1 = new JButton("1");
        button1.setBounds(215,510,50,100);
        button1.addActionListener(this);
        add(button1);
        button2 = new JButton("2");
        button2.setBounds(295,510,50,100);
        button2.addActionListener(this);
        add(button2);
        button3 = new JButton("3");
        button3.setBounds(375,510,50,100);
        button3.addActionListener(this);
        add(button3);
        button4 = new JButton("4");
        button4.setBounds(455,510,50,100);
        button4.addActionListener(this);
        add(button4);
        button5 = new JButton("5");
        button5.setBounds(535,510,50,100);
        button5.addActionListener(this);
        add(button5);
        button6 = new JButton("6");
        button6.setBounds(615,510,50,100);
        button6.addActionListener(this);
        add(button6);
        getContentPane().add(p, BorderLayout.WEST);
        paintPanel = new PaintPanel();
        paintPanel.setBackground(Color.WHITE);
        paintPanel.setBounds(190, 0, 500, 500);
        getContentPane().add(paintPanel, BorderLayout.CENTER);
        pack();
        setSize(815, 655);
        setVisible(true);
    }

    public static void main(String[] args) {
        GUI gui = new GUI();
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == closeButton) {
            int response;
            response = JOptionPane.showConfirmDialog(null, "Do you really want to close this program?");

            if(response == 0){
                System.exit(0);
            }
        }
        if (e.getSource() == aButton){
            paintPanel.setPosY(1);
            console.append("\nNew Y Start Position: 1");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == bButton){
            paintPanel.setPosY(2);
            console.append("\nNew Y Start Position: 2");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == cButton){
            paintPanel.setPosY(3);
            console.append("\nNew Y Start Position: 3");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == dButton){
            paintPanel.setPosY(4);
            console.append("\nNew Y Start Position: 4");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == eButton){
            paintPanel.setPosY(5);
            console.append("\nNew Y Start Position: 5");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == fButton){
            paintPanel.setPosY(6);
            console.append("\nNew Y Start Position: 6");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == button1){
            paintPanel.setPosX(1);
            console.append("\nNew X Start Position: 1");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == button2){
            paintPanel.setPosX(2);
            console.append("\nNew X Start Position: 2");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == button3){
            paintPanel.setPosX(3);
            console.append("\nNew X Start Position: 3");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == button4){
            paintPanel.setPosX(4);
            console.append("\nNew X Start Position: 4");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == button5){
            paintPanel.setPosX(5);
            console.append("\nNew X Start Position: 5");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if (e.getSource() == button6){
            paintPanel.setPosX(6);
            console.append("\nNew X Start Position: 6");
            console.setCaretPosition(console.getText().length() - 1);
            paintPanel.repaint();
        }
        if(e.getSource() == clearButton){
            paintPanel.emptyList();
            console.setText("Visualization started...");
            console.setCaretPosition(console.getText().length() - 1);
        }
    }
}
