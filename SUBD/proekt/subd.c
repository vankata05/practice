#include <stdio.h>
#include <sqlite3.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

int createDB(){
    sqlite3* db;
    char* err_msg = 0;
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

char* sql = "CREATE TABLE IF NOT EXISTS Orders("
    "Id INTEGER PRIMARY KEY, Name VARCHAR(255), Quantity INT, Type VARCHAR(1), Price FLOAT, Date TIMESTAMP, CustomerId INTEGER"
    ");"
    "CREATE TABLE IF NOT EXISTS Customers("
    "Id INTEGER PRIMARY KEY, Name VARCHAR(255), Email VARCHAR(255), Phone VARCHAR(20)"
    ");"
    "CREATE TABLE IF NOT EXISTS Todo("
    "Id INTEGER REFERENCES Orders(Id)"
    ");";

    // printf("\n%s\n", sql);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s", err_msg);
        
        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}

int insertTodo(){
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "INSERT INTO Todo VALUES((SELECT MAX(Id) FROM Orders));";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int insertOrder(char* name, int quantity, char* type, float price, char* date, int customerId) {
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // ...

    char* sql;
    if(type[0] == '-'){
        sql = "INSERT INTO Orders VALUES(NULL, ?, ?, ?, -?, ?, ?);";
    }else if(type[0] == '+'){
        sql = "INSERT INTO Orders VALUES(NULL, ?, ?, ?, ?, ?, ?);";
    }else{
        fprintf(stderr, "Type must be '+' or '-'");
        return 1;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);
    sqlite3_bind_text(stmt, 3, type, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, price);
    sqlite3_bind_text(stmt, 5, date, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, customerId);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if(type[0] == '+'){
        insertTodo();
    }

    return 0;
}

int completeOrder(int id){
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "DELETE FROM Todo WHERE Id = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int deleteOrder(int id){
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "DELETE FROM Orders WHERE Id = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int alterOrder(int id){
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql;
    sqlite3_stmt *stmt;

    int choice;
    printf("What do you want to change?");
    printf("1. Name\n2. Quantity\n3. Type\n4. Price\n5. Date\n");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            printf("Enter new name: ");
            char* name;
            scanf("%ms", &name);
            sql = "UPDATE Orders SET Name = ? WHERE Id = ?;";
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
                return 1;
            }

            sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, id);

            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
                return 1;
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            break;
        case 2:
            printf("Enter new quantity: ");
            int quantity;
            scanf("%d", &quantity);
            sql = "UPDATE Orders SET Quantity = ? WHERE Id = ?;";
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
                return 1;
            }

            sqlite3_bind_int(stmt, 1, quantity);
            sqlite3_bind_int(stmt, 2, id);

            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
                return 1;
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            break;
        case 3:
            printf("Enter new type: ");
            char* type;
            scanf("%ms", &type);
            sql = "UPDATE Orders SET Type = ? WHERE Id = ?;";
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
                return 1;
            }

            sqlite3_bind_text(stmt, 1, type, -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, id);

            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
                return 1;
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            break;
        case 4:
            printf("Enter new price: ");
            float price;
            scanf("%f", &price);
            sql = "UPDATE Orders SET Price = ? WHERE Id = ?;";
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
                return 1;
            }

            sqlite3_bind_double(stmt, 1, price);
            sqlite3_bind_int(stmt, 2, id);

            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
                return 1;
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            break;
        case 5:
            printf("Enter new date: ");
            char* date;
            scanf("%ms", &date);
            sql = "UPDATE Orders SET Date = ? WHERE Id = ?;";
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
                return 1;
            }

            sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, id);

            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
                return 1;
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            break;
        default:
            printf("Invalid choice");
            break;
    }

    return 0;
}

