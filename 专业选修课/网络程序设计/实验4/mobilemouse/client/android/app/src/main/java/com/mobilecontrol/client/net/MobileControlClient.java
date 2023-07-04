package com.mobilecontrol.client.net;

import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;

import java.io.DataInput;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;

public class MobileControlClient {
    private static final String TAG = "MobileControlClient";

    private static final int WAIT_FOR_WAVE_SO_TIMEOUT = 2000; // milliseconds
    private static final int WAIT_FOR_WAVE_BUFFER_SIZE = 1024; // bytes

    private static final String MULTI_CAST_ADDR = "239.5.6.7";
    private static final int SERVER_UDP_PORT = 30000;//multicast send to
    private static final int SERVER_TCP_PORT = 27015;//control data send to
    private static final int LOCAL_UDP_PORT = 28960;//listen multicast here

    private static final short DISCONNECTED = 0;
    private static final short CONNECTING = 1;
    private static final short CONNECTED = 2;

    private NetworkThread mNetworkThread;
    private Handler mNetThreadHandler;
    private OnConnectListener mOnConnectListener;
    private short mConnectionStatus = DISCONNECTED;
    private String mServerIP = "";

    Handler mHandler; // 用于调用心跳包发送
    Handler mUIHandler ; // 用于处理心跳超时异常

    public MobileControlClient() {
        init();
    }

    private void init() {
        if (mConnectionStatus != DISCONNECTED) {
            return;
        }
        HandlerThread mHandlerThread = new HandlerThread("heartBeatThread");
        mHandlerThread.start();
        mHandler = new Handler(mHandlerThread.getLooper());
        mUIHandler = new Handler(mHandlerThread.getLooper());

        mNetworkThread = new NetworkThread("MobConClientNetThread");
        mNetworkThread.start();
        mNetThreadHandler = new Handler(mNetworkThread.getLooper()) {

            @Override
            public void handleMessage(Message msg) {
                Log.d(TAG, "mNetThreadHandler handle msg: " + msg.what);
                switch(msg.what) {
                    case NetworkThread.MSG_FIND_SERVER:
                        mNetworkThread.findServer();
                        break;
                    case NetworkThread.MSG_ON_QR_SCANNED:
                        mNetworkThread.onQRScanEnd((String) msg.obj);
                        break;
                    case NetworkThread.MSG_SEND:
                        mNetworkThread.send((String)msg.obj);
                        break;
                    default:
                        break;
                }
            }

        };
    }

    private void quitAndMarkDisconnected() {
        try {
            clearHandlerMsgs();
//            Looper looper = mNetThreadHandler.getLooper();
//            if (looper != null) {
////                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR2) {
////                    looper.quitSafely();
////                } else {
//                    looper.quit();
////                }
//            }
        } catch (Exception ignored) {
        }

//        mNetworkThread = null;
//        mNetThreadHandler = null;
        this.mServerIP = mNetworkThread.mServerIp;
        mConnectionStatus = DISCONNECTED;
        init();
        mNetworkThread.mServerIp = mServerIP;
    }

    private void clearHandlerMsgs() {
        if (mNetThreadHandler != null) {
            try {
                mNetThreadHandler.removeCallbacksAndMessages(null);
            } catch (Exception ignored) {
            }
        }
    }

    public void setOnConnectListener(OnConnectListener listener) {
        mOnConnectListener = listener;
    }

    public void onQRScanStart() {
        init();
        mConnectionStatus = CONNECTING;
    }

    public void onQRScanEnd(String serverIp) {
        mNetThreadHandler.sendMessage(Message.obtain(mNetThreadHandler, NetworkThread.MSG_ON_QR_SCANNED, serverIp));
    }

    public void findServer() {
        Log.d(TAG, "findServer");
        init();
//        clearHandlerMsgs();
        mNetThreadHandler.sendEmptyMessage(NetworkThread.MSG_FIND_SERVER);
    }

    public void disconnect() {
        if (mConnectionStatus != DISCONNECTED && mNetworkThread != null) {
            mNetworkThread.disconnect(false);
        }
    }

    public void send(String content) {
        Log.d(TAG, "send: " + content);
//        clearHandlerMsgs();
        if (isConnected() && mNetThreadHandler != null) {
            mNetThreadHandler.sendMessage(Message.obtain(mNetThreadHandler, NetworkThread.MSG_SEND, content));
        }
    }

    public boolean isConnected() {
        return mConnectionStatus == CONNECTED && mNetworkThread != null && mNetworkThread.isConnected();
    }

