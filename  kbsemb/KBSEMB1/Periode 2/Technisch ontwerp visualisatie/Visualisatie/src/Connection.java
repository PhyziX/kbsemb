import java.util.*;
import javax.comm.*;
import java.io.*;

public class Connection implements Runnable, SerialPortEventListener
{
    // Initialize variables
    static int START_X = 6, START_Y = 6, INITIALIZE_ROBOT = 100, NEXT_X = 101, NEXT_Y = 102;
    String drivername = "com.sun.comm.Win32Driver",
            defaultPort = "COM7", appName = "comm", next = "";
    Enumeration portlist;
    CommPortIdentifier cpi = null;
    SerialPort port;
    InputStream input;
    int baudrate, data, modX, modY, nextX, nextY;
    Thread readThread;
    BufferedReader read;
    GUI gui;
    boolean connected;

    // Constructor
    public Connection(GUI gui)
    {
        this.gui = gui;
    }

    public void serialEvent(SerialPortEvent spEvent)
    {
        int eventType = spEvent.getEventType();
        if(eventType == SerialPortEvent.DATA_AVAILABLE)
        {
            try{
                data = input.read();
                // Initializion number
                gui.console.append("\n"+data);
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
                    gui.console.append("\nJa! Y");
                }
                if(data == NEXT_X){
                    next = "x";
                }
                else if(data == NEXT_Y){
                    next = "y";
                }
            }
            catch(IOException ioe){
                gui.console.append("\nI/O Exception");
            }
        }
    }

    public void connect(){
                // Initialize driver
        try{
            CommDriver driver = (CommDriver) Class.forName(drivername).newInstance();
            driver.initialize();
        }
        catch(IllegalAccessException iae){
            gui.console.append("\nIllegal access exception while loading driver");
        }
        catch(InstantiationException ie){
            gui.console.append("\nInstantiation exception while loading driver");
        }
        catch(ClassNotFoundException cnfe){
            gui.console.append("\nDriver class not found");
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
            gui.console.append("\nPort currently in use");
        }

        // Make an inputStream for the port
        try{
            input = port.getInputStream();
        }
        catch(IOException ioe){
            gui.console.append("\nI/O exception while creating inputstream");
        }

        // Add evenlistener to port, to start listening to incoming data
        try{
            port.addEventListener(this);
            //read = new BufferedReader(input);
        }
        catch(TooManyListenersException tmle){
            gui.console.append("\nToo many listeners on port");
        }

        // Set notify interrupt, in case incoming data is available
        port.notifyOnDataAvailable(true);
        try{
            port.setSerialPortParams(9600, SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
        }
        catch(UnsupportedCommOperationException ucoe){
            gui.console.append("\nUnsupported comm operation error while setting port settings");
        }

        // Notfiy sender that application is ready to receive data
        port.setDTR(true);

        // Start thread to listen to port
        readThread = new Thread(this);
        readThread.start();

        gui.console.append("\nConnection succesful");
        connected = true;
    }
    
    public void closeConnection(){
        try {
            // Close inputstream
            input.close();
        } catch (IOException ex) {
            gui.console.append("\nInputstream close failed");
        }
        // Close port
        port.close();
        gui.console.append("\nConnection closed");
        
    }
    
    public boolean isConnected(){
        if(connected == true){
            return true;
        }
        else{
            return false;
        }
    }
    public void run()
    {
        
    }
}

