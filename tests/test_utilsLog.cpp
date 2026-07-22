#include <iostream>
#include <cstdint>
#include <cassert>
#include <cstring>

// Define ESP partition types for testing
#define ESP_PARTITION_TYPE_APP 0x00
#define ESP_PARTITION_TYPE_DATA 0x01
#define ESP_PARTITION_SUBTYPE_APP_FACTORY 0x00
#define ESP_PARTITION_SUBTYPE_APP_OTA_0 0x10
#define ESP_PARTITION_SUBTYPE_APP_OTA_1 0x11
#define ESP_PARTITION_SUBTYPE_APP_OTA_2 0x12
#define ESP_PARTITION_SUBTYPE_APP_OTA_3 0x13
#define ESP_PARTITION_SUBTYPE_APP_OTA_4 0x14
#define ESP_PARTITION_SUBTYPE_APP_OTA_5 0x15
#define ESP_PARTITION_SUBTYPE_DATA_OTA 0x00
#define ESP_PARTITION_SUBTYPE_DATA_PHY 0x01
#define ESP_PARTITION_SUBTYPE_DATA_NVS 0x02
#define ESP_PARTITION_SUBTYPE_DATA_NVS_KEYS 0x04
#define ESP_PARTITION_SUBTYPE_DATA_SPIFFS 0x82
#define ESP_PARTITION_SUBTYPE_DATA_FAT 0x81

#define TEST_ENV
#include "../utilsLog.cpp"

void test_partitionTypeToStr() {
    assert(strcmp(partitionTypeToStr(ESP_PARTITION_TYPE_APP), "APP") == 0);
    assert(strcmp(partitionTypeToStr(ESP_PARTITION_TYPE_DATA), "DATA") == 0);
    assert(strcmp(partitionTypeToStr(0xFF), "UNKNOWN") == 0); // Unknown type
    assert(strcmp(partitionTypeToStr(0x02), "UNKNOWN") == 0); // Unknown type
    std::cout << "All partitionTypeToStr tests passed!" << std::endl;
}

int main() {
    test_partitionTypeToStr();
    return 0;
}
