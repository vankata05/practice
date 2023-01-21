package practice.OOP.povishitelen;

public class WinterResort {
    String name;
    Lift[] lifts;

    public WinterResort() {
        this.name = "Winter Resort";
        this.lifts = new Lift[0];
    }

    public WinterResort(String name){
        this.name = name;
        this.lifts = new Lift[0];
    }

    public void addLift(Lift lift){
        for (Lift lift1 : lifts) {
            if(lift1.name.equals(lift.name) && lift1.capacity == lift.capacity){
                throw new IllegalArgumentException("Lift with identical name and capacity already exists");
            }
        }

        Lift[] newLifts = new Lift[lifts.length + 1];
        for (int i = 0; i < lifts.length; i++) {
            newLifts[i] = lifts[i];
        }
        newLifts[lifts.length] = lift;
        lifts = newLifts;
    }
}
