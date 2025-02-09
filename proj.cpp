#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Structure to store food/drink details
struct FoodItem {
    string name;
    int cost;
};

// Structure to store customer order details
struct Order {
    string houseNumber;
    string phoneNumber;
    string address;
    string deliveryTime;
    vector<pair<string, int>> items; // List of items and their quantities
    int totalCost;
};

// Function to display the seller menu
void menutseller(const vector<Order>& orders) {
    cout << "\n--- Seller Menu ---" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Show customer order " << endl;
    cout << "3. View or  Delete menu " << endl;
    cout << "4. Exit" << endl;

    int sellerexit;
    cout << "Enter your choice: ";
    cin >> sellerexit;

    if (sellerexit == 2) {
        // Display all customer orders
        cout << "\n--- Customer Orders ---" << endl;
        for (size_t i = 0; i < orders.size(); i++) {
            cout << "Order " << i + 1 << ":" << endl;
            cout << "House Number: " << orders[i].houseNumber << endl;
            cout << "Phone Number: " << orders[i].phoneNumber << endl;
            cout << "Address: " << orders[i].address << endl;
            cout << "Delivery Time: " << orders[i].deliveryTime << endl;
            cout << "Items:" << endl;
            for (const auto& item : orders[i].items) {
                cout << "  " << item.first << " x " << item.second << endl;
            }
            cout << "Total Cost: " << orders[i].totalCost << endl;
            cout << "-----------------------------" << endl;
        }
    }
}

// Function to display the customer menu
void menuCustomer(vector<Order>& orders, const vector<FoodItem>& foodItems) {
    cout << "\n--- Customer Menu ---" << endl;

    // Display the food items in a table format
    cout << "\n--- Food/Drink List ---" << endl;
    cout << "No.\tName\t\tCost" << endl;
    for (size_t i = 0; i < foodItems.size(); i++) {
        cout << i + 1 << "\t" << foodItems[i].name << "\t\t" << foodItems[i].cost << endl;
    }

    // Allow the customer to select items and quantities
    vector<int> quantities(foodItems.size(), 0); // Initialize quantities to 0
    int itemNumber, quantity;
    int totalCost = 0;

    while (true) {
        cout << "select the  order (or 0 to finish): ";
        cin >> itemNumber;

        if (itemNumber == 0) {
            break; // Exit the loop if the customer is done selecting items
        }
        if (itemNumber > 0 && itemNumber <= foodItems.size()) {
            cout << "Enter the quantity for " << foodItems[itemNumber - 1].name << ": ";
            cin >> quantity;

            if (quantity > 0) {
                quantities[itemNumber - 1] += quantity; // Update the quantity
                totalCost += foodItems[itemNumber - 1].cost * quantity; // Update the total cost
            } else {
                cout << "Quantity must be greater than 0. Try again." << endl;
            }
        } else {
            cout << "Invalid item number. Try again." << endl;
        }
    }

    // Display the selected items and total cost
    cout << "\n--- Your Order ---" << endl;
    for (size_t i = 0; i < foodItems.size(); i++) {
        if (quantities[i] > 0) {
            cout << foodItems[i].name << " x " << quantities[i] << " = " << foodItems[i].cost * quantities[i] << endl;
        }
    }
    cout << "Total Cost: " << totalCost << endl;

    // Collect delivery information
    string houseNumber, phoneNumber, address, deliveryTime;
    cin.ignore(); // Clear the input buffer

    cout << "\nEnter your house number: ";
    getline(cin, houseNumber);

    cout << "Enter your phone number: ";
    getline(cin, phoneNumber);

    cout << "Enter your physical address: ";
    getline(cin, address);

    cout << "Enter the delivery time: ";
    getline(cin, deliveryTime);

    // Verify the total cost
    int customerTotal;
    while (true) {
        cout << "Enter the total cost to confirm your order: ";
        cin >> customerTotal;

        if (customerTotal == totalCost) {
            cout << "\nThank you for your order!" << endl;
            cout << "Your order will be delivered to:" << endl;
            cout << "House Number: " << houseNumber << endl;
            cout << "Phone Number: " << phoneNumber << endl;
            cout << "Address: " << address << endl;
            cout << "Delivery Time: " << deliveryTime << endl;

            // Save the order details
            Order order;
            order.houseNumber = houseNumber;
            order.phoneNumber = phoneNumber;
            order.address = address;
            order.deliveryTime = deliveryTime;
            order.totalCost = totalCost;
            for (size_t i = 0; i < foodItems.size(); i++) {
                if (quantities[i] > 0) {
                    order.items.push_back({foodItems[i].name, quantities[i]});
                }
            }
            orders.push_back(order);

            break;
        } else {
            cout << "Incorrect total cost. Please try again." << endl;
        }
    }
}

