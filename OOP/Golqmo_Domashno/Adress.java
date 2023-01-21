package practice.OOP.Golqmo_Domashno;
//import UUID
import java.util.UUID;

public class Adress {
    final int id = UUID.randomUUID().hashCode();
    String country;
    String city;
    String street;
    int userId;

    public Adress(String country, String city, String street, int userId) {
        this.country = country;
        this.city = city;
        this.street = street;
        this.userId = userId;
    }
}
