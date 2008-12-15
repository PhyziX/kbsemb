import java.util.*;
import javax.comm.*;
import java.io.*;

public class Connection implements Runnable, SerialPortEventListener
{
    // Initialize variables
    static int START_X = 6, START_Y = 6, INITIALIZE_ROBOT = 100, NEXT_X = 101, NEXT_Y = 102;
    String drivername = "com.sun.comm.Win32Driver",
            defaultPort = "COM1", appName = "comm", next = "";
    Enumeration portlist;
    CommPortIdentifier cpi = null;
    SerialPort port;
    InputStream input;
    int baudrate, data, modX, modY, nextX, nextY;
    Thread readThread;
    BufferedReader read;
    GUI gui;

    // Constructor
    public Connection(GUI gui)
    {
        this.gui = gui;
    }

    public void serialEvent(SerialPortEvent spEvent)
    {
       try{
            // Listen to port, and print incoming data
            int eventType = spEvent.getEventType();
            if(eventType == SerialPortEvent.DATA_AVAILABLE)
            {
                try{
                    data = input.read();
                    // Initializion number
                    if(data == INITIALIZE_ROBOT){
                        modX = START_X - gui.paintPanel.posX;
                        modY = START_Y - gui.paintPanel.posY;
                        gui.console.append("\nRobot initialized");
                    }
                    if(next.equals("x")){
                        nextX = data - modX;
                        next = "";
                    }
                    if(next.equals("y")){
                        nextY = data - modY;
                        next = "";
                        gui.paintPanel.makeMove(nextX, nextY);
                    }
                    if(data == NEXT_X){
                        next = "x";
                        gui.console.append("\nx");
                    }
                    if(data == NEXT_Y){
                        next = "y";
                        gui.console.append("\ny");
                    }
                }
                catch(IOException ioe){
                    System.out.println(ioe.getMessage());
                }
            }
       }
       catch(Exception e){
           //
       }
    }

    public boolean connect(){
                // Initialize driver
        try{
            CommDriver driver = (CommDriver) Class.forName(drivername).newInstance();
            driver.initialize();
        }
        catch(IllegalAccessException iae){
            System.out.println(iae.getMessage());
        }
        catch(InstantiationException ie){
            System.out.println(ie.getMessage());
        }
        catch(ClassNotFoundException cnfe){
            System.out.println(cnfe.getMessage());
        }

        // Get list of available ports
        portlist = CommPortIdentifier.getPortIdentifiers();
        cpi = (CommPortIdentifier) portlist.nextElement();

        // Check if the needed port is on the port list
        while ((portlist.hasMoreElements()) && (!cpi.getName().equals(defaultPort)))
        {
            cpi = (CommPortIdentifier) portlist.nextElement();
        }

        // Try to open the needed port
        try{
            port = (SerialPort) cpi.open(appName, 2000);
        }
        catch(PortInUseException piue){
            System.out.println(piue.getMessage());
        }

        // Make an inputStream for the port
        try{
            input = port.getInputStream();
        }
        catch(IOException ioe){
            System.out.println(ioe.getMessage());
        }

        // Add evenlistener to port, to start listening to incoming data
        try{
            port.addEventListener(this);
            //read = new BufferedReader(input);
        }
        catch(TooManyListenersException tmle){
            System.out.println(tmle.getMessage());
        }

        // Set notify interrupt, in case incoming data is available
        port.notifyOnDataAvailable(true);
        try{
            port.setSerialPortParams(9600, SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
        }
        catch(UnsupportedCommOperationException ucoe){
            System.out.println(ucoe.getMessage());
        }

        // Notfiy sender that application is ready to receive data
        port.setDTR(true);
        System.out.println("Aangesloten");

        // Start thread to listen to port
        readThread = new Thread(this);
        readThread.start();

        gui.console.append("\nConnection Succesful");
        return true;
    }

    public void run()
    {
        
    }
}
