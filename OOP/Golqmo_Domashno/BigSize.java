package practice.OOP.Golqmo_Domashno;

public class BigSize extends Package {

    public BigSize(int size, boolean salable) {
        if(size >= 7 && size <= 9){
            this.size = size;
        }else{
            throw new IllegalArgumentException("Size must be between 7 and 9");
        }
        this.salable = salable;
    }

    @Override
    public double getDeliveryPrice() {
        double price = size * 5;
        if(salable){
            price += price*0.1;
        }
        return price;
    }
}
