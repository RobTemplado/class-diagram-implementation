#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

class Product {
public:
    Product(string productID, string name, string description, double price) :
        productID(productID), name(name), description(description), price(price) {}

    string getProductID() const { return productID; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    double getPrice() const { return price; }

    string getDetails() const {
        return "Product ID: " + productID + "\n" +
               "Name: " + name + "\n" +
               "Description: " + description + "\n" +
               "Price: $" + to_string(price) + "\n";
    }

private:
    string productID;
    string name;
    string description;
    double price;
};

class CartItem {
public:
    CartItem(Product* product, int quantity) : product(product), quantity(quantity) {}

    Product* getProduct() const { return product; }
    int getQuantity() const { return quantity; }

    void addQuantity(int amount) { quantity += amount; }
    double calculateTotal() const { return product->getPrice() * quantity; }

private:
    Product* product;
    int quantity;
};

class ShoppingCart {
public:
    void addProduct(Product* product, int quantity) {
        for (CartItem& item : items) {
            if (item.getProduct() == product) {
                item.addQuantity(quantity);
                return;
            }
        }
        items.push_back(CartItem(product, quantity));
    }

    vector<CartItem> getItems() const { return items; }

    double calculateTotal() const {
        double total = 0;
        for (const CartItem& item : items) {
            total += item.calculateTotal();
        }
        return total;
    }

    void clearCart() { items.clear(); }

private:
    vector<CartItem> items;
};

class Customer {
public:
    Customer(int customerID, string name, string email, string address) :
        customerID(customerID), name(name), email(email), address(address) {}

    void addToCart(Product* product, int quantity) {
        shoppingCart.addProduct(product, quantity);
    }

    ShoppingCart getShoppingCart() const { return shoppingCart; }

    void placeOrder() {
        cout << "Order placed successfully!\n";
        shoppingCart.clearCart(); // Clear cart after placing the order
    }

private:
    int customerID;
    string name;
    string email;
    string address;
    ShoppingCart shoppingCart;
};

// Function to display the menu
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. View Products\n";
    cout << "2. Add Product to Cart\n";
    cout << "3. View Shopping Cart\n";
    cout << "4. Checkout\n";
    cout << "5. Exit\n";
}

// Function to display products in a table format
void displayProducts(const vector<Product>& products) {
    cout << "\nProducts:\n";
    cout << setw(15) << "Product ID" << setw(20) << "Name" << setw(15) << "Price\n";
    cout << "----------------------------------------\n";
    for (const Product& product : products) {
        cout << setw(15) << product.getProductID() << setw(20) << product.getName() << setw(15) << product.getPrice() << endl;
    }
}

// Function to display shopping cart items in a table format
void displayShoppingCart(const ShoppingCart& cart) {
    cout << "\nShopping Cart:\n";
    cout << setw(15) << "Product ID" << setw(20) << "Name" << setw(15) << "Price" << setw(15) << "Quantity\n";
    cout << "--------------------------------------------------------------------\n";
    for (const CartItem& item : cart.getItems()) {
        cout << setw(15) << item.getProduct()->getProductID() << setw(20) << item.getProduct()->getName() << setw(15) << item.getProduct()->getPrice() << setw(15) << item.getQuantity() << endl;
    }
}

char toUpper(char ch) {
    return toupper(static_cast<unsigned char>(ch));
}

int main() {
    // Create a list of products
    vector<Product> products = {
        Product("ABC1", "AirPods1stGen", "First Generation", 8000.00),
        Product("ABC2", "AirPods2ndGen", "Second Generation", 10000.00),
        Product("ABC3", "AirPods3rdGen", "Third Generation", 12000.00),
        Product("ABCPRO", "AirPodsPro", "First Generation of Pro ", 15000.00),
        Product("ABCMAX", "AirPodsMax", "First Generation of AirPodsMax ", 30000.00),
    };

    // Create a customer
    Customer customer(1, "John Doe", "johndoe@example.com", "123 Main St");

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                displayProducts(products);
                break;
            }
            case 2: {
                bool addMore = true;

                while (addMore) {
                    string productID;
                    int quantity;
                    bool productFound = false;

                    cout << "Enter the Product ID to add to cart: ";
                    cin >> productID;
                    cout << "Enter the quantity: ";
                    cin >> quantity;

                    for (Product& product : products) {
                        if (product.getProductID() == productID) {
                            customer.addToCart(&product, quantity);
                            productFound = true;
                            break;
                        }
                    }

                    if (!productFound) {
                        cout << "Invalid Product ID.\n";
                    } else {
                        char continueAdding;
                        cout << "Product added to cart. Do you want to add more products? (Y/N): ";
                        cin >> continueAdding;

                        // Convert input to uppercase for case-insensitive comparison
                        continueAdding = toUpper(continueAdding);

                        if (continueAdding != 'Y') {
                            addMore = false;
                        }
                    }
                }

                break;
            }
            case 3:
                displayShoppingCart(customer.getShoppingCart());
                break;
            case 4: {
                ShoppingCart cart = customer.getShoppingCart();
                if (cart.getItems().empty()) {
                    cout << "Your shopping cart is empty.\n";
                } else {
                    cout << "Total amount to pay: PHP" << cart.calculateTotal() << endl;
                    char proceedCheckout;
                    cout << "Do you want to proceed to checkout? (Y/N): ";
                    cin >> proceedCheckout;
                    proceedCheckout = toUpper(proceedCheckout);

                    if (proceedCheckout == 'Y') {
                        customer.placeOrder();
                    } else {
                        cout << "Checkout canceled.\n";
                    }
                }
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}