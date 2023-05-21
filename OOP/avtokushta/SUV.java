package practice.OOP.avtokushta;

class SUV extends Vehicle {
    private boolean has4by4;
    private double clearance;

    public SUV(int id, String maker, String model, int year, String color, double price, boolean has4by4, double clearance) {
        super(id, maker, model, year, color, price);
        this.has4by4 = has4by4;
        this.clearance = clearance;
    }

    public boolean has4by4() {
        return has4by4;
    }

    public double getClearance() {
        return clearance;
    }
}

