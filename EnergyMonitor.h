// =============== EnergyMonitor.h ===============
#ifndef ENERGYMONITOR_H
#define ENERGYMONITOR_H
#include "Appliance.h"
#include <string>
using namespace std;

const int MAX_APPLIANCES = 30;

class EnergyMonitor {
private:
    Appliance appliances[MAX_APPLIANCES];
    int applianceCount;
    double tariff;  // cost per kWh
    
public:
    EnergyMonitor();
    
    // Appliance management
    bool addAppliance(const Appliance& app);
    void viewAllAppliances() const;
    int searchAppliance(string name) const;  // returns index or -1
    bool deleteAppliance(int index);
    
    // File operations
    bool loadFromFile(string filename);
    bool saveToFile(string filename) const;
    
    // Energy calculations
    double calculateTotalEnergy() const;
    void displayEnergySummary() const;
    
    // Billing
    bool setTariff(double t);
    double calculateTotalCost() const;
    void displayBillingSummary() const;
    bool saveBillingSummary(string filename) const;
    
    // Getters
    int getApplianceCount() const { return applianceCount; }
    const Appliance* getAppliances() const { return appliances; }
};
#endif