    public boolean reconnect() {
        disconnect();
        try {
            Thread.sleep(1200);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        mNetworkThread.onQRScanEnd(this.mServerIP);
        return isConnected();
    }

    public interface OnConnectListener {
        void onFindServerComplete(boolean found);
        void onDisconnected(boolean disconnectedByServer);
    }

    public class NetworkThread extends HandlerThread {

        private static final String TAG = "NetworkThread";

        public static final int MSG_FIND_SERVER = 0;
        public static final int MSG_ON_QR_SCANNED = 1;
        public static final int MSG_SEND = 2;

        private Socket mClientSoc;
        private String mServerIp;// = "172.17.106.55";
        private DataOutputStream out;

        public NetworkThread(String name) {
            super(name);
        }

        public void onQRScanEnd(String serverIp) {
            mHandler.removeCallbacks(heartBeatTask);
            boolean found = !TextUtils.isEmpty(serverIp);
            if (found) {
                mServerIp = serverIp; // 设定服务端ip
            } else {
                quitAndMarkDisconnected(); // 若未获取到ip设定状态为未连接
            }
            connect(mServerIp, SERVER_TCP_PORT); // 尝试连接服务端
            if (mClientSoc == null || !mClientSoc.isConnected()) {
                quitAndMarkDisconnected();
                return;
            }
            mOnConnectListener.onFindServerComplete(found);
            mConnectionStatus = CONNECTED; // 设定状态为已连接
            Thread listenThread = new listenThread();
            listenThread.start();
            new Thread(heartBeatTask).start(); // 启动心跳包
        }

        private void findServer() {
            mConnectionStatus = CONNECTING;
            Log.d(TAG, "connect");
            String res;
            wave();
            res = waitForWaveBack();

            if (!TextUtils.isEmpty(res)) {
                mServerIp = res.substring(res.indexOf("/") + 1);
                boolean found = !TextUtils.isEmpty(mServerIp);
                if (found) {
                    mConnectionStatus = CONNECTED;
                } else {
                    quitAndMarkDisconnected();
                }
                mOnConnectListener.onFindServerComplete(found);
            } else {
                quitAndMarkDisconnected();
                mOnConnectListener.onFindServerComplete(false);
            }
        }

        private  final Runnable heartBeatTimeoutTask = new Runnable() {
            @Override
            public void run() {
                Log.e("HEARTBEAT", "lost connection, try reconnect");
                //disconnect(true);
            }
        };

        private  final Runnable heartBeatTask = new Runnable() {
            @Override
            public void run() {
                if (mConnectionStatus != CONNECTED) {
                    return;
                }
                try {
                    send("heartbeat");
                } catch (Exception e) {
                    e.printStackTrace();
                    return;
                }
                mHandler.postDelayed(heartBeatTask, 1000);
                mUIHandler.postDelayed(heartBeatTimeoutTask, 3000);
            }
        };

        class listenThread extends Thread {
            public void run() {
                try {
                    DataInputStream input = new DataInputStream(mClientSoc.getInputStream());
                    while(true) {
                        String ret = input.readUTF();
                        Log.e("SOCKET", "from server:" + ret);
                        if (ret.equals("STOP")) {
                            disconnect(false);
                        }
                        else if (ret.equals("heartbeat")) {
                            Log.d("HEARTBEAT", "receive heart beat");
                            mUIHandler.removeCallbacks(heartBeatTimeoutTask);
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        private boolean reconnect() {
            try {
                mHandler.removeCallbacks(heartBeatTask);
                mUIHandler.removeCallbacks(heartBeatTimeoutTask);
                Log.d(TAG, "Reconnecting to server " + mServerIp + " on port " + SERVER_TCP_PORT);
                mClientSoc = new Socket(mServerIp, SERVER_TCP_PORT);
                mClientSoc.setKeepAlive(true);
                Thread.sleep(1000);
                if (!mClientSoc.isConnected()) {
                    return false;
                }else {
                    mConnectionStatus = CONNECTED;
                    mOnConnectListener.onFindServerComplete(true);
                    Log.d(TAG, "Just connected to server " + mClientSoc.getRemoteSocketAddress());
                    Thread listenThread = new listenThread();
                    listenThread.start();
                    new Thread(heartBeatTask).start(); // 启动心跳包
                    return true;
                }
            } catch (UnknownHostException e) {
                Log.e(TAG, "xxxxxxxxxxxxxxxxx", e);
            } catch (IOException e) {
                Log.e(TAG, "xxxxxxxxxxxxxxxxx", e);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return false;
        }

        private void connect(String serverName, int port) {
            try {
                Log.d(TAG, "Connecting to server " + serverName + " on port " + port);
                mClientSoc = new Socket(serverName, port);
                mClientSoc.setKeepAlive(true);
                Log.d(TAG, "Just connected to server " + mClientSoc.getRemoteSocketAddress());
            } catch (UnknownHostException e) {
                Log.e(TAG, "xxxxxxxxxxxxxxxxx", e);
            } catch (IOException e) {
                Log.e(TAG, "xxxxxxxxxxxxxxxxx", e);
            }
        }

        /**
         * 发送字符串数据
         * @param content
         */
        private void send(String content) {
            Log.d(TAG, "send: " + content + ", mServerIp: " + mServerIp);
            if (TextUtils.isEmpty(mServerIp)) {
                Log.e(TAG, "send: server ip null!");
                return;
            }
            try {
                if (mClientSoc == null) { // 若未连接，尝试重新连接
                    connect(mServerIp, SERVER_TCP_PORT);
                }

                if (out == null) {
                    OutputStream outToServer = mClientSoc.getOutputStream();
                    out = new DataOutputStream(outToServer);
                }

                out.writeUTF(content);

            } catch (IOException e) {
                Log.e(TAG, "exception on send (server disconnected): ", e);
                disconnect(true);
            }
        }

        private void wave() {
            try {
                sendMulticast("hi_i_am_client", MULTI_CAST_ADDR, SERVER_UDP_PORT);
                Log.d(TAG, "wave to server sent");
            } catch (IOException e) {
                Log.e(TAG, "sendMulticast exception: ", e);
            }
        }

        private String waitForWaveBack() {
            String res = null;
            try {
                res = receiveMulticast(MULTI_CAST_ADDR, LOCAL_UDP_PORT);
                Log.d(TAG, "waitForWaveBack, got res: " + res);
            } catch (IOException e) {
                Log.e(TAG, "receiveMulticast exception: ", e);
            }
            return res;
        }

        private void sendMulticast(String sendMessage, String addr, int port) throws IOException {
            Log.d(TAG, "sendMulticast");
            InetAddress inetAddress = InetAddress.getByName(addr);
            DatagramPacket datagramPacket = new DatagramPacket(
                    sendMessage.getBytes(), sendMessage.length(), inetAddress,
                    port);
            MulticastSocket multicastSocket = new MulticastSocket();
            multicastSocket.send(datagramPacket);
            multicastSocket.close();
        }

        private String receiveMulticast(String addr, int port) throws IOException {
            Log.d(TAG, "receiveMulticast");
            InetAddress group = InetAddress.getByName(addr);
            MulticastSocket s = new MulticastSocket(port);
            s.setSoTimeout(WAIT_FOR_WAVE_SO_TIMEOUT);
            int bufferSize = WAIT_FOR_WAVE_BUFFER_SIZE;
            byte[] arb = new byte[bufferSize];
            s.joinGroup(group);
            String res;
            while (mConnectionStatus == CONNECTING) {
                DatagramPacket datagramPacket = new DatagramPacket(arb, bufferSize);
                Log.d(TAG, "before receive");
                try {
                    s.receive(datagramPacket);

                    res = new String(arb);
                    Log.d(TAG, "after receive, res: " + res);
                    if (res.startsWith("hi_i_am_server")) {
                        String ret = datagramPacket.getAddress().toString();
                        Log.d(TAG, "server waved back, ip: " + ret);
                        s.close();
                        return ret;
                    }
                } catch (SocketTimeoutException e) {
                    Log.e(TAG, "waiting for server wave timed out", e);
                    quitAndMarkDisconnected();
                    mOnConnectListener.onFindServerComplete(false);
                    break;
                } finally {
                    try {
                        s.close();
                    } catch (Exception ignored) {
                    }
                }
            }
            return null;
        }

        public void disconnect(boolean disconnectedByServer) {
            mHandler.removeCallbacks(heartBeatTask);
            mUIHandler.removeCallbacks(heartBeatTimeoutTask);
            if (mClientSoc != null) {
                try {
                    mClientSoc.shutdownOutput();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            if (out != null) {
                try {
                    out.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            if (mClientSoc != null) {
                try {
                    mClientSoc.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            quitAndMarkDisconnected();
            mOnConnectListener.onDisconnected(disconnectedByServer);
        }

        public boolean isConnected() {
            return !TextUtils.isEmpty(mServerIp);
        }
    }
}
