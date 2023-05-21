package practice.OOP.kontrolno;

public class Other{
    private final String barcode;
    private String name;
    private double weight;
    private double price;

    public Other(String barcode, double price) {
        if (!isValidBarcode(barcode)) {
            throw new IllegalArgumentException("Invalid barcode");
        }
        if (price <= 0) {
            throw new IllegalArgumentException("Price must be positive");
        }
        this.barcode = barcode;
        this.price = price;
    }

    public Other(String string, String string2, double d, double e) {
        if(!isValidBarcode(string)){
            throw new IllegalArgumentException("Invalid barcode");
        }
        this.barcode = string;
        this.name = string2;
        this.weight = d;
        if(e <= 0){
            throw new IllegalArgumentException("Price must be positive");
        }
        this.price = e;
    }

    public String getBarcode() {
        return barcode;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        if (price <= 0) {
            throw new IllegalArgumentException("Price must be positive");
        }
        this.price = price;
    }

    private boolean isValidBarcode(String barcode) {
        int length = barcode.length();
        if (length != 13) {
            return false;
        }
        for (int i = 0; i < length; i++) {
            char c = barcode.charAt(i);
            if (c < '0' || c > '9') {
                return false;
            }
        }
        return true;
    }
}
