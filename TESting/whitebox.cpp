#include <gtest/gtest.h>
#include <vector>
#include <string>
using namespace std;

// ================= HELPER FUNCTIONS =================

// Login logic (from your system)
bool checkCredentials(string username, string password) {
    if (username == "Aakash") {
        if (password == "1234")
            return true;
        else
            return false;
    }
    return false;
}

// Rating validation
bool validateRating(int rating) {
    if (rating < 1) return false;
    if (rating > 5) return false;
    return true;
}

// Download state logic
string downloadStatus(int progress) {
    if (progress == 0) return "QUEUED";
    else if (progress > 0 && progress < 100) return "DOWNLOADING";
    else if (progress == 100) return "COMPLETED";
    else return "INVALID";
}

// ===================================================
// 🔥 1. STATEMENT COVERAGE
// ===================================================

TEST(StatementCoverage, LoginValid) {
    EXPECT_TRUE(checkCredentials("Aakash", "1234"));
}

TEST(StatementCoverage, LoginInvalid) {
    EXPECT_FALSE(checkCredentials("Wrong", "Wrong"));
}

TEST(StatementCoverage, RatingValid) {
    EXPECT_TRUE(validateRating(3));
}

TEST(StatementCoverage, RatingInvalid) {
    EXPECT_FALSE(validateRating(0));
}

// ===================================================
// 🔥 2. BRANCH / DECISION COVERAGE
// ===================================================

TEST(BranchCoverage, CorrectUsernameWrongPassword) {
    EXPECT_FALSE(checkCredentials("Aakash", "wrong"));
}

TEST(BranchCoverage, WrongUsername) {
    EXPECT_FALSE(checkCredentials("Unknown", "1234"));
}

TEST(BranchCoverage, CorrectBoth) {
    EXPECT_TRUE(checkCredentials("Aakash", "1234"));
}

TEST(BranchCoverage, RatingLowerBoundary) {
    EXPECT_FALSE(validateRating(0));
}

TEST(BranchCoverage, RatingUpperBoundary) {
    EXPECT_FALSE(validateRating(6));
}

// ===================================================
// 🔥 3. PATH COVERAGE
// ===================================================

bool loginSimulation(vector<pair<string,string>> attempts) {
    int tries = 3;
    for (auto &a : attempts) {
        if (tries-- == 0) break;
        if (checkCredentials(a.first, a.second)) {
            return true;
        }
    }
    return false;
}

TEST(PathCoverage, SuccessFirstAttempt) {
    vector<pair<string,string>> attempts = {
        {"Aakash","1234"}
    };
    EXPECT_TRUE(loginSimulation(attempts));
}

TEST(PathCoverage, SuccessSecondAttempt) {
    vector<pair<string,string>> attempts = {
        {"wrong","wrong"},
        {"Aakash","1234"}
    };
    EXPECT_TRUE(loginSimulation(attempts));
}

TEST(PathCoverage, SuccessThirdAttempt) {
    vector<pair<string,string>> attempts = {
        {"x","y"},
        {"a","b"},
        {"Aakash","1234"}
    };
    EXPECT_TRUE(loginSimulation(attempts));
}

TEST(PathCoverage, FailAllAttempts) {
    vector<pair<string,string>> attempts = {
        {"a","b"}, {"c","d"}, {"e","f"}
    };
    EXPECT_FALSE(loginSimulation(attempts));
}

// ===================================================
// 🔥 4. LOOP TESTING
// ===================================================

int loopTestFunction(int ch) {
    int count = 0;
    do {
        count++;
    } while(ch-- > 1);
    return count;
}

TEST(LoopTesting, ZeroCase) {
    EXPECT_EQ(loopTestFunction(1), 1);
}

TEST(LoopTesting, SingleIteration) {
    EXPECT_EQ(loopTestFunction(2), 2);
}

TEST(LoopTesting, MultipleIteration) {
    EXPECT_EQ(loopTestFunction(5), 5);
}

// ===================================================
// 🔥 5. INTERNAL STRUCTURE TESTING
// ===================================================

TEST(DownloadTest, QueuedState) {
    EXPECT_EQ(downloadStatus(0), "QUEUED");
}

TEST(DownloadTest, DownloadingState) {
    EXPECT_EQ(downloadStatus(50), "DOWNLOADING");
}

TEST(DownloadTest, CompletedState) {
    EXPECT_EQ(downloadStatus(100), "COMPLETED");
}

TEST(DownloadTest, InvalidState) {
    EXPECT_EQ(downloadStatus(150), "INVALID");
}

// ===================================================
// 🔥 6. EDGE CASE TESTING
// ===================================================

TEST(EdgeCase, EmptyCredentials) {
    EXPECT_FALSE(checkCredentials("", ""));
}

TEST(EdgeCase, SpecialCharacters) {
    EXPECT_FALSE(checkCredentials("@@@", "###"));
}

TEST(EdgeCase, CaseSensitivity) {
    EXPECT_FALSE(checkCredentials("aakash", "1234"));
}

TEST(EdgeCase, NegativeRating) {
    EXPECT_FALSE(validateRating(-1));
}

TEST(EdgeCase, LargeRating) {
    EXPECT_FALSE(validateRating(100));
}

// ===================================================
// MAIN
// ===================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
