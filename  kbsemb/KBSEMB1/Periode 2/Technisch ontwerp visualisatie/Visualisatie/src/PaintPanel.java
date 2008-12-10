
import java.awt.*;
import java.util.ArrayList;
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
    public int posX = 6;
    public int posY = 6;
    public ArrayList<int[]> moveList;

    public PaintPanel(){
        moveList = new ArrayList<int[]>();
        makeMove(6,5);
        makeMove(6,4);
        makeMove(5,4);
        makeMove(5,3);
        makeMove(4,3);
        makeMove(4,4);
        makeMove(3,4);
        makeMove(3,3);
        makeMove(3,2);
        makeMove(4,2);
        makeMove(4,1);
        makeMove(3,1);
        makeMove(2,1);
        makeMove(2,2);
        makeMove(2,3);
        makeMove(1,3);
        makeMove(1,2);
        
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

        paintRobot(g,((posX * 80) - 35),((posY * 80) - 35));

        if(!moveList.isEmpty()){
            for (int i=0; i < moveList.size(); i++) {
                int[] pos = moveList.get(i);
                if(i == 0){
                    g.drawLine(((posX * 80) - 30), ((posY * 80) - 30), ((pos[0] * 80) - 30), ((pos[1] * 80) - 30));
                }
                else{
                    int[] prevPos = moveList.get(i -1);
                    g.drawLine(((prevPos[0] * 80) - 30), ((prevPos[1] * 80) - 30), ((pos[0] * 80) - 30), ((pos[1] * 80) - 30));
                }
            }
        }
    }

    public void paintRobot(Graphics g,int x,int y){
        g.setColor(Color.RED);
        g.fillOval(x, y, 10, 10);
    }

    public void setPosY(int y){
        posY = y;
    }

    public void setPosX(int x){
        posX = x;
    }

    public void emptyList(){
        moveList.clear();
        posX = 6;
        posY = 6;
        repaint();
    }

    public void makeMove(int x,int y){
        int[] nextPos = {x,y};
        moveList.add(nextPos);
        repaint();
    }

}
