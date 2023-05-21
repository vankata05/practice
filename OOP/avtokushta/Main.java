package practice.OOP.avtokushta;

public class Main {
    public static void main(String[] args){
        Car car = new Car(1, "BMW", "X5", 2015, "Black", 10000, 5, 5, EquipmentLevel.PREMIUM);
        SUV suv = new SUV(2, "Audi", "Q7", 2017, "White", 20000, true, 5.5);
        Truck truck = new Truck(3, "Mercedes", "Actros", 2018, "Red", 30000, 10000, 2.5);

        VehicleDealar dealer = new VehicleDealar();
        dealer.addVehicle(car);
        dealer.addVehicle(suv);
        dealer.addVehicle(truck);
        

        System.out.println(dealer.findVehicleById(1));
        System.out.println(dealer.findVehicleById(2));
        System.out.println(dealer.findVehicleById(3));
    }
}
