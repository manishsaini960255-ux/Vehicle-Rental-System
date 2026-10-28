
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Base class
class Vehicle {
protected:
    int vehicleID;
    string model;
    double rentalRate;

public:
    // Constructor
    Vehicle(int id, string m, double rate) {
        vehicleID = id;
        model = m;
        rentalRate = rate;
    }

    // Virtual function
    virtual double calculateRental(int days) {
        return rentalRate * days;
    }

    // Display vehicle details
    virtual void displayDetails(int days) {
        cout << "\nVehicle ID: " << vehicleID;
        cout << "\nModel: " << model;
        cout << "\nRental Duration: " << days << " days";
        cout << "\nRental Rate: Rs. " << rentalRate << " per day";
        cout << "\nTotal Rental Charges: Rs. "
             << calculateRental(days) << endl;
    }

    virtual ~Vehicle() {}
};

// Derived class: Car
class Car : public Vehicle {
public:
    Car(int id, string m, double rate)
        : Vehicle(id, m, rate) {}

    // Function overriding
    double calculateRental(int days) override {
        double total = rentalRate * days;

        // Additional 10% charge for rentals longer than 7 days
        if (days > 7) {
            total = total + (total * 0.10);
        }

        return total;
    }

    void displayDetails(int days) override {
        cout << "\n--- CAR RENTAL DETAILS ---";
        Vehicle::displayDetails(days);

        if (days > 7) {
            cout << "Additional Charge: 10% for long-term rental"
                 << endl;
        }
    }
};

// Derived class: Bike
class Bike : public Vehicle {
public:
    Bike(int id, string m, double rate)
        : Vehicle(id, m, rate) {}

    // Function overriding
    double calculateRental(int days) override {
        double total = rentalRate * days;

        // 5% discount for rentals of 3 or more days
        if (days >= 3) {
            total = total - (total * 0.05);
        }

        return total;
    }

    void displayDetails(int days) override {
        cout << "\n--- BIKE RENTAL DETAILS ---";
        Vehicle::displayDetails(days);

        if (days >= 3) {
            cout << "Discount: 5% for rentals of 3 or more days"
                 << endl;
        }
    }
};

int main() {
    int choice, vehicleID, days;
    string model;
    double rate;

    cout << "===== VEHICLE RENTAL SYSTEM =====\n";
    cout << "1. Rent a Car\n";
    cout << "2. Rent a Bike\n";
    cout << "Enter your choice: ";

    if (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    cout << "Enter Vehicle ID: ";
    if (!(cin >> vehicleID) || vehicleID <= 0) {
        cout << "Invalid vehicle ID!" << endl;
        return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Vehicle Model: ";
    getline(cin, model);

    if (model.empty()) {
        cout << "Vehicle model cannot be empty!" << endl;
        return 1;
    }

    cout << "Enter Rental Rate per Day (Rs.): ";
    if (!(cin >> rate) || rate <= 0) {
        cout << "Rental rate must be greater than zero!" << endl;
        return 1;
    }

    cout << "Enter Rental Duration (days): ";
    if (!(cin >> days) || days <= 0) {
        cout << "Rental duration must be a positive number!"
             << endl;
        return 1;
    }

    Vehicle* vehicle = nullptr;

    if (choice == 1) {
        vehicle = new Car(vehicleID, model, rate);
    } else {
        vehicle = new Bike(vehicleID, model, rate);
    }

    vehicle->displayDetails(days);

    delete vehicle;

    cout << "\nThank you for using the Vehicle Rental System!"
         << endl;

    return 0;
}

