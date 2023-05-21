package practice.OOP.HW3;

public class Product{
    int id;
    String name;
    String description;
    Category category;
    double price;

    public Product(int id, String name, String description, Category category, double price){
        this.id = id;
        this.name = name;
        this.description = description;
        this.category = category;
        this.price = price;
    }
}