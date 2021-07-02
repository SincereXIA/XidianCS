package com.mobilecontrol.client;

import com.mobilecontrol.client.net.MobileControlClient;

import android.app.Application;

public class MobileControlApp extends Application {
    private MobileControlClient mControlClient;

    public void setMobileControlClient(MobileControlClient mbc) {
        mControlClient = mbc;
    }

    public MobileControlClient getMobileControlClient() {
        return mControlClient;
    }
}
