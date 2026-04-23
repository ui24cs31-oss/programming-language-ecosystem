#include <iostream>
using namespace std;

// =====================================================
// 🔹 STUB FUNCTIONS (LOW LEVEL)
// =====================================================

void stubSearch() {
    cout << "[STUB] Search Language Executed\n";
}

void stubDownload() {
    cout << "[STUB] Download Executed\n";
}

void stubRate() {
    cout << "[STUB] Rating Submitted\n";
}

void stubFeedback() {
    cout << "[STUB] Feedback Submitted\n";
}

void stubAdminAction() {
    cout << "[STUB] Admin Action Executed\n";
}

// =====================================================
// 🔹 TOP LEVEL FLOWS (REAL)
// =====================================================

bool adminLogin(string user, string pass) {
    return (user == "Aakash" && pass == "1234");
}

void adminFlow() {
    cout << "\n--- Admin Flow ---\n";
    stubAdminAction();
}

void developerFlow() {
    cout << "\n--- Developer Flow ---\n";
    cout << "[STUB] Submit Language\n";
}

void userFlow(int choice) {
    cout << "\n--- User Flow ---\n";

    switch(choice) {
        case 1: stubSearch(); break;
        case 2: stubDownload(); break;
        case 3: stubRate(); break;
        case 4: stubFeedback(); break;
        default: cout << "Invalid User Action\n";
    }
}

// =====================================================
// 🔥 TEST DRIVER (TOP-DOWN)
// =====================================================

int main() {

    cout << "=========== TOP-DOWN TESTING ===========\n";

    int failed = 0;

    // =================================================
    // TC1: Admin Login Success
    // =================================================
    if (!adminLogin("Aakash","1234")) {
        cout << "TC1 Failed\n";
        failed++;
    }

    // =================================================
    // TC2: Admin Login Failure
    // =================================================
    if (adminLogin("wrong","wrong")) {
        cout << "TC2 Failed\n";
        failed++;
    }

    // =================================================
    // TC3: Admin Flow Execution
    // =================================================
    cout << "\n[TC3] Admin Flow\n";
    adminFlow();

    // =================================================
    // TC4: Developer Flow
    // =================================================
    cout << "\n[TC4] Developer Flow\n";
    developerFlow();

    // =================================================
    // TC5: User Search
    // =================================================
    cout << "\n[TC5] User Search\n";
    userFlow(1);

    // =================================================
    // TC6: User Download
    // =================================================
    cout << "\n[TC6] User Download\n";
    userFlow(2);

    // =================================================
    // TC7: Invalid User Input
    // =================================================
    cout << "\n[TC7] Invalid Input\n";
    userFlow(99);

    // =================================================
    // RESULT
    // =================================================
    if (failed == 0)
        cout << "\n All Top-Down Tests Passed\n";
    else
        cout << "\n Tests Failed: " << failed << endl;

    return 0;
}
