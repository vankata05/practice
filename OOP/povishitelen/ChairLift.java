package practice.OOP.povishitelen;

public class ChairLift extends Lift{
    public ChairLift() {
        this.name = "Chair Lift";
        this.capacity = 0;
        this.manifactureYear = 0;
        this.speed = 0;
    }

    public ChairLift(String name, int capacity, int manifactureYear, int speed) {
        this.name = name;
        if(capacity <= 8 && capacity >= 2){
            this.capacity = capacity;
        } else {
            throw new IllegalArgumentException("Capacity must be between 2 and 8");
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
        if(manifactureYear > 2010)
            return (capacity + manifactureYear + speed + 500)/10;
        return (capacity + manifactureYear + speed + 200)/10;
    }
    
}
