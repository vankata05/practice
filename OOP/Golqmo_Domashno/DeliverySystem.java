package practice.OOP.Golqmo_Domashno;

public class DeliverySystem {
    User[] users;
    Order[] orders;
    Adress[] adresses;
    User currentUser;

    public DeliverySystem() {
        //add admin user with username admin and pasword admin123
        if(users == null) {
            users = new User[1];
            users[0] = new User("admin", "admin123", Role.ADMINISTRATOR);
        }
    }

    public void login(String username, String password) {
        for (User user : users) {
            if(user.getUsername().equals(username) && user.getPassword().equals(password)) {
                currentUser = user;
                break;
            }
        }
    }

    public void logout() {
        currentUser = null;
    }

    public void registerUser(String username, String password){
        if(currentUser.getRole() == Role.ADMINISTRATOR) {
            User[] temp = new User[users.length + 1];
            for (int i = 0; i < users.length; i++) {
                temp[i] = users[i];
            }
            temp[temp.length - 1] = new User(username, password, Role.CUSTOMER);
            users = temp;
        }else{
            throw new IllegalArgumentException("Only administrators can register users");
        }
    }

    public void registerDriver(String username, String password){
        if(currentUser.getRole() == Role.ADMINISTRATOR) {
            User[] temp = new User[users.length + 1];
            for (int i = 0; i < users.length; i++) {
                temp[i] = users[i];
            }
            temp[temp.length - 1] = new User(username, password, Role.DRIVER);
            users = temp;
        }else{
            throw new IllegalArgumentException("Only administrators can register drivers");
        }
    }

    public void addAdress(Adress address){
        if(currentUser.getRole() == Role.CUSTOMER) {
            Adress[] temp = new Adress[adresses.length + 1];
            for (int i = 0; i < adresses.length; i++) {
                temp[i] = adresses[i];
            }
            temp[temp.length - 1] = address;
            adresses = temp;
        }else{
            throw new IllegalArgumentException("Only customers can add adresses");
        }
    }

    public void addOrder(Order order){
        if(currentUser.getRole() == Role.CUSTOMER) {
            Order[] temp = new Order[orders.length + 1];
            for (int i = 0; i < orders.length; i++) {
                temp[i] = orders[i];
            }
            temp[temp.length - 1] = order;
            orders = temp;
        }else{
            throw new IllegalArgumentException("Only customers can add orders");
        }
    }

    public void addPackage(Package pac, int orderId){
        if(currentUser.getRole() == Role.CUSTOMER) {
            for (Order order : orders) {
                if(order.getId() == orderId) {
                    order.addPackage(pac);
                    break;
                }
            }
        }else{
            throw new IllegalArgumentException("Only customers can add packages");
        }
    }

    public Order getOrderToDeliver(){
        if(currentUser.getRole() == Role.DRIVER) {
            for (Order order : orders) {
                if(order.getStatus() == Status.CREATED) {
                    return order;
                }
            }
        }else{
            throw new IllegalArgumentException("Only drivers can get orders to deliver");
        }
        return null;
    }

    public Order getOrderToDeliver(int id){
        if(currentUser.getRole() == Role.DRIVER) {
            for (Order order : orders) {
                if(order.getId() == id) {
                    if(order.getStatus() == Status.CREATED) {
                        return order;
                    }else{
                        throw new IllegalArgumentException("Order has to be created");
                    }
                }
            }
        }else{
            throw new IllegalArgumentException("Only drivers can get orders to deliver");
        }
        return null;
    }

    public void deliverOrder(int id){
        if(currentUser.getRole() == Role.DRIVER) {
            for (Order order : orders) {
                if(order.getId() == id) {
                    if(order.getStatus() == Status.CREATED) {
                        order.setStatus(Status.DELIVERED);
                        break;
                    }else{
                        throw new IllegalArgumentException("Order has to be created");
                    }
                }
            }
        }else{
            throw new IllegalArgumentException("Only drivers can deliver orders");
        }
    }

}
