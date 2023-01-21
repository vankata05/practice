package practice.OOP.povishitelen;

public class TBarLift extends Lift{
    public TBarLift() {
        this.name = "T-Bar Lift";
        this.capacity = 0;
        this.manifactureYear = 0;
        this.speed = 0;
    }

    public TBarLift(String name, int capacity, int manifactureYear, int speed) {
        this.name = name;
        if(capacity <= 2){
            this.capacity = capacity;
        } else {
            throw new IllegalArgumentException("Capacity must be less than 2");
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
        return (capacity + manifactureYear + speed)/10;
    }
}
