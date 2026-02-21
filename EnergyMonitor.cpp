// =============== EnergyMonitor.cpp ===============
#include "EnergyMonitor.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cctype>
using namespace std;

EnergyMonitor::EnergyMonitor() : applianceCount(0), tariff(0.0) {}

bool EnergyMonitor::addAppliance(const Appliance& app) {
    if (applianceCount >= MAX_APPLIANCES) return false;
    appliances[applianceCount++] = app;
    return true;
}

void EnergyMonitor::viewAllAppliances() const {
    if (applianceCount == 0) {
        cout << "\nNo appliances registered.\n";
        return;
    }
    
    cout << "\n" << string(60, '=') << endl;
    cout << left << setw(5) << "S/N" 
         << setw(20) << "Appliance Name" 
         << setw(15) << "Power (W)" 
         << setw(15) << "Hours/Day" 
         << "Energy (kWh)" << endl;
    cout << string(60, '-') << endl;
    
    for (int i = 0; i < applianceCount; i++) {
        cout << left << setw(5) << (i + 1)
             << setw(20) << appliances[i].getName()
             << setw(15) << fixed << setprecision(1) << appliances[i].getPowerRating()
             << setw(15) << fixed << setprecision(1) << appliances[i].getUsageHours()
             << fixed << setprecision(2) << appliances[i].calculateDailyEnergy() << endl;
    }
    cout << string(60, '=') << endl;
}

int EnergyMonitor::searchAppliance(string name) const {
    // Convert search name to lowercase for case-insensitive comparison
    string searchName = name;
    transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
    
    for (int i = 0; i < applianceCount; i++) {
        string currentName = appliances[i].getName();
        transform(currentName.begin(), currentName.end(), currentName.begin(), ::tolower);
        if (currentName == searchName) {
            return i;
        }
    }
    return -1;
}

bool EnergyMonitor::deleteAppliance(int index) {
    if (index < 0 || index >= applianceCount) return false;
    
    // Shift all elements after index left by one
    for (int i = index; i < applianceCount - 1; i++) {
        appliances[i] = appliances[i + 1];
    }
    applianceCount--;
    return true;
}

bool EnergyMonitor::loadFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    
    applianceCount = 0;
    string line;
    
    while (getline(file, line) && applianceCount < MAX_APPLIANCES) {
        if (!line.empty()) {
            appliances[applianceCount++] = Appliance::fromCSV(line);
        }
    }
    
    file.close();
    return true;
}

bool EnergyMonitor::saveToFile(string filename) const {
    ofstream file(filename);
    if (!file.is_open()) return false;
    
    for (int i = 0; i < applianceCount; i++) {
        file << appliances[i].toCSV() << endl;
    }
    
    file.close();
    return true;
}

double EnergyMonitor::calculateTotalEnergy() const {
    double total = 0;
    for (int i = 0; i < applianceCount; i++) {
        total += appliances[i].calculateDailyEnergy();
    }
    return total;
}

void EnergyMonitor::displayEnergySummary() const {
    cout << "\n" << string(40, '=') << endl;
    cout << "ENERGY CONSUMPTION SUMMARY" << endl;
    cout << string(40, '=') << endl;
    
    viewAllAppliances();
    
    cout << "\nTotal Daily Energy Consumption: " 
         << fixed << setprecision(2) << calculateTotalEnergy() << " kWh" << endl;
    cout << "Total Monthly Energy (30 days): " 
         << fixed << setprecision(2) << calculateTotalEnergy() * 30 << " kWh" << endl;
}

bool EnergyMonitor::setTariff(double t) {
    if (t <= 0) return false;
    tariff = t;
    return true;
}

double EnergyMonitor::calculateTotalCost() const {
    return calculateTotalEnergy() * tariff;
}

void EnergyMonitor::displayBillingSummary() const {
    cout << "\n" << string(50, '=') << endl;
    cout << "ELECTRICITY BILLING SUMMARY" << endl;
    cout << string(50, '=') << endl;
    
    cout << "Tariff Rate: GHS " << fixed << setprecision(2) << tariff << " per kWh" << endl;
    cout << string(50, '-') << endl;
    
    cout << left << setw(20) << "Appliance" 
         << setw(15) << "Energy (kWh)" 
         << "Cost (GHS)" << endl;
    cout << string(50, '-') << endl;
    
    for (int i = 0; i < applianceCount; i++) {
        double energy = appliances[i].calculateDailyEnergy();
        cout << left << setw(20) << appliances[i].getName()
             << setw(15) << fixed << setprecision(2) << energy
             << fixed << setprecision(2) << energy * tariff << endl;
    }
    
    cout << string(50, '-') << endl;
    cout << left << setw(20) << "TOTAL" 
         << setw(15) << fixed << setprecision(2) << calculateTotalEnergy()
         << fixed << setprecision(2) << calculateTotalCost() << endl;
    cout << string(50, '=') << endl;
    
    cout << "\nMonthly Estimate (30 days): GHS " 
         << fixed << setprecision(2) << calculateTotalCost() * 30 << endl;
}

bool EnergyMonitor::saveBillingSummary(string filename) const {
    ofstream file(filename);
    if (!file.is_open()) return false;

    //Get current time using ctime
    time_t now = time(0);
    char* dt = ctime(&now);
    //file << "Generated on: " << dt;
    
    file << string(50, '=') << endl;
    file << "ELECTRICITY BILLING SUMMARY" << endl;
    file << "Generated on: " << dt;
    file << string(50, '=') << endl;
    
    file << "Tariff Rate: GHS " << fixed << setprecision(2) << tariff << " per kWh" << endl;
    file << string(50, '-') << endl;
    
    file << left << setw(20) << "Appliance" 
         << setw(15) << "Energy (kWh)" 
         << "Cost (GHS)" << endl;
    file << string(50, '-') << endl;
    
    for (int i = 0; i < applianceCount; i++) {
        double energy = appliances[i].calculateDailyEnergy();
        file << left << setw(20) << appliances[i].getName()
             << setw(15) << fixed << setprecision(2) << energy
             << fixed << setprecision(2) << energy * tariff << endl;
    }
    
    file << string(50, '-') << endl;
    file << left << setw(20) << "TOTAL" 
         << setw(15) << fixed << setprecision(2) << calculateTotalEnergy()
         << fixed << setprecision(2) << calculateTotalCost() << endl;
    file << string(50, '=') << endl;
    
    file << "\nMonthly Estimate (30 days): GHS " 
         << fixed << setprecision(2) << calculateTotalCost() * 30 << endl;
    
    file.close();
    return true;
}