#include <assert.h>
#include <iostream>
using namespace std;
 
bool batteryIsOk(float temperature, float soc, float chargeRate) {
  bool temperatureOk = (temperature >= 0 && temperature <= 45);
  bool socOk = (soc >= 20 && soc <= 80);
  bool chargeRateOk = (chargeRate <= 0.8);

  if (!temperatureOk || !socOk || !chargeRateOk) {
    // if (!temperatureOk) cout << "Temperature out of range!\n";
    // if (!socOk) cout << "State of Charge out of range!\n";
    // if (!chargeRateOk) cout << "Charge Rate out of range!\n";
    return false;
  }
  return true;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}