// Function to display the main menu
void menu() {
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Administrator" << endl;
    cout << "2. Customer" << endl;
    cout << "3. Exit" << endl;
}

// Function to handle the exit option
void Exit() {
    cout << "Closing the food ordering process. Goodbye!" << endl;
    exit(0); // Terminate the program
}

// Function to save food items to a file
void saveToFile(const vector<FoodItem>& items) {
    ofstream file("food_items.txt");
    for (const auto& item : items) {
        file << item.name << "," << item.cost << endl;
    }
    file.close();
}

// Function to load food items from a file
void loadFromFile(vector<FoodItem>& items) {
    ifstream file("food_items.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            string name = line.substr(0, commaPos);
            int cost = stoi(line.substr(commaPos + 1));
            items.push_back({name, cost});
        }
        file.close();
    }
}

int main() {
    int choose_darshbord, password = 123, password2;
    int sellerexit, cost;
    string food;
    vector<FoodItem> foodItems;
    vector<Order> orders;

    // Load food items from file at the start of the program
    loadFromFile(foodItems);

    while (true) { // Loop to keep the program running
        // Display the main menu
        menu();

        // Take input from the user
        cout << "You are customer or administrator select correct option: ";
        cin >> choose_darshbord;

        // Process the user's choice
        switch (choose_darshbord) {
            case 1: // Seller option
                cout << "Enter password: ";
                cin >> password2;

                if (password == password2) {
                    menutseller(orders); // Display seller menu if password is correct

                    // Take input for seller menu options
                    cout << "select correct option: ";
                    cin >> sellerexit;

                    if (sellerexit == 4) {
                        Exit(); // Exit the program
                    } else if (sellerexit == 1) {
                        // Clear the input buffer to avoid issues with getline
                        cin.ignore();

                        // Take input for food name and cost
                        cout << "Enter the food name or drink: ";
                        getline(cin, food);

                        cout << "Enter the cost of the food or drink: ";
                        cin >> cost;

                        // Add the food item to the vector
                        foodItems.push_back({food, cost});

                        // Save the updated list to the file
                        saveToFile(foodItems);

                        cout << "Food/Drink added successfully!" << endl << endl;
                    } else if (sellerexit == 3) {
                        // Display the food items in a table format
                        cout << "\n--- Food/Drink List ---" << endl;
                        cout << "No.\tName\t\tCost" << endl;
                        for (size_t i = 0; i < foodItems.size(); i++) {
                            cout << i + 1 << "\t" << foodItems[i].name << "\t\t" << foodItems[i].cost << endl;
                        }

                        // Allow the seller to delete an item
                        int deleteChoice;
                        cout << "Enter the number of the item to delete (or 0 to cancel): ";
                        cin >> deleteChoice;

                        if (deleteChoice > 0 && deleteChoice <= foodItems.size()) {
                            foodItems.erase(foodItems.begin() + deleteChoice - 1);
                            saveToFile(foodItems); // Save the updated list to the file
                            cout << "Item deleted successfully!" << endl << endl;
                        } else if (deleteChoice != 0) {
                            cout << "Invalid choice. No item deleted." << endl << endl;
                        }
                    }
                } else {
                    cout << "Wrong password! You are not authorized." << endl << endl;
                }
                break;

            case 2: // Customer option
                menuCustomer(orders, foodItems);
                break;

            case 3: // Exit option
                Exit();
                break;

            default:
                cout << "Wrong choice! Please try again." << endl;
                break;
        }
    }

    return 0;
}
