package com.example.gameserver.players;

import javax.persistence.*;
import java.util.Objects;

@Entity
@Table(name = "PLAYER")
public class Player {
    @Id
    @Column(name = "NICK", nullable = false)
    private String nick;

    @Column(name = "FIRST_NAME", nullable = false)
    private String firstName;
    @Column(name = "LAST_NAME", nullable = false)
    private String lastName;
    @Column(name = "AGE", nullable = false)
    private Integer age;
    @Column(name = "PASSWORD", nullable = false)
    private String password;

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public Player() {}

    public Player(String nick, String firstName, String lastName, Integer age, String password) {
        this.nick = nick;
        this.firstName = firstName;
        this.lastName = lastName;
        this.age = age;
        this.password = password;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Player player = (Player) o;
        return nick.equals(player.nick) && firstName.equals(player.firstName) && lastName.equals(player.lastName) && age.equals(player.age) && password.equals(player.password);
    }

    @Override
    public int hashCode() {
        return Objects.hash(nick, firstName, lastName, age, password);
    }

    public String getNick() {
        return nick;
    }

    public void setNick(String nick) {
        this.nick = nick;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String first_name) {
        this.firstName = first_name;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String last_name) {
        this.lastName = last_name;
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Player{" +
                "nick=" + nick +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", age='" + age + '\'' +
                ", password='" + password + '\'' +
                '}';
    }
}
