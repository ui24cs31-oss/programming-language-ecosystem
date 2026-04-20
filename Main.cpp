#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <limits>

enum class UserRole { Admin, Developer, RegularUser };

struct Profile {
    std::string name;
};

struct Date {
    std::string timestamp;
    Date() { timestamp = "2024-01-01T00:00:00Z"; }
    Date(std::string ts) : timestamp(ts) {}
};

class Version;
class Rating;
class ProgrammingLanguage;
class ContributedLanguage;
class DownloadRecord;
class DownloadState;
class User;
class Admin;
class Developer;
class RegularUser;
class Permission;

class Permission {
private:
    int permissionId;
    std::string permissionName;
    std::string description;
public:
    Permission(int id, std::string name, std::string desc) 
        : permissionId(id), permissionName(name), description(desc) {}
    
    int getId() { return permissionId; }
    std::string getName() { return permissionName; }
    std::string getDescription() { return description; }
};

class Rating {
private:
    int ratingId;
    int userId;
    int languageId;
    int rating;
    std::string feedback;
    Date timestamp;
public:
    Rating(int userId, int langId, int rating) 
        : userId(userId), languageId(langId), rating(rating) {
        ratingId = rand() % 10000;
    }
    
    int getId() { return ratingId; }
    int getUserId() { return userId; }
    int getRating() { return rating; }
    std::string getFeedback() { return feedback; }
    void setFeedback(std::string text) { feedback = text; }
};

class Version {
private:
    int versionId;
    std::string versionNumber;
    double fileSize;
    int downloadCount;
    std::string checksum;
public:
    Version(std::string vNum, double size) 
        : versionNumber(vNum), fileSize(size), downloadCount(0) {
        versionId = rand() % 10000;
        checksum = "dummy_checksum";
    }
    
    std::string calculateChecksum() { return checksum; }
    double getFileSize() { return fileSize; }
    bool validateChecksum(std::string chk) { return chk == checksum; }
    void incrementDownloadCount() { downloadCount++; }
    int getId() { return versionId; }
    std::string getVersionNumber() { return versionNumber; }
    int getDownloadCount() { return downloadCount; }
};

class DownloadState {
private:
    std::string stateName;
    Date timestamp;
    std::map<std::string, std::vector<std::string>> transitionMap;

public:
    static const DownloadState BROWSING;
    static const DownloadState QUEUED;
    static const DownloadState DOWNLOADING;
    static const DownloadState PAUSED;
    static const DownloadState VERIFYING;
    static const DownloadState COMPLETED;
    static const DownloadState FAILED;

    DownloadState(std::string name) : stateName(name) {
        if (name == "QUEUED") transitionMap["QUEUED"] = {"DOWNLOADING", "FAILED"};
    }
    bool canTransitionTo(DownloadState next) { return true; }
    std::string getStateName() const { return stateName; }
    Date getTimestamp() { return timestamp; }
};

const DownloadState DownloadState::BROWSING("BROWSING");
const DownloadState DownloadState::QUEUED("QUEUED");
const DownloadState DownloadState::DOWNLOADING("DOWNLOADING");
const DownloadState DownloadState::PAUSED("PAUSED");
const DownloadState DownloadState::VERIFYING("VERIFYING");
const DownloadState DownloadState::COMPLETED("COMPLETED");
const DownloadState DownloadState::FAILED("FAILED");

class DownloadRecord {
private:
    int downloadId;
    int userId;
    int languageId;
    int versionId;
    Date downloadDate;
    double fileSize;
    double progress;
    DownloadState status;
    double downloadSpeed;
    Version* version;

public:
    DownloadRecord(int uId, int lId, int vId) 
        : userId(uId), languageId(lId), versionId(vId), status(DownloadState::QUEUED), progress(0.0) {
        downloadId = rand() % 10000;
    }
    ~DownloadRecord() {}
    
    void updateProgress(double pct) { progress = pct; }
    bool updateStatus(DownloadState state) { status = state; return true; }
    bool isCompleted() { return progress >= 100.0; }
    int getEstimatedTime() { return 100; }
    void pause() { status = DownloadState::PAUSED; }
    void resume() { status = DownloadState::DOWNLOADING; }
    void cancel() { status = DownloadState::FAILED; }
    int getId() { return downloadId; }
    double getProgress() { return progress; }
    std::string getStatus() { return status.getStateName(); }
};

