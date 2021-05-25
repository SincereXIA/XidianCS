package com.mobilecontrol.client;

import android.Manifest;
import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.TextView;
import android.widget.Toast;

import com.mobilecontrol.client.data.TouchData;
import com.mobilecontrol.client.net.MobileControlClient;
import com.mobilecontrol.client.net.MobileControlClient.OnConnectListener;
import com.mobilecontrol.client.qrscan.QRScannerActivity;

public class MainActivity extends Activity implements View.OnClickListener {

    protected static final String TAG = "MainActivity";

    private static final int REQ_CODE_SCAN = 100;
    private int CAMERA_OK;

    private long mLongClickTime = 400;
    private int mSpeed = 1;
    private MobileControlClient mControlClient;
    private TextView mConnectionStatusView;
    private static AlertDialog alertDialog;

    private OnConnectListener mOnConnectListener = new OnConnectListener() {

        @Override
        public void onDisconnected(final boolean disconnectedByServer) {
            Log.d(TAG, "onDisconnected" + (disconnectedByServer ? " by server" : ""));
            MainActivity.this.runOnUiThread(new Runnable() {

                @Override
                public void run() {
                    mConnectionStatusView.setText(disconnectedByServer
                            ? R.string.disconnected_by_server : R.string.disconnected);
                }
            });
            if (disconnectedByServer) {
                MainActivity.this.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                         MainActivity.alertDialog = new AlertDialog.Builder(MainActivity.this)
                                .setTitle("正在重新连接")
                                .setMessage("")
                                .create();
                         alertDialog.show();
                    }
                });
                for (int i = 0; i<5; i++) {
                    if(mControlClient.reconnect()) {
                        MainActivity.this.runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                alertDialog.dismiss();
                            }
                        });
                        return;
                    }
                    try {
                        Thread.sleep(5000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }

        @Override
        public void onFindServerComplete(final boolean found) {
            MainActivity.this.runOnUiThread(new Runnable() {

                @Override
                public void run() {
                    mConnectionStatusView.setText(found ? R.string.connected : R.string.server_not_found);
                }
            });
        }
    };
    /** 获取权限*/
    private void getPermission() {
        if (Build.VERSION.SDK_INT>22){
            if (ContextCompat.checkSelfPermission(MainActivity.this,
                    android.Manifest.permission.CAMERA)!= PackageManager.PERMISSION_GRANTED){
                //先判断有没有权限 ，没有就在这里进行权限的申请
                ActivityCompat.requestPermissions(MainActivity.this,
                        new String[]{Manifest.permission.CAMERA, Manifest.permission.WRITE_EXTERNAL_STORAGE},CAMERA_OK);
            }else {
                //说明已经获取到摄像头权限了
                Log.i("MainActivity","已经获取了权限");
            }
        }else {
//这个说明系统版本在6.0之下，不需要动态获取权限。
            Log.i("MainActivity","这个说明系统版本在6.0之下，不需要动态获取权限。");
        }
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getPermission();
        ActionBar actionBar = getActionBar();
        actionBar.setDisplayUseLogoEnabled(false);

        findViewById(R.id.btn_left).setOnClickListener(this);
        findViewById(R.id.btn_right).setOnClickListener(this);

        findViewById(R.id.touch_pad).setOnTouchListener(new OnTouchListener() {

            float lastX, lastY, downX, downY;
            long downTime;

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        downX = lastX = event.getX();
                        downY = lastY = event.getY();
                        downTime = System.currentTimeMillis();
                        break;
                    case MotionEvent.ACTION_MOVE:
                        float x = event.getX();
                        float y = event.getY();
                        float dx = x - lastX;
                        float dy = y - lastY;
                        lastX = x;
                        lastY = y;

                        TouchData td = new TouchData();
                        td.setType(TouchData.TOUCH_TYPE_MOVE);
                        td.setX(mSpeed * (int) dx);
                        td.setY(mSpeed * (int) dy);
                        send(td);
                        break;
                    case MotionEvent.ACTION_UP:
                        x = event.getX();
                        y = event.getY();
                        dx = x - downX;
                        dy = y - downY;
                        if (dx < 2 && dy < 2) {
                            // this is a click event
                            TouchData td_c = new TouchData();
                            long tx = System.currentTimeMillis() - downTime;
                            Log.d(TAG, "tx " + tx);
                            td_c.setType(tx > mLongClickTime ? TouchData.TOUCH_TYPE_LONG_CLICK
                                    : TouchData.TOUCH_TYPE_CLICK);
//                        td_c.setX((int) x);
//                        td_c.setY((int) y);
                            send(td_c);
                        }
                        break;
                }
                return true;
            }
        });

        mConnectionStatusView = (TextView) findViewById(R.id.connection_status);

        MobileControlApp app = (MobileControlApp) getApplication();
        mControlClient = app.getMobileControlClient();
        if (mControlClient == null) {
            mControlClient = new MobileControlClient();
            mControlClient.setOnConnectListener(mOnConnectListener);
//            if (!mControlClient.isConnected()) {
//                mControlClient.findServer();
//            }

            app.setMobileControlClient(mControlClient);
        }

    }

    @Override
    protected void onResume() {
        super.onResume();
        if (mControlClient.isConnected()) {
            mConnectionStatusView.setText(R.string.connected);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_qr_scan:
                if (mControlClient.isConnected()) {
                    Toast.makeText(this, R.string.already_connected, Toast.LENGTH_LONG).show();
                } else {
                    startQRScan();
                }
                return true;
            case R.id.action_disconnect:
                disconnect();
                return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private void startQRScan() {
        mControlClient.onQRScanStart();
        startActivityForResult(new Intent(this, QRScannerActivity.class), REQ_CODE_SCAN);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == REQ_CODE_SCAN) {
            if (resultCode == RESULT_OK) {
                String result = null;
                if (data != null) {
                    result = data.getStringExtra(QRScannerActivity.QR_SCAN_RESULT);
                }
                mControlClient.onQRScanEnd(result);
            } else {
                mControlClient.onQRScanEnd(null);
            }
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // mControlClient.disconnect();
    }

    private void autoDiscoverServer() {
        mControlClient.findServer();
    }

    private void disconnect() {
        mControlClient.disconnect();
    }

    private void sendHello() {
        mControlClient.send("Hello");
    }

    /**
     * 向服务端发送手势数据
     * @param td
     */
    private void send(TouchData td) {
        if (td == null || !mControlClient.isConnected()) {
            return;
        }
        StringBuilder sb = new StringBuilder();
        sb.append(td.getHead()).append(",")
                .append(td.getType()).append(",")
                .append(td.getX()).append(",")
                .append(td.getY());
        String jsonStr = sb.toString();
        Log.d(TAG, "send: " + jsonStr);
        mControlClient.send(jsonStr);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_left:
                onLeftClicked();
                break;
            case R.id.btn_right:
                onRightClicked();
                break;
        }
    }

    private void onRightClicked() {
        TouchData td_c = new TouchData();
        td_c.setType(TouchData.TOUCH_TYPE_LONG_CLICK);
        send(td_c);
    }

    private void onLeftClicked() {
        TouchData td_c = new TouchData();
        td_c.setType(TouchData.TOUCH_TYPE_CLICK);
        send(td_c);
    }
}
