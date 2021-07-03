package com.mobcontrol.server.ui;

import com.mobcontrol.server.MobileControlSever;

import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

public class MainWindow {
    private JComboBox<String> comboBox1;
    private JButton button1;
    public JPanel panel;
    private JButton buttonStop;
    private JLabel infoLabel;
    private JLabel qrLabel;

    public void setAddrList(ArrayList<String> ipList) {
        for (String ip:ipList) {
            comboBox1.addItem(ip);
        }
    }
    public void setInfoLabel(String message) {
        infoLabel.setText(message);
    }

    public void setComboBoxCallback(ItemListener itemListener) {
        comboBox1.addItemListener(itemListener);
    }

    public  void setApplyButtonCallback(ActionListener actionListener) {
        button1.addActionListener(actionListener);
    }

    public void setStopButtonCallback(ActionListener actionListener) {
        buttonStop.addActionListener(actionListener);
    }

    public void showImage(BufferedImage image) {
        if (image == null) {
            qrLabel.setIcon(null);
        }
        qrLabel.setIcon(new ImageIcon(image));
    }
}
