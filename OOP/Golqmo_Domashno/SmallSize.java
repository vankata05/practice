package practice.OOP.Golqmo_Domashno;

public class SmallSize extends Package {

    public SmallSize(int size, boolean salable) {
        if(size >= 1 && size <= 3){
            this.size = size;
        }else{
            throw new IllegalArgumentException("Size must be between 1 and 3");
        }
        this.salable = salable;
    }

    @Override
    public double getDeliveryPrice() {
        double price = size * 3;
        if(salable){
            price += price*0.1;
        }
        return price;
    }
}
