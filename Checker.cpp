#include <iostream>
#include <cassert>
#include <string>

using namespace std;

// Pure function to check temperature
bool checkTemperature(float temperature, std::string &message) 
{
    if (temperature < 0) {
        message = "Temperature too low!";
        return false;
    } else if (temperature > 45) {
        message = "Temperature too high!";
        return false;
    }
    return true;
}

// Pure function to check state of charge (SOC)
bool checkSOC(float soc, std::string &message) 
{
    if (soc < 20) {
        message = "State of Charge too low!";
        return false;
    } else if (soc > 80) {
        message = "State of Charge too high!";
        return false;
    }
    return true;
}

// Pure function to check charge rate
bool checkChargeRate(float chargeRate, std::string &message) 
{
    if (chargeRate > 0.8) {
        message = "Charge Rate too high!";
        return false;
    }
    return true;
}

// Main function combining checks and I/O
bool batteryIsOk(float temperature, float soc, float chargeRate, std::string &message) 
{
    return (!checkTemperature(temperature, message) && !checkSOC(soc, message) && !checkChargeRate(chargeRate, message)); 
}

// Test function
void testBatteryIsOk() {
    std::string message = "Battery is OK.";

    // Test case where battery is OK
    assert(batteryIsOk(25, 70, 0.7, message) == true);
    assert(message == "Battery is OK.");

    // Test case where temperature is too high
    assert(batteryIsOk(50, 70, 0.7, message) == false);
    assert(message == "Temperature too high!");

    // Test case where SOC is too low
    assert(batteryIsOk(25, 10, 0.7, message) == false);
    assert(message == "State of Charge too low!");

    // Test case where charge rate is too high
    assert(batteryIsOk(25, 70, 0.9, message) == false);
    assert(message == "Charge Rate too high!");
}

int main() {
    testBatteryIsOk();
    cout << "All tests passed.\n";
    return 0;
}
