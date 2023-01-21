package practice.OOP.povishitelen;

public class GondolaLift extends Lift {
    public GondolaLift() {
        this.name = "Gondola Lift";
        this.capacity = 0;
        this.manifactureYear = 0;
        this.speed = 0;
    }

    public GondolaLift(String name, int capacity, int manifactureYear, int speed) {
        this.name = name;
        if(capacity <= 25 && capacity >= 6){
            this.capacity = capacity;
        } else {
            throw new IllegalArgumentException("Capacity must be between 6 and 25");
        }

        if(manifactureYear > 1930 && manifactureYear < 9999){
            this.manifactureYear = manifactureYear;
        } else {
            throw new IllegalArgumentException("Manifacture year must be between 1930 and consist of four digits");
        }

        this.speed = speed;
    }

    @Override
    public double getRating() {
        if(capacity > 15)
            return (capacity + manifactureYear + speed + 1200)/10;
        return (capacity + manifactureYear + speed + 600)/10;
    }
    
}
