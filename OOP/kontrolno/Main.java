package practice.OOP.kontrolno;

import java.util.List;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        BookStore bookstore = new BookStore("My Bookstore");

        Book book1 = new Book("9783161484100", "J.K. Rowling", "Harry Potter and the Philosopher's Stone", "A boy wizard saves the world", 9.99);
        Book book2 = new Book("9780439064873", "J.K. Rowling", "Harry Potter and the Chamber of Secrets", "More adventures at Hogwarts", 8.99);
        Other item1 = new Other("0123456789012", "Pencil", 0.05, 0.99);
        Other item2 = new Other("0987654321098", "Notebook", 0.2, 2.99);
        bookstore.addBook(new Pair<>(book1, 10));
        bookstore.addBook(new Pair<>(book2, 5));
        bookstore.addOther(new Pair<>(item1, 100));
        bookstore.addOther(new Pair<>(item2, 50));

        double totalValue = bookstore.getBookStorePrice();
        System.out.println("Total value of all items in the bookstore: " + totalValue);

        Pair<?, Integer> cheapestItem = bookstore.getCheapestItem();
        if(cheapestItem.getFirst() instanceof Book){
            System.out.println("Cheapest item in the bookstore: " + ((Book) cheapestItem.getFirst()).getName() + " ($" + ((Book) cheapestItem.getFirst()).getPrice() + ")");
        }else{
            System.out.println("Cheapest item in the bookstore: " + ((Other) cheapestItem.getFirst()).getName() + " ($" + ((Other) cheapestItem.getFirst()).getPrice() + ")");
        }

        Map<String, List<Book>> booksByAuthor = bookstore.getBooksByAuthor();
        for (String author : booksByAuthor.keySet()) {
            List<Book> books = booksByAuthor.get(author);
            System.out.println("Books by " + author + ": " + books.toString());
        }

        Book book3 = bookstore.getBook("9783161484100");
        System.out.println("Book found by ISBN: " + book3.toString());

        Other item3 = bookstore.getOther("0123456789012");
        System.out.println("Other item found by barcode: " + item3.toString());
    }
}
