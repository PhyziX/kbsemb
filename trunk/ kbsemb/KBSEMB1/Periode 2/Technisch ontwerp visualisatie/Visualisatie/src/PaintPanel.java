
import java.awt.*;
import javax.swing.*;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Gerhard
 */
public class PaintPanel extends JPanel {

    public PaintPanel(){
        setSize(500, 500);
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        setBackground(Color.WHITE);
        g.setColor(Color.GRAY);
        g.drawLine(10,10,490,10);
        g.drawLine(490,10,490,490);
        g.drawLine(10,490,410,490);
        g.drawLine(10,10,10,90);
        g.drawLine(10,170,10,490);
        g.drawLine(90,10,90,170);
        g.drawLine(10,250,170,250);
        g.drawLine(170,250,170,90);
        g.drawLine(170,90,250,90);
        g.drawLine(330,10,330,90);
        g.drawLine(410,90,410,250);
        g.drawLine(410,250,490,250);
        g.drawLine(410,170,250,170);
        g.drawLine(250,170,250,250);
        g.drawLine(90,330,170,330);
        g.drawLine(170,330,170,410);
        g.drawLine(170,410,90,410);
        g.drawLine(90,410,90,490);
        g.drawLine(250,330,250,410);
        g.drawLine(250,410,330,410);
        g.drawLine(330,490,330,250);
        g.drawLine(330,410,410,410);
        g.drawLine(410,410,410,330);
        /*for(int v = 10; v <= 490; v += 80) {
             g.drawLine(v, 10, v, 490);
        }
        for(int h = 10; h <= 490; h += 80) {
             g.drawLine(10, h, 490, h);
        }*/

        paintRobot(g);
    }

    public void paintRobot(Graphics g){
        g.setColor(Color.RED);
        g.fillOval(445, 445, 10, 10);
    }

}
