package practice.OOP.kontrolno;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class BookStore {
    final String name;
    final Collection<Pair<Book, Integer>> books;
    final Collection<Pair<Other, Integer>> others;

    public BookStore(String name) {
        this.name = name;
        this.books = new ArrayList<>();
        this.others = new ArrayList<>();
    }

    public void addBook(Pair<Book, Integer> book) {
        Book b = book.getFirst();
        int quantity = book.getSecond();
        for (Pair<Book, Integer> pair : books) {
            if (pair.getFirst().getIsbn().equals(b.getIsbn())) {
                pair.setSecond(pair.getSecond() + quantity);
                return;
            }
        }
        books.add(new Pair<>(b, quantity));
    }

    public void addOther(Pair<Other, Integer> other) {
        Other o = other.getFirst();
        int quantity = other.getSecond();
        for (Pair<Other, Integer> pair : others) {
            if (pair.getFirst().getBarcode().equals(o.getBarcode())) {
                pair.setSecond(pair.getSecond() + quantity);
                return;
            }
        }
        others.add(new Pair<>(o, quantity));
    }

    public double getBookStorePrice() {
        double totalPrice = 0.0;
        for (Pair<Book, Integer> pair : books) {
            totalPrice += pair.getFirst().getPrice() * pair.getSecond();
        }
        for (Pair<Other, Integer> pair : others) {
            totalPrice += pair.getFirst().getPrice() * pair.getSecond();
        }
        return totalPrice;
    }

    public Pair<?, Integer> getCheapestItem() {
        Pair<?, Integer> cheapest = null;
        double minPrice = Double.MAX_VALUE;
        for (Pair<Book, Integer> pair : books) {
            double price = pair.getFirst().getPrice();
            if (price < minPrice) {
                cheapest = pair;
                minPrice = price;
            }
        }
        for (Pair<Other, Integer> pair : others) {
            double price = pair.getFirst().getPrice();
            if (price < minPrice) {
                cheapest = pair;
                minPrice = price;
            }
        }
        return cheapest;
    }

    public Map<String, List<Book>> getBooksByAuthor() {
        Map<String, List<Book>> booksByAuthor = new HashMap<>();
        for (Pair<Book, Integer> pair : books) {
            Book book = pair.getFirst();
            String author = book.getAuthor();
            if (author != null) {
                List<Book> books = booksByAuthor.computeIfAbsent(author, k -> new ArrayList<>());
                books.add(book);
            }
        }
        return booksByAuthor;
    }

    public Book getBook(String isbn) {
        for (Pair<Book, Integer> pair : books) {
            if (pair.getFirst().getIsbn().equals(isbn)) {
                return pair.getFirst();
            }
        }
        throw new IllegalArgumentException("Book with ISBN " + isbn + " not found");
    }

    public Other getOther(String barcode) {
        for (Pair<Other, Integer> pair : others) {
            if (pair.getFirst().getBarcode().equals(barcode)) {
                return pair.getFirst();
            }
        }
        throw new IllegalArgumentException("Other item with barcode " + barcode + " not found");
    }
}