class ContributedLanguage {
private:
    int contributionId;
    int languageId;
    Date submissionDate;
    std::string status;
public:
    ContributedLanguage(int cId, int lId) : contributionId(cId), languageId(lId), status("PENDING") {}
    int getId() { return contributionId; }
    int getLanguageId() { return languageId; }
    std::string getStatus() { return status; }
    void setStatus(std::string st) { status = st; }
};

class ProgrammingLanguage {
private:
    int languageId;
    std::string name;
    std::string description;
    std::string paradigm;
    std::string license;
    std::vector<Version> versions;
    std::vector<Rating*> ratings;
    int totalDownloads;

public:
    ProgrammingLanguage(std::string name, std::string desc) 
        : name(name), description(desc), totalDownloads(0) {
        languageId = rand() % 10000;
    }
    void addVersion(Version v) { versions.push_back(v); }
    void addRating(Rating* r) { ratings.push_back(r); }
    double getAverageRating() { 
        if (ratings.empty()) return 0.0;
        double sum = 0;
        for (auto r : ratings) sum += r->getRating();
        return sum / ratings.size();
    }
    int getId() { return languageId; }
    std::string getName() { return name; }
    int getTotalDownloads() { return totalDownloads; }
    std::vector<Rating*> getRatings() { return ratings; }
};

class User {
protected:
    int userId;
    std::string username;
    std::string email;
    std::string password;
    UserRole role;
    std::vector<Rating*> ratings; 

public:
    User(int id, std::string u, std::string e, std::string p) 
        : userId(id), username(u), email(e), password(p), role(UserRole::RegularUser) {}
    virtual ~User() {}
    
    virtual void performAction() = 0;
    
    Profile getProfile() { return Profile{username}; }
    void updateProfile(std::string name) { username = name; }
    bool validatePassword(std::string pwd) { return password == pwd; }
    int getId() { return userId; }
    UserRole getRole() { return role; }
};

class Admin : public User {
private:
    int adminId;
    std::vector<Permission> permissions;
public:
    Admin(int id, std::string u, std::string p) 
        : User(id, u, "admin@ecosystem.org", p) {
        adminId = id;
        role = UserRole::Admin;
    }
    ~Admin() {}
    
    void performAction() override {
        std::cout << "- Admin " << username << " performing action." << std::endl;
    }
    bool addLanguage(ProgrammingLanguage lang) { return true; }
    bool deleteLanguage(int langId) { return true; }
    std::vector<User*> viewAllUsers() { return std::vector<User*>(); }
    void managePermissions(User* u) {}
    int getAdminId() { return adminId; }
};

class Developer : public User {
private:
    int developerId;
    std::vector<ContributedLanguage> contributedLanguages;
    int contributionCount;
public:
    Developer(int id, std::string u, std::string p) 
        : User(id, u, "dev@ecosystem.org", p), contributionCount(0) {
        developerId = id;
        role = UserRole::Developer;
    }
    ~Developer() {}

    void performAction() override {
        std::cout << "- Developer " << username << " performing action." << std::endl;
    }
    bool submitLanguage(ProgrammingLanguage lang) { return true; }
    bool updateLanguage(ProgrammingLanguage lang) { return true; }
    std::vector<ProgrammingLanguage> viewContributions() { return std::vector<ProgrammingLanguage>(); }
    int getContributionCount() { return contributionCount; }
    void incrementContribution() { contributionCount++; }
};

class RegularUser : public User {
private:
    int userId;
    std::vector<DownloadRecord*> downloadHistory;
    int ratingCount;
    std::vector<int> ratedLanguages;
public:
    RegularUser(int id, std::string u, std::string p) 
        : User(id, u, "user@ecosystem.org", p), ratingCount(0) {
        this->userId = id;
        role = UserRole::RegularUser;
    }
    ~RegularUser() {}

    void performAction() override {
        std::cout << "- RegularUser " << username << " performing action." << std::endl;
    }
    std::vector<ProgrammingLanguage> searchLanguage(std::string query) { return std::vector<ProgrammingLanguage>(); }
    std::vector<ProgrammingLanguage> browseLanguages() { return std::vector<ProgrammingLanguage>(); }
    
    DownloadRecord downloadLanguage(ProgrammingLanguage* l, Version* v) {
        DownloadRecord dr(this->userId, l->getId(), v->getId());
        return dr;
    }
    bool rateLanguage(int langId, int rating) { return true; }
    bool provideFeedback(int langId, std::string text) { return true; }
    int getRatingCount() { return ratingCount; }
    bool hasRated(int langId) { return std::find(ratedLanguages.begin(), ratedLanguages.end(), langId) != ratedLanguages.end(); }
    void recordRating(int langId) { ratedLanguages.push_back(langId); }
};

