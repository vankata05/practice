package practice.OOP.avtokushta;

class Truck extends Vehicle {
    private int maxLoadWeight;
    private double maxLoadVolume;

    public Truck(int id, String maker, String model, int year, String color, double price, int maxLoadWeight, double maxLoadVolume) {
        super(id, maker, model, year, color, price);
        this.maxLoadWeight = maxLoadWeight;
        this.maxLoadVolume = maxLoadVolume;
    }

    public int getMaxLoadWeight() {
        return maxLoadWeight;
    }

    public double getMaxLoadVolume() {
        return maxLoadVolume;
    }
}