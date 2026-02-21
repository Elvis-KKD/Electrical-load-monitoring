# Electrical-load-monitoring

# === README.md ===
# Electrical Load Monitoring and Billing Simulator

## Project Overview
A C++ console application to simulate electrical load monitoring and electricity billing for small facilities or households.

## Features
- Appliance Management: Add, view, search, and delete electrical appliances
- Energy Calculation: Compute daily energy consumption in kilowatt-hours (kWh)
- Billing Calculator: Generate electricity bills based on user-defined tariff
- Data Persistence: Save/load appliance data using text files
- Input Validation: Robust error handling for all user inputs

## Technical Specifications
- Language: C++
- Platform: Windows (offline)
- Maximum Appliances: 30
- Data Storage: CSV format (appliances.txt, billing_summary.txt)

## Installation & Compilation

### Prerequisites
- GCC compiler (MinGW for Windows) or any C++ compiler
- VS Code (recommended) or any text editor
- Git for version control

### Compilation
bash 
g++ main.cpp Appliance.cpp EnergyMonitor.cpp -o load_monitor.exe