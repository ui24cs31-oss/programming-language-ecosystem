# Programming Language Ecosystem 🖥️

An interactive C++ console application that simulates a **Programming Language Ecosystem** platform. This project was developed as part of a **Semester 4 Object-Oriented Programming** course to demonstrate core OOP concepts.

## 📌 OOP Concepts Demonstrated

| Concept | Where Used |
|---|---|
| **Inheritance** | `Admin`, `Developer`, `RegularUser` inherit from `User` |
| **Polymorphism** | `performAction()` overridden in each subclass |
| **Constructors & Destructors** | Defined across all major classes |
| **Static Variables** | `DownloadState` static constants (BROWSING, QUEUED, etc.) |
| **Encapsulation** | Private members with public getters/setters in all classes |
| **Abstraction** | Pure virtual `performAction()` in `User` base class |

## 🧩 System Architecture

```
User (abstract base)
├── Admin       – Manages languages, permissions, users
├── Developer   – Submits new languages for approval
└── RegularUser – Searches, downloads, rates, and reviews languages
```

**Supporting Classes:**
- `ProgrammingLanguage` – Holds language info, versions, and ratings
- `Version` – Tracks version metadata and download counts
- `Rating` – Stores user ratings and feedback text
- `DownloadRecord` – Tracks download state and progress
- `DownloadState` – State machine (BROWSING → QUEUED → DOWNLOADING → COMPLETED)
- `Permission` – Role-based permission descriptor

## 🚀 Getting Started

### Prerequisites
- A C++ compiler supporting **C++11** or later (e.g., `g++`, `clang++`, MSVC)

### Compile & Run

**Using g++ (Linux/macOS/MinGW):**
```bash
g++ -std=c++11 -o ecosystem Main.cpp
./ecosystem
```

**Using g++ on Windows (PowerShell):**
```powershell
g++ -std=c++11 -o ecosystem.exe Main.cpp
.\ecosystem.exe
```

**Using MSVC (Developer Command Prompt):**
```cmd
cl /EHsc /std:c++17 Main.cpp /Fe:ecosystem.exe
ecosystem.exe
```

## 🎮 Usage

The app presents an interactive menu:

```
=== Programming Language Ecosystem Interactive Menu ===
1. Login as Admin
2. Login as Developer
3. Login as Regular User
4. Exit
```

### Default Credentials
| Role | Username | Password |
|---|---|---|
| Admin | `Aakash` | `1234` |
| Developer | *(no auth required)* | – |
| Regular User | *(no auth required)* | – |

### Features by Role

**Admin**
- Approve pending language submissions
- Delete languages from the ecosystem
- View all registered users
- Manage permissions
- Review user feedback

**Developer**
- Submit new programming languages for approval
- View contribution count

**Regular User**
- Browse all available languages
- Search languages by name
- Download a language (simulated)
- Rate languages (1–5 stars, one rating per language)
- Provide written feedback (requires prior rating)
- View average ratings

## 📁 Project Structure

```
project/
├── Main.cpp          # Full source code (single-file project)
├── README.md
├── .gitignore
├── TESting/          # Testing documentation & test programs
│   ├── blackbox.cpp
│   ├── bottom_up.cpp
│   ├── state_based.cpp
│   ├── top_down.cpp
│   ├── whitebox.cpp
│   └── *.pdf         # Testing strategy documents
└── dig/              # UML diagrams
    ├── class.png
    ├── usecase.png
    ├── sequence.png
    ├── activity.png
    ├── state.png
    └── Communication.png
```

## 📊 UML Diagrams

The `dig/` folder contains full UML diagrams for this system:
- **Class Diagram** – Full class hierarchy and relationships
- **Use Case Diagram** – Actor interactions
- **Sequence Diagram** – Key interaction flows
- **Activity Diagram** – Control flow
- **State Diagram** – DownloadRecord state machine
- **Communication Diagram** – Object collaboration

## 📄 License

This project is for academic purposes only.
