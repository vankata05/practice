package practice.OOP.Golqmo_Domashno;
//import UUID
import java.util.UUID;

abstract class Package {
    final int id = UUID.randomUUID().hashCode();
    boolean salable;
    int size;

    abstract double getDeliveryPrice();
}
