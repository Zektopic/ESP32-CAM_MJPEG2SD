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

#include <cstdarg>

// Mock logging macro for testing formatHex
char lastLog[1024] = {0};

void mock_log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(lastLog, sizeof(lastLog), fmt, args);
    va_end(args);
    // std::cout << "MOCK LOG: " << lastLog << std::endl;
}
#define LOG_INF(...) mock_log(__VA_ARGS__)

#include "../utilsLog.cpp"

void test_partitionTypeToStr() {
    assert(strcmp(partitionTypeToStr(ESP_PARTITION_TYPE_APP), "APP") == 0);
    assert(strcmp(partitionTypeToStr(ESP_PARTITION_TYPE_DATA), "DATA") == 0);
    assert(strcmp(partitionTypeToStr(0xFF), "UNKNOWN") == 0); // Unknown type
    assert(strcmp(partitionTypeToStr(0x02), "UNKNOWN") == 0); // Unknown type
    std::cout << "All partitionTypeToStr tests passed!" << std::endl;
}


void formatHex(const char* inData, size_t inLen);
void test_formatHex() {
    // Test 1: Typical byte array
    const char data1[] = {(char)0xDE, (char)0xAD, (char)0xBE, (char)0xEF};
    formatHex(data1, sizeof(data1));
    assert(strcmp(lastLog, "Hex: de ad be ef ") == 0);

    // Test 2: Single byte
    const char data2[] = {0x00};
    formatHex(data2, sizeof(data2));
    assert(strcmp(lastLog, "Hex: 00 ") == 0);

    // Test 3: Empty data
    lastLog[0] = '\0'; // Reset log
    formatHex(nullptr, 0);
    assert(strcmp(lastLog, "Hex: ") == 0);

    // Test 4: Extended bytes that might cause sign extension if not handled properly
    const char data4[] = {0x7F, (char)0x80, (char)0xFF};
    formatHex(data4, sizeof(data4));
    assert(strcmp(lastLog, "Hex: 7f 80 ff ") == 0);

    std::cout << "All formatHex tests passed!" << std::endl;
}

int main() {
    test_formatHex();
    test_partitionTypeToStr();
    return 0;
}
