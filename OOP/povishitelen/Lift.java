package practice.OOP.povishitelen;

public abstract class Lift {
    String name;
    int capacity;
    int manifactureYear;
    int speed;

    public Lift() {
        this.name = "Lift";
        this.capacity = 0;
        this.manifactureYear = 0;
        this.speed = 0;
    }

    public Lift(String name, int capacity, int manifactureYear, int speed) {
        this.name = name;

        if(capacity > 25 && capacity < 0){
            this.capacity = capacity;
        } else {
            throw new IllegalArgumentException("Capacity must be between 0 and 25");
        }

        if(manifactureYear > 1930 && manifactureYear < 9999){
            this.manifactureYear = manifactureYear;
        } else {
            throw new IllegalArgumentException("Manifacture year must be between 1930 and consist of four digits");
        }

        this.manifactureYear = manifactureYear;
        this.speed = speed;
    }

    public abstract double getRating();
}

    