#include <iostream>
#include <cstdint>
#include <cassert>

bool calcProgress(int progressVal, int totalVal, int percentReport, uint8_t &pcProgress) {
  uint8_t percentage = (progressVal * 100) / totalVal;
  if (percentage >= pcProgress + percentReport) {
    pcProgress = percentage;
    return true;
  } else return false;
}

void test_calcProgress() {
    uint8_t pcProgress = 0;

    // Test 1: Initial threshold met (0 -> 5)
    assert(calcProgress(5, 100, 5, pcProgress) == true);
    assert(pcProgress == 5);

    // Test 2: Threshold not met yet (5 -> 9)
    assert(calcProgress(9, 100, 5, pcProgress) == false);
    assert(pcProgress == 5);

    // Test 3: Threshold met (5 -> 10)
    assert(calcProgress(10, 100, 5, pcProgress) == true);
    assert(pcProgress == 10);

    // Test 4: Big jump, threshold met (10 -> 25)
    assert(calcProgress(25, 100, 5, pcProgress) == true);
    assert(pcProgress == 25);

    // Test 5: Exact 100%
    assert(calcProgress(100, 100, 5, pcProgress) == true);
    assert(pcProgress == 100);

    // Test 6: Another start, different report percentage
    pcProgress = 0;
    assert(calcProgress(20, 200, 10, pcProgress) == true); // 10%
    assert(pcProgress == 10);

    assert(calcProgress(39, 200, 10, pcProgress) == false); // 19%
    assert(pcProgress == 10);

    assert(calcProgress(40, 200, 10, pcProgress) == true); // 20%
    assert(pcProgress == 20);

    std::cout << "All calcProgress tests passed!" << std::endl;
}

int main() {
    test_calcProgress();
    return 0;
}
