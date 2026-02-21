// =============== Appliance.h ===============
#ifndef APPLIANCE_H
#define APPLIANCE_H
#include <string>
using namespace std;

class Appliance {
private:
    string name;
    double powerRating;  // in watts
    double usageHours;   // hours per day
    
public:
    Appliance();
    Appliance(string n, double power, double hours);
    
    // Getters
    string getName() const;
    double getPowerRating() const;
    double getUsageHours() const;
    
    // Setters with validation
    bool setName(string n);
    bool setPowerRating(double power);
    bool setUsageHours(double hours);
    
    // Calculate daily energy consumption in kWh
    double calculateDailyEnergy() const;
    
    // Convert to CSV string for file storage
    string toCSV() const;
    
    // Create from CSV string
    static Appliance fromCSV(string csvLine);
};
#endif