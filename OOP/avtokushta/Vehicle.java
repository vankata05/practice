package practice.OOP.avtokushta;

class Vehicle {
    private int id;
    private String maker;
    private String model;
    private int year;
    private String color;
    private double price;

    public Vehicle(int id, String maker, String model, int year, String color, double price) {
        this.id = id;
        this.maker = maker;
        this.model = model;
        this.year = year;
        this.color = color;
        this.price = price;
    }

    public int getId() {
        return id;
    }

    public String getMaker() {
        return maker;
    }

    public String getModel() {
        return model;
    }

    public int getYear() {
        return year;
    }

    public String getColor() {
        return color;
    }

    public double getPrice() {
        return price;
    }

    public EquipmentLevel getEquipmentLevel() {
        return null;
    }
}