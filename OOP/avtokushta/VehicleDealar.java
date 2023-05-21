package practice.OOP.avtokushta;

import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class VehicleDealar {
    private List<Vehicle> cars;
    private List<SUV> suvs;
    private List<Truck> trucks;
    private double turnover;

    public VehicleDealar() {
        this.cars = new ArrayList<>();
        this.suvs = new ArrayList<>();
        this.trucks = new ArrayList<>();
        this.turnover = 0;
    }

    public void addVehicle(Vehicle vehicle) throws Exception {
        if (vehicle == null) {
            throw new IllegalArgumentException("Vehicle cannot be null");
        }
        if (vehicle.getId() <= 0) {
            throw new IllegalArgumentException("Invalid vehicle ID");
        }
        if (findVehicleById(vehicle.getId()) != null) {
            throw new Exception("Vehicle with ID " + vehicle.getId() + " already exists");
        }
        if (vehicle instanceof Car) {
            cars.add((Car) vehicle);
        } else if (vehicle instanceof SUV) {
            suvs.add((SUV) vehicle);
        } else if (vehicle instanceof Truck) {
            trucks.add((Truck) vehicle);
        }
    }

    public Vehicle findVehicleById(int id) {
        return Stream.of(cars, suvs, trucks)
                     .flatMap(List::stream)
                     .filter(v -> v.getId() == id)
                     .findFirst()
                     .orElse(null);
    }

    public Map<String, Map<Integer, Vehicle>> getAllVehiclesByIdByMaker() {
        return Stream.of(cars, suvs, trucks)
                     .flatMap(List::stream)
                     .collect(Collectors.groupingBy(Vehicle::getMaker, Collectors.toMap(Vehicle::getId, Function.identity())));
    }

    public List<SUV> getAllSUVWith4By4() {
        return suvs.stream()
                   .filter(SUV::has4by4)
                   .collect(Collectors.toList());
    }

    public List<Vehicle> getAllCarsWithEquipmentLevel(EquipmentLevel equipmentLevel) {
        return cars.stream()
                   .filter(car -> car.getEquipmentLevel() == equipmentLevel)
                   .collect(Collectors.toList());
    }

    public Vehicle getCheapestVehicle(List<Vehicle> vehicles) {
        if (vehicles == null || vehicles.isEmpty()) {
            return null;
        }
        return vehicles.stream()
                       .min(Comparator.comparingDouble(Vehicle::getPrice))
                       .orElse(null);
    }

    public void sellVehicle(int vehicleId) throws Exception {
        Vehicle vehicle = findVehicleById(vehicleId);
        if (vehicle == null) {
            throw new Exception("Vehicle with ID " + vehicleId + " not found");
        }
        turnover += vehicle.getPrice();
        if (vehicle instanceof Car) {
            cars.remove(vehicle);
        } else if (vehicle instanceof SUV) {
            suvs.remove(vehicle);
        } else if (vehicle instanceof Truck) {
            trucks.remove(vehicle);
        }
    }
}

