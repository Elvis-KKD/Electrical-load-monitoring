// =============== Appliance.cpp ===============
#include "Appliance.h"
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

Appliance::Appliance() : name(""), powerRating(0), usageHours(0) {}

Appliance::Appliance(string n, double power, double hours) {
    setName(n);
    setPowerRating(power);
    setUsageHours(hours);
}

string Appliance::getName() const { return name; }

double Appliance::getPowerRating() const { return powerRating; }

double Appliance::getUsageHours() const { return usageHours; }

bool Appliance::setName(string n) {
    if (n.empty()) return false;
    name = n;
    return true;
}

bool Appliance::setPowerRating(double power) {
    if (power <= 0) return false;
    powerRating = power;
    return true;
}

bool Appliance::setUsageHours(double hours) {
    if (hours < 0 || hours > 24) return false;
    usageHours = hours;
    return true;
}

double Appliance::calculateDailyEnergy() const {
    // Convert watts to kW and multiply by hours
    return (powerRating / 1000.0) * usageHours;
}

string Appliance::toCSV() const {
    stringstream ss;
    ss << name << "," << powerRating << "," << usageHours;
    return ss.str();
}

Appliance Appliance::fromCSV(string csvLine) {
    stringstream ss(csvLine);
    string name, powerStr, hoursStr;
    
    getline(ss, name, ',');
    getline(ss, powerStr, ',');
    getline(ss, hoursStr, ',');
    
    double power = stod(powerStr);
    double hours = stod(hoursStr);
    
    return Appliance(name, power, hours);
}

