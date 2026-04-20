#include <iostream>
#include <vector>
#include <string>
using namespace std;

// =====================================================
// 🔹 STUBS (Lower-level modules replaced)
// =====================================================

void voterMenu() {
    cout << "[STUB] Voter Menu Called\n";
}

void candidateMenu() {
    cout << "[STUB] Candidate Menu Called\n";
}

void adminMenu() {
    cout << "[STUB] Admin Menu Called\n";
}

void officerMenu() {
    cout << "[STUB] Officer Menu Called\n";
}

void evmMenu() {
    cout << "[STUB] EVM Menu Called\n";
}

// =====================================================
// 🔹 AUTHENTICATION (Top-level logic)
// =====================================================

bool authenticate(string username, string password) {
    vector<pair<string,string>> admins = {
        {"parth","1234"},
        {"prajyesh","5678"}
    };

    for(auto &a : admins) {
        if(username == a.first && password == a.second)
            return true;
    }
    return false;
}

// =====================================================
// 🔹 MAIN SYSTEM (TOP LEVEL MODULE)
// =====================================================

void mainSystem(int choice) {
    switch(choice) {
        case 1: voterMenu(); break;
        case 2: candidateMenu(); break;
        case 3: adminMenu(); break;
        case 4: officerMenu(); break;
        case 5: evmMenu(); break;
        default: cout << "Invalid Choice\n";
    }
}

// =====================================================
// 🔥 TESTS (Executes test cases)
// =====================================================

int main() {

    int failed = 0;

    cout << "=========== TOP-DOWN TESTING ===========\n";

    // =================================================
    // 🔹 TEST 1: Authentication Success
    // =================================================
    if(authenticate("parth","1234") != true) {
        cout << "TC1 Failed: Valid login not working\n";
        failed++;
    }

    // =================================================
    // 🔹 TEST 2: Authentication Failure
    // =================================================
    if(authenticate("wrong","wrong") != false) {
        cout << "TC2 Failed: Invalid login accepted\n";
        failed++;
    }

    // =================================================
    // 🔹 TEST 3: Menu → Voter Module
    // =================================================
    cout << "\n[TC3] Expect: Voter Stub\n";
    mainSystem(1);

    // =================================================
    // 🔹 TEST 4: Menu → Candidate Module
    // =================================================
    cout << "\n[TC4] Expect: Candidate Stub\n";
    mainSystem(2);

    // =================================================
    // 🔹 TEST 5: Menu → Admin Module
    // =================================================
    cout << "\n[TC5] Expect: Admin Stub\n";
    mainSystem(3);

    // =================================================
    // 🔹 TEST 6: Menu → Officer Module
    // =================================================
    cout << "\n[TC6] Expect: Officer Stub\n";
    mainSystem(4);

    // =================================================
    // 🔹 TEST 7: Invalid Input
    // =================================================
    cout << "\n[TC7] Expect: Invalid Choice\n";
    mainSystem(99);

    // =================================================
    // 🔹 FINAL RESULT
    // =================================================
    if(failed == 0)
        cout << "\n All Top-Down Tests Passed\n";
    else
        cout << "\n Some Tests Failed: " << failed << endl;

    return 0;
}