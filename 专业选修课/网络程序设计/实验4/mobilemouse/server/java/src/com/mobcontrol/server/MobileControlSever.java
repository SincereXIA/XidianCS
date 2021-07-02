package com.mobcontrol.server;

import java.awt.AWTException;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.PointerInfo;
import java.awt.Robot;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.BindException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.MulticastSocket;
import java.net.NetworkInterface;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.util.*;
import java.util.Timer;

import javax.swing.*;

import com.google.zxing.WriterException;
import com.mobcontrol.server.ui.MainWindow;
import com.mobcontrol.server.ui.UIFrame;

public class MobileControlSever extends Thread {

    //TODO: connection status management

    private Mode mMode = Mode.QR_SCAN;

    private static final String MULTI_CAST_ADDR = "239.5.6.7";
    private static final int LOCAL_UDP_PORT = 30000;
    private static final int MCAST_CLIENT_PORT = 28960;
    private static final int LOCAL_TCP_PORT = 27015;// control data comes here

    private static final int WAIT_FOR_WAVE_SO_TIMEOUT = 60 * 1000; // milliseconds
    private static final int WAIT_FOR_WAVE_BUFFER_SIZE = 1024; // bytes

    private ServerSocket mServerSocket;
    private Socket mSocket;
    private String mIpAddr;
    private ArrayList<String> mIpAddrList;
    private Robot mRobot;
    private int mPort;
    private long mHeartBeatTime = 0; // 上次心跳时间
    private boolean isStop = true;
    private boolean mIsAlive = false;

    DataOutputStream mOutputStream;

    private int mMouseX, mMouseY;

    private enum Mode {
        DISCOVERY,
        QR_SCAN
    }

    private MainWindow mainWindow;

    private byte[] mHeartBeat = new byte[0]; // 心跳包数据

    /**
     * 服务端初始化
     * @param port 监听端口
     * @throws IOException
     */
    public MobileControlSever(Mode mode, int port) throws IOException {
        show(); // 显示图形化界面
        mMode = mode;
        mPort = port;
        mServerSocket = new ServerSocket(); // 创建服务端监听 Socket
        try {
            mRobot = new Robot();
        } catch (AWTException e) {
            e.printStackTrace();
        }
        mIpAddrList = getIpList(); // 扫描网卡ip，从中筛选出内网ip
        mainWindow.setAddrList(mIpAddrList); // ip 地址显示在界面中
        mainWindow.setComboBoxCallback(this.ipSelectedCallback()); // 设置下拉菜单的回调函数
        mainWindow.setApplyButtonCallback(this.startButtonCallback()); // 设置开始按钮回调函数
        mainWindow.setStopButtonCallback(this.stopButtonCallback()); // 设置停止按钮回调函数
        mainWindow.setInfoLabel("等待设定监听 ip，完成后点击开始运行按钮");
        this.mIpAddr = mIpAddrList.get(0);
    }

    /**
     * @param x
     *            to x
     * @param y
     *            to y
     */
    private void mouseMove(int x, int y) {
        System.out.println("mouseMove called, x: " + x + ", y: " + y);
        if (mRobot != null) {
            mRobot.mouseMove(x, y);
        }

        updateCurrentMousePosition();
    }

    private void updateCurrentMousePosition() {
        PointerInfo pointerInfo = MouseInfo.getPointerInfo();
        if (pointerInfo != null) {
            Point p = pointerInfo.getLocation();
            if (p != null) {
                mMouseX = (int) p.getX();
                mMouseY = (int) p.getY();
            }
        }
    }

    private void leftClick() {
        System.out.println("leftClick called");
        if (mRobot != null) {
            mRobot.mousePress(InputEvent.BUTTON1_MASK);
            mRobot.mouseRelease(InputEvent.BUTTON1_MASK);
        }
    }

    private void rightClick() {
        System.out.println("rightClick called");
        if (mRobot != null) {
            mRobot.mousePress(InputEvent.BUTTON3_MASK);
            mRobot.mouseRelease(InputEvent.BUTTON3_MASK);
        }
    }

