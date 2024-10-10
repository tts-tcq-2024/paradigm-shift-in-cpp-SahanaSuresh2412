#include <iostream>
#include <cassert>
#include <string>
using namespace std;

void checkForWarning(float value, const float lowerLimit, const float upperLimit, std::string &warning, const std::string &type) {
    const float tolerance = (upperLimit - lowerLimit) * 0.05; // 5% of the range
    if (value >= lowerLimit && value < lowerLimit + tolerance) {
        warning += "Warning: Approaching low " + type + " limit! ";
    } else if (value > upperLimit - tolerance && value <= upperLimit) {
        warning += "Warning: Approaching high " + type + " limit! ";
    }
}

bool isTemperatureWithinRange(float temperature, std::string &message, std::string &warning) {
    const float lowerLimit = 0.0;
    const float upperLimit = 45.0;
    
    if (temperature < lowerLimit) 
    {
        message = "Temperature too low!";
        return false;
    } 
    else if (temperature > upperLimit) 
    {
        message = "Temperature too high!";
        return false;
    }
    else
    {
        checkForWarning(temperature, lowerLimit, upperLimit, warning, "temperature");
        return true;
    }
}

bool isSOCWithinRange(float soc, std::string &message, std::string &warning) {
    const float lowerLimit = 20.0;
    const float upperLimit = 80.0;
    
    if (soc < lowerLimit) 
    {
        message = "State of Charge too low!";
        return false;
    } 
    else if (soc > upperLimit) 
    {
        message = "State of Charge too high!";
        return false;
    }
    else
    {
        checkForWarning(soc, lowerLimit, upperLimit, warning, "State of Charge");
        return true;
    }
}
bool isChargeRateOK(float chargeRate, std::string &message, std::string &warning) {
    const float upperLimit = 0.8;
    const float tolerance = upperLimit * 0.05; // 5% of the upper limit

    if (chargeRate > upperLimit) 
    {
        message = "Charge Rate too high!";
        return false;
    } 
    else if (chargeRate >= upperLimit - tolerance) 
    {
        warning += "Warning: Approaching high charge rate limit!";
    }
    return true;
}
 
bool isTemperatureAndSOCWithinRange(float temperature, float soc, std::string &message, std::string &warning) {
	if(isTemperatureWithinRange(temperature, message, warning) && isSOCWithinRange(soc, message, warning)) 
	{
		return true;
	}
	else 
	{
		return false;
	}
 
}
bool performCheck(float temperature, float soc, float chargeRate, std::string &message, std::string &warning) {
    if(isTemperatureAndSOCWithinRange(temperature, soc, message, warning) && isChargeRateOK(chargeRate, message, warning)) 
    {
		return true;
	}
	else 
	{
		return false;
	}
}
bool batteryIsOk(float temperature, float soc, float chargeRate, std::string &message, std::string &warning) {
    bool allChecksOk = performCheck(temperature, soc, chargeRate, message, warning);
    if (allChecksOk) 
    {
        message = "Battery is OK.";
		return true;
    }
	else 
	{
		return false;
	}
}
void testBatteryChecks() {
    std::string message;
    std::string warning;

    // Test case: Battery is OK
    assert(batteryIsOk(25, 50, 0.7, message, warning) == true);
    assert(message == "Battery is OK.");
    assert(warning.empty());

    // Test case: Temperature too low
    assert(batteryIsOk(-1, 50, 0.7, message, warning) == false);
    assert(message == "Temperature too low!");
    assert(warning.empty());

    // Test case: Temperature too high
    assert(batteryIsOk(50, 50, 0.7, message, warning) == false);
    assert(message == "Temperature too high!");
    assert(warning.empty());

    // Test case: SOC too low
    assert(batteryIsOk(25, 10, 0.7, message, warning) == false);
    assert(message == "State of Charge too low!");
    assert(warning.empty());

    // Test case: SOC too high
    assert(batteryIsOk(25, 90, 0.7, message, warning) == false);
    assert(message == "State of Charge too high!");
    assert(warning.empty());

    // Test case: Charge rate too high
    assert(batteryIsOk(25, 50, 0.9, message, warning) == false);
    assert(message == "Charge Rate too high!");
    assert(warning.empty());

    // Test case: Approaching low temperature limit (warning)
    warning.clear(); // Clear warning for this test
    assert(batteryIsOk(0.5, 50, 0.7, message, warning) == true);
    assert(message == "Battery is OK.");
    assert(warning == "Warning: Approaching low temperature limit! ");

    // Test case: Approaching high temperature limit (warning)
    warning.clear(); // Clear warning for this test
    assert(batteryIsOk(44.5, 50, 0.7, message, warning) == true);
    assert(message == "Battery is OK.");
    assert(warning == "Warning: Approaching high temperature limit! ");

    // Test case: Approaching low SOC limit (warning)
    warning.clear(); // Clear warning for this test
    assert(batteryIsOk(25, 20.5, 0.7, message, warning) == true);
    assert(message == "Battery is OK.");
    assert(warning == "Warning: Approaching low State of Charge limit! ");

    // Test case: Approaching high SOC limit (warning)
    warning.clear(); // Clear warning for this test
    assert(batteryIsOk(25, 79.5, 0.7, message, warning) == true);
    assert(message == "Battery is OK.");
    assert(warning == "Warning: Approaching high State of Charge limit! ");

    // Test case: Approaching high charge rate limit (warning)
    warning.clear(); // Clear warning for this test
    assert(batteryIsOk(25, 50, 0.76, message, warning) == true);
    assert(message == "Battery is OK.");
    assert(warning == "Warning: Approaching high charge rate limit!");
    
    warning.clear(); // Clear warning for this test
    assert(batteryIsOk(0.5, 20.5, 0.76, message, warning) == true);
    assert(message == "Battery is OK.");
    assert(warning == "Warning: Approaching low temperature limit! Warning: Approaching low State of Charge limit! Warning: Approaching high charge rate limit!");
}

int main() {
    testBatteryChecks();
    cout << "All tests passed.\n";
    return 0;
}
