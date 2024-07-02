#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Customer {
private:
    string name;
    int unitsConsumed;
public:
    Customer(const string& name, int unitsConsumed)
        : name(name), unitsConsumed(unitsConsumed) {}

    string getName() const {
        return name;
    }

    int getUnitsConsumed() const {
        return unitsConsumed;
    }

    double calculateBill() const {
        const double ratePerUnit = 10.5; // Rate per unit of electricity consumed
        return unitsConsumed * ratePerUnit;
    }
};

int main() {
    string name;
    int unitsConsumed;

    // Get customer details
    cout << "Enter customer name: ";
    getline(cin, name);

    cout << "Enter units consumed: ";
    cin >> unitsConsumed;

    // Create a Customer object
    Customer customer(name, unitsConsumed);

    // Generate the bill
    double billAmount = customer.calculateBill();

    // Print the bill
    cout << fixed << setprecision(2);
    cout << "\n--- Electricity Bill ---" << endl;
    cout << "Customer Name: " << customer.getName() << endl;
    cout << "Units Consumed: " << customer.getUnitsConsumed() << endl;
    cout << "Bill Amount: $" << billAmount << endl;

    return 0;
}