    /**
     * 获取点击按钮的回调函数
     *
     * @return ActionListener 回调函数
     * @throws IOException
     */
    public ActionListener startButtonCallback() throws IOException {
        ActionListener actionListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("my ip: " + mIpAddr);
                isStop = false;
                if (mIpAddr == null || mIpAddr.length() == 0) {
                    throw new IllegalArgumentException("IP address is null!");
                }
                if (mServerSocket.isClosed()) {
                    try {
                        mServerSocket = new ServerSocket();
                    } catch (IOException ioException) {
                        ioException.printStackTrace();
                    }
                }
                if (!mServerSocket.isBound()) {
                    try {
                        mServerSocket.bind(new InetSocketAddress(mIpAddr, mPort)); // 监听用户设定的ip地址
                    } catch (IOException exception) {
                        exception.printStackTrace(); // 端口已经被占用
                    }
                }
                if (!isAlive()) {
                    start(); // 启动循环线程，在循环中不断接受客户端发送的数据并处理
                }
            }
        };
        return actionListener;
    }

    /**
     * 获取下拉按钮重新选择后的回调函数
     *
     * @return
     * @throws IOException
     */
    public ItemListener ipSelectedCallback() throws IOException {
        ItemListener itemListener = e -> {
            if(ItemEvent.SELECTED == e.getStateChange()) {
                String selectedItem = e.getItem().toString();
                mIpAddr = selectedItem;
            }
        };
        return itemListener;
    }

    public ActionListener stopButtonCallback() {
        ActionListener actionListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                isStop = true;
                try {
                    if (mSocket!=null && mSocket.isConnected()){
                        DataOutputStream out = new DataOutputStream(mSocket.getOutputStream());
                        out.writeUTF("STOP");
                    }
                    mServerSocket.close();
                    mainWindow.showImage(null);
                    mainWindow.setInfoLabel("服务未运行，点击开始运行重新启动服务");
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }
            }
        };
        return actionListener;
    }

    /**
     * 看门狗线程
     */
    class WatchDogThread extends Thread {
        public void run() {
            while(true) {
                try {
                    Thread.sleep(500);
                    long delta = System.currentTimeMillis() - mHeartBeatTime;
                    if (isStop) {
                        return;
                    }
                    if (delta > 5000) {
                        System.out.println("Heartbeat lost, close socket");
                        mIsAlive = false;
                        mSocket.close();
                        mainWindow.setInfoLabel("网络中断，等待客户端重新连接");
                        break;
                    }
                } catch (InterruptedException | IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    /**
     * 主运行线程
     */
    public void run() {
        updateCurrentMousePosition();
        while (true) {
            while (isStop) {
                try {
                    Thread.sleep(1000); // 未运行时停止1秒
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            if (mMode == Mode.DISCOVERY) {
                try {
                    waitForClientWave(MULTI_CAST_ADDR, LOCAL_UDP_PORT);
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            } else {
                generateAndShowQRCode();
            }

            Socket server = null;
            try {
                server = mServerSocket.accept(); // 获取到客户端连接
                mSocket = server;
                mOutputStream = new DataOutputStream(mSocket.getOutputStream());
                // 启动看门狗
                mIsAlive = true;
                mHeartBeatTime = System.currentTimeMillis();
                WatchDogThread watchDogThread = new WatchDogThread();
                watchDogThread.start();
                mainWindow.setInfoLabel("Android 客户端已连接");
            } catch (IOException e1) {
                // TODO Auto-generated catch block
                e1.printStackTrace();
                continue;
            }
            while (true) {
                DataInputStream in = null;
                try {
                    System.out.println("Waiting for client on port " + mServerSocket.getLocalPort() + "...");
                    // System.out.println("Server ip: "
                    // + mServerSocket.getInetAddress());
                    System.out.println("Just connected to " + server.getRemoteSocketAddress());
                    if (isStop) {
                        throw new IOException();
                    }
                    in = new DataInputStream(server.getInputStream()); // 阻塞式等待客户端数据包
                    String inStr = in.readUTF(); // 使用 UTF 格式进行解码
                    System.out.println(inStr);
                    handleTouchData(inStr); // 处理收到的数据，并模拟鼠标操作
                } catch (SocketTimeoutException s) {
                    System.out.println("Socket timed out!");
                    break;
                } catch (IOException e) {
                    //client disconnected
                    e.printStackTrace();
                    System.out.println("client disconnected");
                    //TODO: alert the user
                    try {
                        in.close();
                        server.close();
                        in = null;
                        server = null;
                    } catch (Exception ee) {
                        e.printStackTrace();
                    }
                    break;
                }
            }
        }
    }

    private void generateAndShowQRCode() {
        try {
            BufferedImage image = QRUtils.createQRImage(mIpAddr, 200);
            if (image != null) {
                SwingUtilities.invokeLater(new Runnable() {

                    @Override
                    public void run() {
                        mainWindow.setInfoLabel("请使用 Android 客户端扫描下方二维码");
                        mainWindow.showImage(image);
                    }
                });
            }
        } catch (WriterException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    /**
     * 处理从客户端发送来的数据
     * @param t
     */
    private void handleTouchData(String t) throws IOException {
        if (t != null && t.length() > 0) {
            String[] segs = t.split(",");
            int segLen = segs.length;
            if (segLen > 1 && "mctd".equals(segs[0])) {
                String type = segs[1];
                if ("L".equals(type)) {
                    leftClick();
                } else if ("R".equals(type)) {
                    rightClick();
                } else if ("M".equals(type)) {
                    if (segLen > 3) {
                        String x = segs[2], y = segs[3];
                        System.out.println("handle move, x: " + x + ", y: " + y);
                        try {
                            int xInt = Integer.valueOf(x);
                            int yInt = Integer.valueOf(y);
                            if (xInt != 0 || yInt != 0) {
                                mouseMove(mMouseX + xInt, mMouseY + yInt);
                            }
                        } catch (NumberFormatException e) {
                            e.printStackTrace();
                        }
                    }
                }
            } else if (segLen == 1 && "heartbeat".equals(segs[0])) {
                System.out.println("heart beat received");
                mHeartBeatTime = System.currentTimeMillis();
                mOutputStream.writeUTF("heartbeat"); // 回应心跳包
            }
            else {
                System.out.println(t);
            }
        }
    }

    private ArrayList<String> getIpList() {
        ArrayList<String> result = new ArrayList<String>();
        try {
            System.out.println("Full list of Network Interfaces:");
            for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {
                NetworkInterface intf = en.nextElement();
                System.out.println("    " + intf.getName() + " " + intf.getDisplayName());
                for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
                    InetAddress ia = enumIpAddr.nextElement();
                    String ip = ia.getHostAddress();
                    System.out.println("        " + ip);
                    if (ip != null && (ip.startsWith("192.168") || ip.startsWith("172.") || ip.startsWith("10."))) {
                        result.add(ip);
                    }
                }
            }
        } catch (SocketException e) {
            System.out.println(" (error retrieving network interface list)");
        }
        return result;
    }

    private void waitForClientWave(String addr, int port) throws IOException {
        System.out.println("waitForClientWave " + addr + ", " + port);
        InetAddress group = InetAddress.getByName(addr);
        MulticastSocket s = new MulticastSocket(port);
        s.setSoTimeout(WAIT_FOR_WAVE_SO_TIMEOUT);
        int bufferSize = WAIT_FOR_WAVE_BUFFER_SIZE;
        byte[] arb = new byte[bufferSize];
        s.joinGroup(group);
        String res;
        while (true) {
            DatagramPacket datagramPacket = new DatagramPacket(arb, bufferSize);
            try {
                s.receive(datagramPacket);

                // System.out.println(arb.length);
                res = new String(arb);
                System.out.println("got client wave: " + res);
                if (res.startsWith("hi_i_am_client")) {
                    String sendMessage = "hi_i_am_server";
                    sendMulticast(sendMessage, MULTI_CAST_ADDR, MCAST_CLIENT_PORT);
                    System.out.println("waitForClientWave, got client wave, waved back");
                    s.close();
                    return;
                }
            } catch (SocketTimeoutException e) {
                System.out.println("waiting for client wave timed out");
                //TODO: handle timeout: notify the user to start a new round of waiting
                break;
            } finally {
                try {
                    s.close();
                } catch (Exception ignored) {
                }
            }

        }
    }

    private void sendMulticast(String sendMessage, String addr, int port) throws IOException {
        InetAddress inetAddress = InetAddress.getByName(addr);
        DatagramPacket datagramPacket = new DatagramPacket(sendMessage.getBytes(), sendMessage.length(), inetAddress,
                port);
        MulticastSocket multicastSocket = new MulticastSocket();
        multicastSocket.send(datagramPacket);
        multicastSocket.close();
    }

    public static void main(String[] args) {
        // int port = Integer.parseInt(args[0]);
        try {
            Thread t = new MobileControlSever(Mode.QR_SCAN, LOCAL_TCP_PORT);
            //t.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void show()  {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (UnsupportedLookAndFeelException e) {
            e.printStackTrace();
        }
        JFrame frame = new JFrame("MainWindow");
        this.mainWindow = new MainWindow();
        frame.setContentPane(mainWindow.panel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }

}
