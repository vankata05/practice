package practice.OOP.avtokushta;

class Car extends Vehicle {
    private int seatNumber;
    private int doorsNumber;
    private EquipmentLevel equipmentLevel;

    public Car(int id, String maker, String model, int year, String color, double price, int seatNumber, int doorsNumber, EquipmentLevel equipmentLevel) {
        super(id, maker, model, year, color, price);
        this.seatNumber = seatNumber;
        this.doorsNumber = doorsNumber;
        this.equipmentLevel = equipmentLevel;
    }

    public int getSeatNumber() {
        return seatNumber;
    }

    public int getDoorsNumber() {
        return doorsNumber;
    }

    public EquipmentLevel getEquipmentLevel() {
        return equipmentLevel;
    }
}