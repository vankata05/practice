package practice.OOP.kontrolno;

public class Book {
    private final String isbn;
    private String author;
    private String name;
    private String description;
    private double price;

    public Book(String isbn, double price) {
        if (!isValidIsbn(isbn)) {
            throw new IllegalArgumentException("Invalid ISBN");
        }
        this.isbn = isbn;
        if(price <= 0){
            throw new IllegalArgumentException("Price must be non-negative");
        }
        this.price = price;
    }

    public Book(String string, String string2, String string3, String string4, double d) {
        if(!isValidIsbn(string)){
            throw new IllegalArgumentException("Invalid ISBN");
        }
        this.isbn = string;
        this.author = string2;
        this.name = string3;
        this.description = string4;
        if(d < 0){
            throw new IllegalArgumentException("Price must be non-negative");
        }
        this.price = d;
    }

    public String getIsbn() {
        return isbn;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        if (price < 0) {
            throw new IllegalArgumentException("Price must be non-negative");
        }
        this.price = price;
    }

    private boolean isValidIsbn(String isbn) {
        int length = isbn.length();
        if (length != 10 && length != 13) {
            return false;
        }
        for (int i = 0; i < length; i++) {
            char c = isbn.charAt(i);
            if (c < '0' || c > '9') {
                return false;
            }
        }
        return true;
    }
}
