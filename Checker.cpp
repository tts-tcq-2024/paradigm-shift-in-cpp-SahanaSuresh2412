#include <iostream>
#include <cassert>
#include <string>

// Pure function to check temperature
bool checkTemperature(float temperature, std::string &message) {
    if (temperature < 0 || temperature > 45) {
        message = "Temperature out of range!";
        return false;
    }
    return true;
}

// Pure function to check state of charge (SOC)
bool checkSOC(float soc, std::string &message) {
    if (soc < 20 || soc > 80) {
        message = "State of Charge out of range!";
        return false;
    }
    return true;
}

// Pure function to check charge rate
bool checkChargeRate(float chargeRate, std::string &message) {
    if (chargeRate > 0.8) {
        message = "Charge Rate out of range!";
        return false;
    }
    return true;
}

// Function that uses pure functions and adds I/O
bool batteryIsOk(float temperature, float soc, float chargeRate, std::string &message) {
    if (!checkTemperature(temperature, message)) & (!checkSOC(soc, message)) & (!checkChargeRate(chargeRate, message)) 
    {
        return false;
    }
    message = "Battery is OK.";
    return true;
}

void testBatteryIsOk() {
    std::string message;

    assert(batteryIsOk(25, 70, 0.7, message) == true);
    assert(message == "Battery is OK.");

    assert(batteryIsOk(50, 85, 0, message) == false);
    assert(message == "Temperature out of range!");

    assert(batteryIsOk(25, 85, 0, message) == false);
    assert(message == "State of Charge out of range!");

    assert(batteryIsOk(25, 70, 0.9, message) == false);
    assert(message == "Charge Rate out of range!");
}

int main() {
    testBatteryIsOk();
    std::cout << "All tests passed.\n";
    return 0;
}
