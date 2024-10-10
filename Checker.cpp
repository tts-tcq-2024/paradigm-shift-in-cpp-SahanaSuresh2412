#include <iostream>
#include <cassert>
#include <string>
using namespace std;
bool checkTemperature(float temperature, std::string &message) {
    if (temperature < 0) {
        message = "Temperature too low!";
        return false;
    } else if (temperature > 45) {
        message = "Temperature too high!";
        return false;
    }
    return true;
}
bool checkSOC(float soc, std::string &message) {
    if (soc < 20) {
        message = "State of Charge too low!";
        return false;
    } else if (soc > 80) {
        message = "State of Charge too high!";
        return false;
    }
    return true;
}
bool checkChargeRate(float chargeRate, std::string &message) {
    if (chargeRate > 0.8) {
        message = "Charge Rate too high!";
        return false;
    }
    return true;
}
bool performCheck(float temperature, float soc, float chargeRate, std::string &message) {
    bool temperatureOk = checkTemperature(temperature, message);
    bool socOk = checkSOC(soc, message);
    bool chargeRateOk = checkChargeRate(chargeRate, message);
    return temperatureOk && socOk && chargeRateOk;
}
bool batteryIsOk(float temperature, float soc, float chargeRate, std::string &message) {
    bool allChecksOk = performCheck(temperature, soc, chargeRate, message);
    if (allChecksOk) {
        message = "Battery is OK.";
    }
    return allChecksOk;
}
void testBatteryIsOk() {
    std::string message;
    // Test case where battery is OK
    assert(batteryIsOk(25, 70, 0.7, message) == true);
    assert(message == "Battery is OK.");
    // Test case where temperature is too low
    assert(batteryIsOk(-1, 70, 0.7, message) == false);
    assert(message == "Temperature too low!");
    // Test case where temperature is too high
    assert(batteryIsOk(50, 70, 0.7, message) == false);
    assert(message == "Temperature too high!");
    // Test case where SOC is too low
    assert(batteryIsOk(25, 10, 0.7, message) == false);
    assert(message == "State of Charge too low!");
    // Test case where SOC is too high
    assert(batteryIsOk(25, 100, 0.7, message) == false);
    assert(message == "State of Charge too high!");
    // Test case where charge rate is too high
    assert(batteryIsOk(25, 70, 0.9, message) == false);
    assert(message == "Charge Rate too high!");
}
int main() {
    testBatteryIsOk();
    cout << "All tests passed.\n";
    return 0;
}
has context menu
