package com.mobcontrol.server.ui;

import java.awt.image.BufferedImage;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class UIFrame extends JFrame {

    /**
     * 
     */
    private static final long serialVersionUID = 1831203428568086441L;

    public void showImage(BufferedImage image) {
        if (image == null) {
            return;
        }
        this.setTitle("Mobile Control");
        this.setSize((int)(image.getWidth() * 1.5f), (int)(image.getHeight() * 1.5f));
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);

        JLabel jLabel = new JLabel(new ImageIcon(image));
        JPanel jPanel = new JPanel();
        jPanel.add(jLabel);
        this.add(jPanel);
        this.setVisible(true);
    }

}
