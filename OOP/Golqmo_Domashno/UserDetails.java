package practice.OOP.Golqmo_Domashno;

import java.util.UUID;

public class UserDetails {
    final int id = UUID.randomUUID().hashCode();
    String firstName;
    String lastName;
    String telephoneNumber;
    int userId;

    public UserDetails(String firstName, String lastName, String telephoneNumber, int userId) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.telephoneNumber = telephoneNumber;
        this.userId = userId;
    }

    public int getId() {
        return id;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getTelephoneNumber() {
        return telephoneNumber;
    }

    public int getUserId() {
        return userId;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public void setTelephoneNumber(String telephoneNumber) {
        this.telephoneNumber = telephoneNumber;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }
}
