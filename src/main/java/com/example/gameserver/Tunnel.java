package com.example.gameserver;

import com.jcraft.jsch.JSch;
import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.Session;

public class Tunnel {
    private Session session;
    private String username, password, host;
    private int port;
    private int lport = 1234;
    private int rport = 1521;
    private String rhost = "labora";

    public Tunnel(String username, String password,
                  String host, int port) {
        this.username = username;
        this.password = password;
        this.host = host;
        this.port = port;
    }


    public void connect() throws JSchException {
        session = new JSch().getSession(username, host, port);
        session.setPassword(password);
        session.setConfig("StrictHostKeyChecking", "no");
        session.connect();
        System.out.println("Connected");

        int assinged_port=session.setPortForwardingL(lport, rhost, rport);
        System.out.println("localhost:"+assinged_port+" -> "+rhost+":"+rport);
    }

    public void disconnect() {
        session.disconnect();
        System.out.println("Disconnected");
    }

}

