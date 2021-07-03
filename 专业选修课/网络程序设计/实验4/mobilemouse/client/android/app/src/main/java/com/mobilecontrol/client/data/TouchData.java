package com.mobilecontrol.client.data;

public class TouchData {

    public static final String TOUCH_TYPE_INVALID = "INVALID";
    public static final String TOUCH_TYPE_CLICK = "L";
    public static final String TOUCH_TYPE_LONG_CLICK = "R";
    public static final String TOUCH_TYPE_MOVE = "M";

    private String head;
    private String type;
    private int mx;
    private int my;

    public TouchData() {
        head = "mctd";
    }

    public String getHead() {
        return head;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public int getX() {
        return mx;
    }

    public void setX(int x) {
        this.mx = x;
    }

    public int getY() {
        return my;
    }

    public void setY(int y) {
        this.my = y;
    }

}
