#include <iostream>
#include <string>
using namespace std;

// ===== SYSTEM FUNCTIONS (SIMULATION) =====

// Login function
bool login(string username, string password) {
    return (username == "Aakash" && password == "1234");
}

// Rating function
bool validateRating(int rating) {
    return (rating >= 1 && rating <= 5);
}

// Menu validation
bool validateMenu(int choice) {
    return (choice >= 1 && choice <= 4);
}

// ===== TESTING FUNCTION =====

void testCase(string testID, bool condition, string expected) {
    if (condition)
        cout << testID << " PASS\n";
    else
        cout << testID << " FAIL (Expected: " << expected << ")\n";
}

// ===== MAIN TEST RUNNER =====

int main() {

    cout << "=== BLACK BOX TESTING OUTPUT ===\n\n";

    // 🔹 LOGIN TESTS
    testCase("AL_EP_01", login("Aakash", "1234"), "Login Success");
    testCase("AL_EP_02", !login("Wrong", "1234"), "Login Fail");
    testCase("AL_EP_03", !login("Aakash", "wrong"), "Login Fail");

    cout << "\n";

    // 🔹 MENU TESTS
    testCase("MM_EP_01", validateMenu(1), "Valid");
    testCase("MM_EP_02", !validateMenu(0), "Invalid");
    testCase("MM_EP_03", !validateMenu(10), "Invalid");

    cout << "\n";

    // 🔹 RATING TESTS
    testCase("RT_EP_01", validateRating(3), "Accept");
    testCase("RT_EP_02", !validateRating(0), "Reject");
    testCase("RT_EP_03", !validateRating(6), "Reject");

    cout << "\n";

    // 🔹 BOUNDARY TESTS
    testCase("RT_BVA_01", validateRating(1), "Accept");
    testCase("RT_BVA_02", validateRating(5), "Accept");
    testCase("RT_BVA_03", !validateRating(0), "Reject");
    testCase("RT_BVA_04", !validateRating(6), "Reject");

    cout << "\n=== TESTING COMPLETE ===\n";

    return 0;
}