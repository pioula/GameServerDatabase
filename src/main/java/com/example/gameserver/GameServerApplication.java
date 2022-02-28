package com.example.gameserver;

import com.jcraft.jsch.JSchException;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Properties;

@SpringBootApplication
public class GameServerApplication {

    public static void main(String[] args) throws JSchException {
        Properties prop = new Properties();
        String config = "src/main/resources/app.config";
        try (FileInputStream fis = new FileInputStream(config)) {
            prop.load(fis);
        } catch (FileNotFoundException ex) {
            System.out.println("Config not found!");
        } catch (Exception exp) {
            exp.printStackTrace();
        }

        Tunnel tunnel = new Tunnel(prop.getProperty("app.login"), prop.getProperty("app.password"), "students.mimuw.edu.pl", 22);
        tunnel.connect();
        SpringApplication.run(GameServerApplication.class, args);
    }

}
