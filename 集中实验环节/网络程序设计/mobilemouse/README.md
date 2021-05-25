# mobilemouse
Turn your android phone into a mouse touchpad for your pc.

[中文](http://www.jianshu.com/p/ac0513b2b684)

## Introduction
The purpose is to control the mouse cursor of a pc through a smart phone with a touch screen which is used as a touchpad for the pc. The pc and the phone are connected through a socket connection. they don't have to be connected to the internet, just need to be in the SAME LAN, which usually means they have to be connected to the SAME WIFI.

## Project structure
This project consists of two parts: the client(the phone end) and the server(the pc end). For now, there is an android client and a server written in java. Your are all welcome to contribute for other platforms.

## The connection process
   1. Discovery phase
   
      The two ends need to find each other before they can make a connection. First, the server listens for a UDP multicast on a certain multicast ip address and port. When the client starts the connection process, it sends a multicast on the address and port that was previously agreed opon in compile time, says "hi_i_am_client". And when the server gets this, it waves back with "hi_i_am_sever", and it makes a ServerSocket and listens in an infinite loop for input stream of control data from client and manipulate the cursor accordingly. When the client gets this "hi_i_am_server" wave back, it resolves the ip of the server, and that means they have found each other.
      
   2. Connection phase
   
      When the client needs to send control data to the server for the first time, it makes a socket connection to the servers ip address that was got within the discovery phase.
   
   3. Disconnection phase
   
      Each of both ends can disconnect, and the other end will know it by getting an EOFException.