int main() {
    Admin admin(1, "Aakash", "1234");
    Developer dev(2, "dev1", "pass");
    RegularUser activeUser(100, "alice", "pwd123");

    ProgrammingLanguage clang("C++", "System programming language");
    Version cpp20("20", 1024.5);
    clang.addVersion(cpp20);

    std::vector<std::string> pendingLanguages;
    std::vector<ProgrammingLanguage*> ecosystemLanguages;
    ecosystemLanguages.push_back(&clang);
    
    std::vector<std::string> hardcodedLangs = {
        "Python", "Java", "JavaScript", "C#", "Ruby", "PHP", 
        "Swift", "Go", "Kotlin", "TypeScript", "Scala", "R", 
        "Perl", "Haskell", "Lua", "Dart", "Elixir", "C", "Rust", "Clojure"
    };
    for (const auto& name : hardcodedLangs) {
        ecosystemLanguages.push_back(new ProgrammingLanguage(name, "Standard language"));
    }

    int choice;
    while(true) {
        std::cout << "\n=== Programming Language Ecosystem Interactive Menu ===" << std::endl;
        std::cout << "1. Login as Admin" << std::endl;
        std::cout << "2. Login as Developer" << std::endl;
        std::cout << "3. Login as Regular User" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter choice: ";
        if (!(std::cin >> choice)) {
        std::cout << "Invalid input! Only numbers allowed.\n";
    std::cin.clear(); // reset fail state
    std::cin.ignore(1000, '\n'); // discard bad input
    continue; // retry
}

        if (choice == 1) {
            std::string inputUser, inputPass;
            std::cout << "Enter Admin ID: ";
            std::cin >> inputUser;
            std::cout << "Enter Password: ";
            std::cin >> inputPass;
            
            if (inputUser == admin.getProfile().name && admin.validatePassword(inputPass)) {
                while (true) {
                    std::cout << "\n--- Admin Menu ---" << std::endl;
                    std::cout << "1. Perform Default Action\n2. Approve Pending Language\n3. Delete Language\n4. View All Users\n5. Manage Permissions\n6. Check Feedback\n7. Logout\nChoice: ";
                    int sub;
                    if (!(std::cin >> sub)) break;
                    if (sub == 1) admin.performAction();
                    else if (sub == 2) {
                        if (pendingLanguages.empty()) {
                            std::cout << "[Admin] No pending languages to approve." << std::endl;
                        } else {
                            std::string langName = pendingLanguages.front();
                            pendingLanguages.erase(pendingLanguages.begin());
                            ProgrammingLanguage* approvedLang = new ProgrammingLanguage(langName, "Approved language");
                            ecosystemLanguages.push_back(approvedLang);
                            admin.addLanguage(*approvedLang);
                            dev.incrementContribution();
                            std::cout << "[Admin] Successfully approved language: " << langName << std::endl;
                        }
                    }
                    else if (sub == 3) {
                        int delId;
                        std::cout << "Enter language ID to delete: ";
                        std::cin >> delId;
                        auto it = std::remove_if(ecosystemLanguages.begin(), ecosystemLanguages.end(), [delId](ProgrammingLanguage* p){ return p->getId() == delId; });
                        if (it != ecosystemLanguages.end()) {
                            ecosystemLanguages.erase(it, ecosystemLanguages.end());
                            std::cout << "[Admin] Language ID " << delId << " prominently deleted from ecosystem." << std::endl;
                        } else {
                            std::cout << "[Admin] Language ID not found." << std::endl;
                        }
                    }
                    else if (sub == 4) {
                        std::cout << "[Admin] System currently has: \n- Admin ID 1\n- Developer ID 2\n- RegularUser ID 100\n";
                    }
                    else if (sub == 5) {
                        std::cout << "[Admin] Successfully updated user permissions (Simulation)." << std::endl;
                    }
                    else if (sub == 6) {
                        if (ecosystemLanguages.empty()) {
                            std::cout << "[Admin] No languages available." << std::endl;
                        } else {
                            std::cout << "Select a language to check feedback:\n";
                            for (size_t i = 0; i < ecosystemLanguages.size(); ++i) {
                                std::cout << (i + 1) << ". " << ecosystemLanguages[i]->getName() << std::endl;
                            }
                            int sel;
                            std::cout << "Choice: ";
                            if (!(std::cin >> sel)) break;
                            if (sel >= 1 && sel <= static_cast<int>(ecosystemLanguages.size())) {
                                ProgrammingLanguage* target = ecosystemLanguages[sel - 1];
                                std::cout << "--- Feedback for " << target->getName() << " ---" << std::endl;
                                bool hasFb = false;
                                for (auto r : target->getRatings()) {
                                    if (!r->getFeedback().empty()) {
                                        std::cout << r->getFeedback() << std::endl;
                                        hasFb = true;
                                    }
                                }
                                if (!hasFb) std::cout << "(No feedback available)" << std::endl;
                            } else {
                                std::cout << "Invalid selection!" << std::endl;
                            }
                        }
                    }
                    else if (sub == 7) { std::cout << "Logging out admin." << std::endl; break; }
                }
            } else {
                std::cout << "Invalid credentials! Access Denied." << std::endl;
            }
        } else if (choice == 2) {
            while (true) {
                std::cout << "\n--- Developer Menu ---" << std::endl;
                std::cout << "1. Perform Default Action\n2. Submit Language\n3. View Contributions\n4. Logout\nChoice: ";
                int sub;
                if (!(std::cin >> sub)) break;
                if (sub == 1) dev.performAction();
                else if (sub == 2) {
                    std::string langName;
                    std::cout << "Enter language name to submit: ";
                    std::cin >> langName;
                    bool exists = false;
                    for (auto l : ecosystemLanguages) {
                        if (l->getName() == langName) { exists = true; break; }
                    }
                    for (const auto& pending : pendingLanguages) {
                        if (pending == langName) { exists = true; break; }
                    }
                    if (exists) {
                        std::cout << "[Developer] Language '" << langName << "' already exists in the system or pending queue. Submission rejected." << std::endl;
                    } else {
                        pendingLanguages.push_back(langName);
                        std::cout << "[Developer] Submitted language '" << langName << "' for Admin approval." << std::endl;
                    }
                }
                else if (sub == 3) {
                    std::cout << "Current Contributions Count: " << dev.getContributionCount() << std::endl;
                }
                else if (sub == 4) { std::cout << "Logging out developer." << std::endl; break; }
            }
        } else if (choice == 3) {
            while (true) {
                std::cout << "\n--- Regular User Menu ---" << std::endl;
                std::cout << "1. Perform Default Action\n2. Search Language\n3. Browse Languages\n4. Download Language\n5. Rate Language\n6. Provide Feedback\n7. Get Average Rating\n8. Logout\nChoice: ";
                int sub;
                if (!(std::cin >> sub)) break;
                if (sub == 1) {
                    activeUser.performAction();
                } else if (sub == 2) {
                    std::string query;
                    std::cout << "Enter search query: ";
                    std::cin >> query;
                    bool found = false;
                    for (auto l : ecosystemLanguages) {
                        if (l->getName().find(query) != std::string::npos) {
                            std::cout << "[Result] " << l->getName() << " (ID: " << l->getId() << ")" << std::endl;
                            found = true;
                        }
                    }
                    if (!found) std::cout << "[Regular User] No exact match results found for '" << query << "'." << std::endl;
                } else if (sub == 3) {
                    std::cout << "[Regular User] Browsing Ecosystem catalog...\n";
                    for (auto l : ecosystemLanguages) {
                        std::cout << " - " << l->getName() << " (ID: " << l->getId() << ")" << std::endl;
                    }
                } else if (sub == 4) {
                    if (ecosystemLanguages.empty()) {
                        std::cout << "[Regular User] No languages available to download." << std::endl;
                    } else {
                        std::cout << "Select a language to download:\n";
                        for (size_t i = 0; i < ecosystemLanguages.size(); ++i) {
                            std::cout << (i + 1) << ". " << ecosystemLanguages[i]->getName() << std::endl;
                        }
                        int sel;
                        std::cout << "Choice: ";
                        if (!(std::cin >> sel)) break;
                        if (sel >= 1 && sel <= static_cast<int>(ecosystemLanguages.size())) {
                            ProgrammingLanguage* target = ecosystemLanguages[sel - 1];
                            DownloadRecord rec = activeUser.downloadLanguage(target, &cpp20);
                            rec.updateStatus(DownloadState::COMPLETED);
                            rec.updateProgress(100.0);
                            std::cout << "Downloaded " << target->getName() << " v" << cpp20.getVersionNumber() << std::endl;
                            std::cout << "Status: " << rec.getStatus() << " | Progress: " << rec.getProgress() << "%" << std::endl;
                        } else {
                            std::cout << "Invalid selection!" << std::endl;
                        }
                    }
                } else if (sub == 5) {
                    if (ecosystemLanguages.empty()) {
                        std::cout << "[Regular User] No languages available to rate." << std::endl;
                    } else {
                        std::cout << "Select a language to rate:\n";
                        for (size_t i = 0; i < ecosystemLanguages.size(); ++i) {
                            std::cout << (i + 1) << ". " << ecosystemLanguages[i]->getName() << std::endl;
                        }
                        int sel, r;
                        std::cout << "Choice: ";
                        if (!(std::cin >> sel)) break;
                        if (sel >= 1 && sel <= static_cast<int>(ecosystemLanguages.size())) {
                            ProgrammingLanguage* target = ecosystemLanguages[sel - 1];
                            if (activeUser.hasRated(target->getId())) {
                                std::cout << "[Regular User] You have already rated this language! Only one rating allowed." << std::endl;
                            } else {
                                std::cout << "Enter rating (1-5): ";
                                if (!(std::cin >> r)) break;
                                activeUser.recordRating(target->getId());
                                activeUser.rateLanguage(target->getId(), r);
                                Rating* newRating = new Rating(activeUser.getId(), target->getId(), r);
                                target->addRating(newRating);
                                std::cout << "[Regular User] Rated language " << r << " stars." << std::endl;
                            }
                        } else {
                            std::cout << "Invalid selection!" << std::endl;
                        }
                    }
                } else if (sub == 6) {
                    if (ecosystemLanguages.empty()) {
                        std::cout << "[Regular User] No languages available." << std::endl;
                    } else {
                        std::cout << "Select a language to provide feedback:\n";
                        for (size_t i = 0; i < ecosystemLanguages.size(); ++i) {
                            std::cout << (i + 1) << ". " << ecosystemLanguages[i]->getName() << std::endl;
                        }
                        int sel;
                        std::cout << "Choice: ";
                        if (!(std::cin >> sel)) break;
                        if (sel >= 1 && sel <= static_cast<int>(ecosystemLanguages.size())) {
                            ProgrammingLanguage* target = ecosystemLanguages[sel - 1];
                            Rating* userRating = nullptr;
                            for (auto r : target->getRatings()) {
                                if (r->getUserId() == activeUser.getId()) { userRating = r; break; }
                            }
                            if (userRating) {
                                std::string fb;
                                std::cout << "Enter feedback text: ";
                                std::cin >> std::ws;
                                std::getline(std::cin, fb);
                                std::string current = userRating->getFeedback();
                                if (current.empty()) {
                                    userRating->setFeedback("- " + fb);
                                } else {
                                    userRating->setFeedback(current + "\n- " + fb);
                                }
                                activeUser.provideFeedback(target->getId(), fb);
                                std::cout << "[Regular User] Successfully recorded feedback: \"" << fb << "\"" << std::endl;
                            } else {
                                std::cout << "[Regular User] You must rate this language first before providing feedback!" << std::endl;
                            }
                        } else {
                            std::cout << "Invalid selection!" << std::endl;
                        }
                    }
                } else if (sub == 7) {
                    if (ecosystemLanguages.empty()) {
                        std::cout << "[Regular User] No languages available." << std::endl;
                    } else {
                        std::cout << "Select a language to get average rating:\n";
                        for (size_t i = 0; i < ecosystemLanguages.size(); ++i) {
                            std::cout << (i + 1) << ". " << ecosystemLanguages[i]->getName() << std::endl;
                        }
                        int sel;
                        std::cout << "Choice: ";
                        if (!(std::cin >> sel)) break;
                        if (sel >= 1 && sel <= static_cast<int>(ecosystemLanguages.size())) {
                            ProgrammingLanguage* target = ecosystemLanguages[sel - 1];
                            std::cout << "[Regular User] Average rating for " << target->getName() << " is: " << target->getAverageRating() << " stars." << std::endl;
                        } else {
                            std::cout << "Invalid selection!" << std::endl;
                        }
                    }
                } else if (sub == 8) {
                    std::cout << "Logging out regular user." << std::endl; break;
                }
            }
        } else if (choice == 4) {
            std::cout << "Exiting application." << std::endl;
            break;
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
    return 0;
}
