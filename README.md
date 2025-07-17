# Personal Finance Manager

A desktop application for managing personal finances with a modern mBank-inspired UI, built using **C++** and **Dear ImGui** (OpenGL + GLFW). Easily add, edit, and view your incomes and expenses, generate summaries and reports, and manage standing orders.

## Features

- **Modern UI:** Clean, responsive interface inspired by mBank.
- **Income & Expense Tracking:** Add, edit, remove, and filter transactions.
- **Categories:** Built-in types for income (`Work`, `Additional`) and expense (`Bills`, `Food`, `Clothes`, `Other`).
- **Financial Summary:** See your balance, latest transactions, and a balance history chart.
- **Reports:** Generate detailed reports for any date range.
- **Standing Orders:** Support for monthly recurring transactions (like rent or salary).
- **CSV Database:** All data is saved to and loaded from a CSV file (`db.csv`), which can be easily backed up or edited.

## Screenshots

*(Feel free to add screenshots here!)*

---

## Build & Run

### Requirements

- C++17 or newer
- CMake (recommended)
- [Dear ImGui](https://github.com/ocornut/imgui) (with OpenGL and GLFW bindings)
- [GLFW](https://www.glfw.org/) and [OpenGL](https://www.opengl.org/)
- (Optionally) Visual Studio, CLion, or any modern C++ IDE

### Quick Start (Linux/Mac/WSL)

```bash
git clone https://github.com/yourusername/personal-finance-manager.git
cd personal-finance-manager
mkdir build && cd build
cmake ..
make
./PersonalFinanceManager
```

Quick Start (Windows)

    Clone the repository.

    Open the project in Visual Studio or your C++ IDE.

    Make sure Dear ImGui, GLFW, and OpenGL libraries are included (see CMakeLists.txt or project properties).

    Build and run.

File Structure

    main.cpp — Entry point, handles ImGui UI, events, and main loop.

    financemanager.h/cpp — Main business logic: adding/editing transactions, summaries, reports, saving/loading CSV.

    transaction.h/cpp — Class hierarchy for transactions (base Transaction, and derived Income, Expense).

    db.csv — (Auto-created) Stores all transactions.

    standing_orders.csv — Stores recurring (monthly) transactions.

Usage

    Home: See current balance, latest incomes/expenses, balance chart, and all transactions.

    Transactions: Full editable/filterable transaction list.

    Add Income/Expense: Add a new transaction with category and description.

    Standing Orders: Add monthly recurring transactions.

    Summary/Report: See statistics per category, or generate a full report for any date range.

    Everything is saved automatically to CSV.

Data Format

db.csv

Date,Type,Subtype,Description,Amount
01.07.2024,Dochod,Praca,Salary,5000
05.07.2024,Wydatek,Jedzenie,Groceries,-300
...

standing_orders.csv

StartDate,Type,Category,Description,Amount
01.01.2024,Przychod,Praca,Salary,5000
10.01.2024,Wydatek,Rachunki,Rent,2000
...

License

MIT 

Feel free to contribute or report issues!
