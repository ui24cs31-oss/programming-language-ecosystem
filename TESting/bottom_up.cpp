#include <iostream>
#include <vector>
using namespace std;

// =====================================================
// 🔹 LOW LEVEL MODULE (REAL CODE FROM YOUR PROJECT)
// =====================================================

// Login module
bool checkCredentials(string username, string password) {
    return (username == "Aakash" && password == "1234");
}

// Rating module
bool validateRating(int rating) {
    return (rating >= 1 && rating <= 5);
}

// Download module
string downloadStatus(int progress) {
    if (progress == 0) return "QUEUED";
    else if (progress > 0 && progress < 100) return "DOWNLOADING";
    else if (progress == 100) return "COMPLETED";
    else return "INVALID";
}

// =====================================================
// 🔥 DRIVER (SIMULATES UPPER MODULES LIKE MENU + MAIN)
// =====================================================

int main() {

    cout << "=========== BOTTOM-UP TESTING (DRIVER) ===========\n";

    int failed = 0;

    // =================================================
    // 🔹 TC1: Simulating Login Module
    // =================================================
    if(!checkCredentials("Aakash", "1234")) {
        cout << "TC1 Failed\n";
        failed++;
    }

    // =================================================
    // 🔹 TC2: Invalid Login
    // =================================================
    if(checkCredentials("wrong", "wrong")) {
        cout << "TC2 Failed\n";
        failed++;
    }

    // =================================================
    // 🔹 TC3: Valid Rating
    // =================================================
    if(!validateRating(5)) {
        cout << "TC3 Failed\n";
        failed++;
    }

    // =================================================
    // 🔹 TC4: Invalid Rating
    // =================================================
    if(validateRating(0)) {
        cout << "TC4 Failed\n";
        failed++;
    }

    // =================================================
    // 🔹 TC5: Download Status Check
    // =================================================
    if(downloadStatus(100) != "COMPLETED") {
        cout << "TC5 Failed\n";
        failed++;
    }

    // =================================================
    // 🔹 TC6: Simulating Integration (Login → Rating → Download)
    // =================================================
    cout << "\n[Driver] Simulating system flow...\n";

    if(checkCredentials("Aakash","1234")) {
        if(validateRating(4)) {
            if(downloadStatus(100) == "COMPLETED") {
                cout << "[System] Flow executed successfully\n";
            } else {
                cout << "TC6 Failed (Download)\n";
                failed++;
            }
        } else {
            cout << "TC6 Failed (Rating)\n";
            failed++;
        }
    } else {
        cout << "TC6 Failed (Login)\n";
        failed++;
    }

    // =================================================
    // 🔹 FINAL RESULT
    // =================================================

    if(failed == 0)
        cout << "\n All Bottom-Up Tests Passed\n";
    else
        cout << "\n Tests Failed: " << failed << endl;

    return 0;
}