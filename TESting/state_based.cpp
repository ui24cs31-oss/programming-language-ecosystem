#include <iostream>
using namespace std;

// =====================================================
// 🔹 STATES (as per PPT style)
// =====================================================

enum State {
    IDLE,
    ENTERING,
    AUTHENTICATED,
    RETRY,
    LOCKED
};

// =====================================================
// 🔹 STATE MACHINE CLASS
// =====================================================

class LoginSystem {
private:
    State currentState;
    int attempts;

public:
    LoginSystem() {
        currentState = IDLE;
        attempts = 0;
    }

    State getState() {
        return currentState;
    }

    void insertUser() {
        if (currentState == IDLE) {
            currentState = ENTERING;
        }
    }

    void enterPassword(bool correct) {
        if (currentState == ENTERING || currentState == RETRY) {

            if (correct) {
                currentState = AUTHENTICATED;
            } else {
                attempts++;

                if (attempts >= 3) {
                    currentState = LOCKED;
                } else {
                    currentState = RETRY;
                }
            }
        }
    }
};

// =====================================================
// 🔥 TEST DRIVER (STATE BASED TESTING)
// =====================================================

int main() {

    cout << "=========== STATE BASED TESTING ===========\n";

    int failed = 0;

    // =================================================
    // 🔹 TC1: Successful Login
    // =================================================
    LoginSystem s1;
    s1.insertUser();
    s1.enterPassword(true);

    if (s1.getState() != AUTHENTICATED) {
        cout << "TC1 Failed\n";
        failed++;
    }

    // =================================================
    // 🔹 TC2: One Wrong Attempt
    // =================================================
    LoginSystem s2;
    s2.insertUser();
    s2.enterPassword(false);

    if (s2.getState() != RETRY) {
        cout << "TC2 Failed\n";
        failed++;
    }

    // =================================================
    // 🔹 TC3: Three Wrong Attempts → LOCKED
    // =================================================
    LoginSystem s3;
    s3.insertUser();
    s3.enterPassword(false);
    s3.enterPassword(false);
    s3.enterPassword(false);

    if (s3.getState() != LOCKED) {
        cout << "TC3 Failed\n";
        failed++;
    }

    // =================================================
    // 🔹 TC4: Correct After Retry
    // =================================================
    LoginSystem s4;
    s4.insertUser();
    s4.enterPassword(false);
    s4.enterPassword(true);

    if (s4.getState() != AUTHENTICATED) {
        cout << "TC4 Failed\n";
        failed++;
    }

    // =================================================
    // 🔹 TC5: Locked State Behavior
    // =================================================
    LoginSystem s5;
    s5.insertUser();
    s5.enterPassword(false);
    s5.enterPassword(false);
    s5.enterPassword(false);
    s5.enterPassword(true); // should NOT change state

    if (s5.getState() != LOCKED) {
        cout << "TC5 Failed\n";
        failed++;
    }

    // =================================================
    // 🔹 FINAL RESULT
    // =================================================
    if (failed == 0)
        cout << "\n All State-Based Tests Passed\n";
    else
        cout << "\n Some Tests Failed: " << failed << endl;

    return 0;
}