int printBalance(){
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "SELECT SUM(Price) FROM Orders;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    printf("Balance: %d\n", sqlite3_column_int(stmt, 0));

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int printTodo(){
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "SELECT Todo.Id, Orders.Name, Orders.Quantity, Orders.Price FROM Todo LEFT JOIN Orders ON Todo.Id = Orders.Id;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    printf("| Id\t|Name\t|Quantity\t|Price  |\n|---------------------------------------|\n");
    while (rc == SQLITE_ROW) {
        printf("| %d\t|%s\t|%d\t\t|%d\t|\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2), sqlite3_column_int(stmt, 3));
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int printIncome(){
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "SELECT * FROM Orders WHERE Type = '+';";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    printf("| Id\t|Name\t|Quantity\t|Type\t|Price  |Date\t   |\n|----------------------------------------------------------|\n");
    while (rc == SQLITE_ROW) {
        printf("| %d\t|%s\t|%d\t\t|%s\t|%d\t|%s|\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2), sqlite3_column_text(stmt, 3), sqlite3_column_int(stmt, 4), sqlite3_column_text(stmt, 5));
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int printExpenses(){
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "SELECT * FROM Orders WHERE Type = '-';";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    printf("| Id\t|Name\t|Quantity\t|Type\t|Price  |Date\t   |\n|----------------------------------------------------------|\n");
    while (rc == SQLITE_ROW) {
        printf("| %d\t|%s\t|%d\t\t|%s\t|%d\t|%s|\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2), sqlite3_column_text(stmt, 3), sqlite3_column_int(stmt, 4), sqlite3_column_text(stmt, 5));
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int printCashFlow(){
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "SELECT * FROM Orders GROUP BY Price ORDER BY Price DESC;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    printf("| Id\t|Name\t|Quantity\t|Type\t|Price  |Date\t   |\n|----------------------------------------------------------|\n");
    while (rc == SQLITE_ROW) {
        printf("| %d\t|%s\t|%d\t\t|%s\t|%d\t|%s|\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2), sqlite3_column_text(stmt, 3), sqlite3_column_int(stmt, 4), sqlite3_column_text(stmt, 5));
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int printOrder(int id){
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "SELECT * FROM Orders WHERE Id = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    printf("| Id\t|Name\t|Quantity\t|Type\t|Price  |Date\t   |\n|----------------------------------------------------------|\n");
    while (rc == SQLITE_ROW) {
        printf("| %d\t|%s\t|%d\t\t|%s\t|%d\t|%s|\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2), sqlite3_column_text(stmt, 3), sqlite3_column_int(stmt, 4), sqlite3_column_text(stmt, 5));
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int addCustomer(char* name, char* email, char* phone) {
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "INSERT INTO Customers (Name, Email, Phone) VALUES (?, ?, ?);";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, phone, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int deleteCustomer(int id) {
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char* sql = "DELETE FROM Customers WHERE Id = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));

        return 1;
    }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));

        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int getCustomerOrders(int customerId) {
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char* sql = "SELECT * FROM Orders WHERE CustomerId = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_int(stmt, 1, customerId);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));
        return 1;
    }

    printf("| Id\t|Name\t|Quantity\t|Type\t|Price  |Date\t   |\n|----------------------------------------------------------|\n");
    while (rc == SQLITE_ROW) {
        printf("| %d\t|%s\t|%d\t\t|%s\t|%d\t|%s|\n", sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2),
               sqlite3_column_text(stmt, 3), sqlite3_column_int(stmt, 4),
               sqlite3_column_text(stmt, 5));

        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int getCustomerOrdersByDate(int customerId, char* date) {
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char* sql = "SELECT * FROM Orders WHERE CustomerId = ? AND Date = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));

        return 1;
    }

    sqlite3_bind_int(stmt, 1, customerId);
    sqlite3_bind_text(stmt, 2, date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));

        return 1;
    }

    printf("| Id\t|Name\t|Quantity\t|Type\t|Price  |Date\t   |\n|----------------------------------------------------------|\n");
    while (rc == SQLITE_ROW) {
        printf("| %d\t|%s\t|%d\t\t|%s\t|%d\t|%s|\n", sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2),
               sqlite3_column_text(stmt, 3), sqlite3_column_int(stmt, 4),
               sqlite3_column_text(stmt, 5));

        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int getCustomerOrdersByType(int customerId, char* type) {
    sqlite3* db;
    
    int rc = sqlite3_open("Biznis.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char* sql = "SELECT * FROM Orders WHERE CustomerId = ? AND Type = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s", sqlite3_errmsg(db));

        return 1;
    }

    sqlite3_bind_int(stmt, 1, customerId);
    sqlite3_bind_text(stmt, 2, type, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Failed to insert data: %s", sqlite3_errmsg(db));

        return 1;
    }

    printf("| Id\t|Name\t|Quantity\t|Type\t|Price  |Date\t   |\n|----------------------------------------------------------|\n");
    while (rc == SQLITE_ROW) {
        printf("| %d\t|%s\t|%d\t\t|%s\t|%d\t|%s|\n", sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2),
               sqlite3_column_text(stmt, 3), sqlite3_column_int(stmt, 4),
               sqlite3_column_text(stmt, 5));

        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int main() {
    int choice;

    createDB();

    do {
        printf("1. Add order\n2. Complete order\n3. Alter order\n4. Print balance\n5. Print todo list\n6. Print income\n7. Print expenses\n8. Print cash flow\n9. Get customer orders by date\n10. Get customer orders by type\n11. Add customer\n12. Delete customer\n13. Exit\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                system("clear");
                char* name, type;
                char* date;
                int quantity;
                float price;
                printf("Enter name of order: ");
                scanf("%ms", &name);
                printf("Enter quantity of order: ");
                scanf("%d", &quantity);
                printf("Enter type of order: ");
                scanf(" %c", &type);
                printf("Enter price of order: ");
                scanf("%f", &price);
                printf("Enter date of order in format dd.mm.yyyy: ");
                scanf("%ms", &date);
                int customerId;
                printf("Enter customer ID: ");
                scanf("%d", &customerId);
                insertOrder(name, quantity, &type, price, date, customerId);
                break;
            case 2:
                system("clear");
                int id;
                printTodo();
                printf("\nEnter id of order to complete: ");
                scanf("%d", &id);
                completeOrder(id);
                break;
            case 3:
                system("clear");
                int id2;
                printf("Enter id of order to alter: ");
                printTodo();
                printf("\n");
                scanf("%d", &id2);
                system("clear");
                printOrder(id2);
                printf("\n");

                alterOrder(id2);
                break;
            case 4:
                system("clear");
                printBalance();
                getchar();
                getchar();
                break;
            case 5:
                system("clear");
                printTodo();
                getchar();
                getchar();
                break;
            case 6:
                system("clear");
                printIncome();
                getchar();
                getchar();
                break;
            case 7:
                system("clear");
                printExpenses();
                getchar();
                getchar();
                break;
            case 8:
                system("clear");
                printCashFlow();
                getchar();
                getchar();
                break;
            case 9:
                system("clear");
                int customerIdByDate;
                char* dateByDate;
                printf("Enter customer ID: ");
                scanf("%d", &customerIdByDate);
                printf("Enter date in format dd.mm.yyyy: ");
                scanf("%ms", &dateByDate);
                getCustomerOrdersByDate(customerIdByDate, dateByDate);
                getchar();
                getchar();
                break;
            case 10:
                system("clear");
                int customerIdByType;
                char typeByType;
                printf("Enter customer ID: ");
                scanf("%d", &customerIdByType);
                printf("Enter order type (+/-): ");
                scanf(" %c", &typeByType);
                getCustomerOrdersByType(customerIdByType, &typeByType);
                getchar();
                getchar();
                break;
            case 11:
                system("clear");
                int newCustomerId;
                printf("Enter customer ID: ");
                scanf("%d", &newCustomerId);
                char* newCustomerName;
                printf("Enter customer name: ");
                scanf("%ms", &newCustomerName);
                addCustomer(newCustomerId, newCustomerName);
                getchar();
                getchar();
                break;
            case 12:
                system("clear");
                int deleteCustomerId;
                printf("Enter customer ID to delete: ");
                scanf("%d", &deleteCustomerId);
                deleteCustomer(deleteCustomerId);
                getchar();
                getchar();
                break;
            case 13:
                system("clear");
                printf("Goodbye!\n");
                sleep(1);
                break;
            default:
                printf("Invalid choice!\n");
                sleep(1);
                break;
        }
        system("clear");
    } while(choice != 13);
    return 0;
}
