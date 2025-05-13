#include <iostream>
#include <vector>
using namespace std;

class Burger {
public:
    bool meat = false;
    bool vegetarian = false;
    bool ketchup = false;
    bool mustard = false;
    bool lettuce = false;
    bool onions = false;
    bool pickles = false;
    bool tomato = false;
    bool cheese = false; // New topping
    

    // Method to loop and choose toppings
    void ToppingLoop() {
        int choice;
        do {
            // Displaying Topping Options
            cout << "\nChoose your toppings:\n";
            cout << "1. Meat\n";
            cout << "2. Vegetarian\n";
            cout << "3. Ketchup\n";
            cout << "4. Mustard\n";
            cout << "5. Lettuce\n";
            cout << "6. Onions\n";
            cout << "7. Pickles\n";
            cout << "8. Tomato\n";
            cout << "9. Cheese\n";
            cout << "10. Finish selection\n";
            cout << "Enter choice: ";
            cin >> choice;

            // Setting toppings based on user choice
            switch (choice) {
                case 1: 
                    if (vegetarian) {
                        cout << "You cannot have both Meat and Vegetarian on the same burger.\n";
                    } else {
                        meat = true;
                        cout << "Meat added.\n";
                    }
                    break;
                case 2:  
                    if (meat) {
                        cout << "You cannot have both Meat and Vegetarian on the same burger.\n";
                    } else {
                        vegetarian = true;
                        cout << "Vegetarian option added.\n";
                    }
                    break;
                case 3: ketchup = true; break;
                case 4: mustard = true; break;
                case 5: lettuce = true; break;
                case 6: onions = true; break;
                case 7: pickles = true; break;
                case 8: tomato = true; break;
                case 9: cheese = true; break;
                case 10: 
                    cout << "Topping selection complete.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 10);
    }

    // Method to display the final burger order
    void DisplayOrder(int burgerNumber) {
        cout << "\nBurger " << burgerNumber + 1 << ":\n";
        
        // Displaying the type of burger
        if (meat) cout << "Type: Meat\n";
        if (vegetarian) cout << "Type: Vegetarian\n";
        
        cout << "Toppings:\n";
        bool hasToppings = false;
        if (ketchup) { cout << "- Ketchup\n"; hasToppings = true; }
        if (mustard) { cout << "- Mustard\n"; hasToppings = true; }
        if (lettuce) { cout << "- Lettuce\n"; hasToppings = true; }
        if (onions) { cout << "- Onions\n"; hasToppings = true; }
        if (pickles) { cout << "- Pickles\n"; hasToppings = true; }
        if (tomato) { cout << "- Tomato\n"; hasToppings = true; }
        if (cheese) { cout << "- Cheese\n"; hasToppings = true; }

        if (!hasToppings) {
            cout << "- No toppings selected.\n";
        }
    }
};

// Main function
int main() {
    vector<Burger> burgers;
    int numofburgers;

    // Asking for number of burgers
    cout << "Enter amount of Burgers: ";
    cin >> numofburgers;
    cin.ignore(); // Clear input buffer

    // Creating each burger and customizing it
    for (int i = 0; i < numofburgers; i++) {
        cout << "\nConfiguring Burger " << i + 1 << ":\n";
        Burger tempBurger;
        tempBurger.ToppingLoop();
        burgers.push_back(tempBurger);
    }

    // Displaying all burger orders
    cout << "\nOrder Summary:\n";
    for (int i = 0; i < burgers.size(); i++) {
        burgers[i].DisplayOrder(i);
    }

    return 0;
}
