#include <iostream>
#include <cstring>
#include <cassert>

#define TEST_ENV
#include "../jsonParser.cpp"

void test_getJsonValue_edge_cases() {
    char value[FILE_NAME_LEN];
    const char* json = "{\"id\": 1, \"user\": {\"name\": \"Alice\"}}";

    value[0] = '\0';
    bool res1 = getJsonValue(json, "id", value, nullptr, 0);
    assert(res1 == true);
    assert(strcmp(value, "1") == 0);

    value[0] = '\0';
    bool res2 = getJsonValue(json, "id", value, nullptr, -5);
    assert(res2 == true);
    assert(strcmp(value, "1") == 0);

    value[0] = '\0';
    bool res3 = getJsonValue(json, "user", value, nullptr, 1);
    assert(res3 == true);
    assert(strcmp(value, "{\"name\": \"Alice\"}") == 0);

    value[0] = '\0';
    bool res4 = getJsonValue(json, "user", value, "", 1);
    assert(res4 == true);
    assert(strcmp(value, "{\"name\": \"Alice\"}") == 0);

    value[0] = '\0';
    bool res5 = getJsonValue(json, "user", value, "name", 1);
    assert(res5 == true);
    assert(strcmp(value, "Alice") == 0);

    value[0] = '\0';
    bool res6 = getJsonValue(json, "user", value, "age", 1);
    assert(res6 == false);
    assert(strcmp(value, "") == 0);

    value[0] = '\0';
    bool res7 = getJsonValue(json, "id", value, "name", 1);
    assert(res7 == true);
    assert(strcmp(value, "1") == 0);

    value[0] = '\0';
    bool res8 = getJsonValue("", "id", value, nullptr, 1);
    assert(res8 == false);

    value[0] = '\0';
    bool res9 = getJsonValue(json, "missing", value, nullptr, 1);
    assert(res9 == false);

    std::cout << "All getJsonValue tests passed!" << std::endl;
}

int main() {
    test_getJsonValue_edge_cases();
    return 0;
}
