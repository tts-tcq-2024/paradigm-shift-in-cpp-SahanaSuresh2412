#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <utility> // For std::pair
using namespace std;

// Struct to hold limits and tolerance
struct ParameterLimits {
    float lowerLimit;
    float upperLimit;
    bool warningEnabled;
};

// Warning messages
const string WARNING_DISCHARGE = "Warning: Approaching discharge";
const string WARNING_CHARGE_PEAK = "Warning: Approaching charge-peak";

// Function to check warnings based on limits
void checkWarning(float value, const ParameterLimits& limits, string& message) {
    float tolerance = (limits.upperLimit - limits.lowerLimit) * 0.05;

    if (limits.warningEnabled) {
        if (value >= limits.lowerLimit && value <= limits.lowerLimit + tolerance) {
            message = WARNING_DISCHARGE;
        } else if (value <= limits.upperLimit && value >= limits.upperLimit - tolerance) {
            message = WARNING_CHARGE_PEAK;
        }
    }
}

// Parameter check functions
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

// Helper function to perform all checks and update the message
bool performCheck(float temperature, float soc, float chargeRate, string &message,
                  const ParameterLimits& tempLimits, const ParameterLimits& socLimits, const ParameterLimits& chargeRateLimits) {
    bool temperatureOk = checkTemperature(temperature, message);
    bool socOk = checkSOC(soc, message);
    bool chargeRateOk = checkChargeRate(chargeRate, message);

    // Check warnings
    checkWarning(temperature, tempLimits, message);
    checkWarning(soc, socLimits, message);
    checkWarning(chargeRate, chargeRateLimits, message);

    return temperatureOk && socOk && chargeRateOk;
}

// Main function combining checks and I/O
bool batteryIsOk(float temperature, float soc, float chargeRate, string &message) {
    ParameterLimits tempLimits = {0, 45, true};
    ParameterLimits socLimits = {20, 80, true};
    ParameterLimits chargeRateLimits = {0, 0.8, false}; // Warnings disabled for charge rate

    bool allChecksOk = performCheck(temperature, soc, chargeRate, message, tempLimits, socLimits, chargeRateLimits);

    if (allChecksOk) {
        message = "Battery is OK.";
    }

    return allChecksOk;
}

// Test function
void testBatteryIsOk() {
    string message;

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

    // Test case for warnings
    assert(batteryIsOk(20, 20, 0.7, message) == true);
    assert(message == WARNING_DISCHARGE);

    assert(batteryIsOk(25, 76, 0.7, message) == true);
    assert(message == WARNING_CHARGE_PEAK);
}

int main() {
    testBatteryIsOk();
    cout << "All tests passed.\n";
    return 0;
}
