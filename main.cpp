// =============== main.cpp ===============
#include <iostream>
#include <limits>
#include <cctype>
#include "EnergyMonitor.h"
using namespace std;

// Function prototypes
void displayMainMenu();
void handleAddAppliance(EnergyMonitor& monitor);
void handleSearchAppliance(const EnergyMonitor& monitor);
void handleDeleteAppliance(EnergyMonitor& monitor);
void handleBilling(EnergyMonitor& monitor);
double getValidDouble(string prompt, double min, double max);
int getValidInt(string prompt, int min, int max);
string getValidString(string prompt);
void clearInputBuffer();

int main() {
    EnergyMonitor monitor;
    
    // Try to load existing data
    if (monitor.loadFromFile("appliances.txt")) {
        cout << "\n✓ Data loaded successfully from appliances.txt\n";
    } else {
        cout << "\n! No existing data found. Starting fresh.\n";
    }
    
    int choice;
    do {
        displayMainMenu();
        choice = getValidInt("Enter your choice (0-7): ", 0, 7);
        
        switch(choice) {
            case 1:
                handleAddAppliance(monitor);
                break;
                
            case 2:
                monitor.viewAllAppliances();
                break;
                
            case 3:
                handleSearchAppliance(monitor);
                break;
                
            case 4:
                handleDeleteAppliance(monitor);
                break;
                
            case 5:
                monitor.displayEnergySummary();
                break;
                
            case 6:
                handleBilling(monitor);
                break;
                
            case 7:
                if (monitor.saveToFile("appliances.txt")) {
                    cout << "\n✓ Data saved successfully to appliances.txt\n";
                } else {
                    cout << "\n✗ Error saving data!\n";
                }
                break;
                
            case 0:
                cout << "\nSaving data before exit...\n";
                if (monitor.saveToFile("appliances.txt")) {
                    cout << "✓ Data saved. Goodbye!\n";
                } else {
                    cout << "✗ Error saving data!\n";
                }
                break;
        }
        
        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}

void displayMainMenu() {
    cout << "\n" << string(50, '=') << endl;
    cout << "   ELECTRICAL LOAD MONITORING SYSTEM" << endl;
    cout << string(50, '=') << endl;
    cout << "1. Add New Appliance" << endl;
    cout << "2. View All Appliances" << endl;
    cout << "3. Search Appliance" << endl;
    cout << "4. Delete Appliance" << endl;
    cout << "5. Energy Consumption Summary" << endl;
    cout << "6. Billing Calculator" << endl;
    cout << "7. Save Data to File" << endl;
    cout << "0. Exit" << endl;
    cout << string(50, '-') << endl;
}

void handleAddAppliance(EnergyMonitor& monitor) {
    if (monitor.getApplianceCount() >= MAX_APPLIANCES) {
        cout << "\n✗ Cannot add more appliances. Maximum limit (30) reached.\n";
        return;
    }
    
    cout << "\n--- ADD NEW APPLIANCE ---\n";
    
    string name = getValidString("Enter appliance name: ");
    
    cout << "Enter power rating (watts, >0): ";
    double power = getValidDouble("", 0.1, 10000);
    
    cout << "Enter daily usage hours (0-24): ";
    double hours = getValidDouble("", 0, 24);
    
    Appliance app(name, power, hours);
    
    if (monitor.addAppliance(app)) {
        cout << "\n✓ Appliance added successfully!\n";
    } else {
        cout << "\n✗ Failed to add appliance.\n";
    }
}

void handleSearchAppliance(const EnergyMonitor& monitor) {

    if (monitor.getApplianceCount() == 0) {
        cout << "\nNo appliances to search.\n";
        return;
    }
    
    string name = getValidString("Enter appliance name to search: ");
    int index = monitor.searchAppliance(name);
    
    if (index != -1) {
        const Appliance* apps = monitor.getAppliances();
        cout << "\n✓ Appliance found:\n";
        cout << "Name: " << apps[index].getName() << endl;
        cout << "Power Rating: " << apps[index].getPowerRating() << " W" << endl;
        cout << "Daily Usage: " << apps[index].getUsageHours() << " hours" << endl;
        cout << "Daily Energy: " << apps[index].calculateDailyEnergy() << " kWh" << endl;
    } else {
        cout << "\n✗ Appliance not found.\n";
    }
}

void handleDeleteAppliance(EnergyMonitor& monitor) {
    if (monitor.getApplianceCount() == 0) {
        cout << "\nNo appliances to delete.\n";
        return;
    }
    
    monitor.viewAllAppliances();
    
    int index = getValidInt("Enter the S/N of appliance to delete (0 to cancel): ", 0, monitor.getApplianceCount());
    
    if (index == 0) {
        cout << "\nDeletion cancelled.\n";
        return;
    }
    
    if (monitor.deleteAppliance(index - 1)) {
        cout << "\n✓ Appliance deleted successfully!\n";
    } else {
        cout << "\n✗ Failed to delete appliance.\n";
    }
}

void handleBilling(EnergyMonitor& monitor) {
    if (monitor.getApplianceCount() == 0) {
        cout << "\nNo appliances registered. Please add appliances first.\n";
        return;
    }
    
    cout << "\n--- BILLING CALCULATOR ---\n";
    cout << "Enter electricity tariff (GHS per kWh, >0): ";
    double tariff = getValidDouble("", 0.01, 100);
    
    if (monitor.setTariff(tariff)) {
        monitor.displayBillingSummary();
        
        char save;
        cout << "\nSave billing summary to file? (y/n): ";
        cin >> save;
        clearInputBuffer();
        
        if (tolower(save) == 'y') {
            if (monitor.saveBillingSummary("billing_summary.txt")) {
                cout << "✓ Billing summary saved to billing_summary.txt\n";
            } else {
                cout << "✗ Error saving billing summary!\n";
            }
        }
    } else {
        cout << "\n✗ Invalid tariff value.\n";
    }
}

// Utility functions for input validation
double getValidDouble(string prompt, double min, double max) {
    double value;
    bool valid;
    
    do {
        if (!prompt.empty()) cout << prompt;
        cin >> value;
        valid = !cin.fail() && value >= min && value <= max;
        
        if (!valid) {
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
            cin.clear();
            clearInputBuffer();
        }
    } while (!valid);
    
    clearInputBuffer();
    return value;
}

int getValidInt(string prompt, int min, int max) {
    int value;
    bool valid;
    
    do {
        cout << prompt;
        cin >> value;
        valid = !cin.fail() && value >= min && value <= max;
        
        if (!valid) {
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            cin.clear();
            clearInputBuffer();
        }
    } while (!valid);
    
    clearInputBuffer();
    return value;
}

string getValidString(string prompt) {
    string value;
    bool valid;
    
    do {
        cout << prompt;
        getline(cin, value);
        valid = !value.empty();
        
        if (!valid) {
            cout << "Input cannot be empty. Please try again.\n";
        }
    } while (!valid);
    
    return value;
}

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}