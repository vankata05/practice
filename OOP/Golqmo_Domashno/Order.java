package practice.OOP.Golqmo_Domashno;
//import uuid
import java.util.UUID;

public class Order {
    final int id = UUID.randomUUID().hashCode();
    Package[] packages;
    int addressId;
    Status status;


    public Order(Package[] packages, int addressId) {
        this.packages = packages;
        this.addressId = addressId;
        status = Status.CREATED;
    }

    public double getDeliveryPrice(){
        double price = 0;
        for (Package aPackage : packages) {
            price += aPackage.getDeliveryPrice();
        }
        return price;
    }

    public void setStatus(Status status) {
        this.status = status;
    }

    public int getId() {
        return id;
    }

    public Package getPackage(int index) {
        return packages[index];
    }
    
    public void addPackage(Package aPackage){
        Package[] newPackages = new Package[packages.length + 1];
        for (int i = 0; i < packages.length; i++) {
            newPackages[i] = packages[i];
        }
        newPackages[newPackages.length - 1] = aPackage;
        packages = newPackages;
    }

    public Status getStatus() {
        return status;
    }
}
