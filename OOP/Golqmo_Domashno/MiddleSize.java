package practice.OOP.Golqmo_Domashno;

public class MiddleSize extends Package {

    public MiddleSize(int size, boolean salable) {
        if(size >= 4 && size <= 6){
            this.size = size;
        }else{
            throw new IllegalArgumentException("Size must be between 4 and 6");
        }
        this.salable = salable;
    }

    @Override
    public double getDeliveryPrice() {
        double price = size * 4;
        if(salable){
            price += price*0.1;
        }
        return price;
    }
}
