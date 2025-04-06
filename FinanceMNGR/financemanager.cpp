#include "FinanceManager.h"
#include <sstream>
#include <algorithm>
#include <map>

// Konstruktor domyœlny
FinanceManager::FinanceManager(const std::string& dbFile) : databaseFile(dbFile) {
    loadFromDatabase();
    // Jeœli plik nie istnieje, utworzymy go od razu, aby by³ gotowy do zapisu
    if (!std::ifstream(databaseFile).good()) {
        std::ofstream createFile(databaseFile);
        if (createFile.is_open()) {
            createFile << "Data,Typ,Podtyp,Opis,Kwota\n";
            createFile.close();
            std::cout << "Utworzono nowy plik bazy danych: " << databaseFile << std::endl;
        }
    }
}

// Konstruktor kopiuj¹cy – wykonuje g³êbok¹ kopiê transakcji
FinanceManager::FinanceManager(const FinanceManager& other) : databaseFile(other.databaseFile) {
    for (const auto& t : other.transactions) {
        transactions.push_back(std::unique_ptr<Transaction>(t->clone()));
    }
}

// Dodawanie transakcji
void FinanceManager::addTransaction(Transaction* t) {
    transactions.push_back(std::unique_ptr<Transaction>(t));
}

// Dodawanie dochodu
void FinanceManager::addIncome(const std::string& date, const std::string& desc, double amt, IncomeType type) {
    addTransaction(new Income(date, desc, amt, type));
}

// Dodawanie wydatku
void FinanceManager::addExpense(const std::string& date, const std::string& desc, double amt, ExpenseType type) {
    addTransaction(new Expense(date, desc, amt, type));
}

// Wypisanie transakcji na std::cout
void FinanceManager::listTransactions() const {
    if (transactions.empty()) {
        std::cout << "Brak transakcji." << std::endl;
        return;
    }
    for (const auto& t : transactions) {
        std::cout << *t << std::endl;
    }
}

// Wypisanie transakcji w podanym zakresie dat
void FinanceManager::listTransactionsByDate(const std::string& startDate, const std::string& endDate) const {
    for (const auto& t : transactions) {
        if (t->getDate() >= startDate && t->getDate() <= endDate) {
            std::cout << *t << std::endl;
        }
    }
}

// Edytowanie transakcji
bool FinanceManager::editTransaction(int index, const std::string& newDate, const std::string& newDesc, double newAmt) {
    if (index < 0 || index >= transactions.size()) {
        return false;
    }
    transactions[index]->setDate(newDate);
    transactions[index]->setDescription(newDesc);
    transactions[index]->setAmount(newAmt);
    return true;
}

// Usuwanie transakcji
bool FinanceManager::removeTransaction(int index) {
    if (index < 0 || index >= transactions.size()) {
        return false;
    }
    transactions.erase(transactions.begin() + index);
    return true;
}

// Generowanie raportu finansowego
void FinanceManager::generateReport(const std::string& startDate, const std::string& endDate) const {
    double totalIncome = 0.0;
    double totalExpense = 0.0;
    for (const auto& t : transactions) {
        if (t->getDate() >= startDate && t->getDate() <= endDate) {
            if (t->getType() == "Dochód") {
                totalIncome += t->getAmount();
            }
            else if (t->getType() == "Wydatek") {
                totalExpense += t->getAmount();
            }
        }
    }
    std::cout << "Raport od " << startDate << " do " << endDate << ":\n";
    std::cout << "Ca³kowity dochód: " << totalIncome << " z³\n";
    std::cout << "Ca³kowity wydatek: " << totalExpense << " z³\n";
    std::cout << "Saldo: " << (totalIncome - totalExpense) << " z³\n";
}

// Obliczenie salda – dochody sumujemy, wydatki odejmujemy
double FinanceManager::getBalance() const {
    double balance = 0.0;
    for (const auto& t : transactions) {
        if (t->getType() == "Dochód")
            balance += t->getAmount();
        else if (t->getType() == "Wydatek")
            balance -= t->getAmount();
    }
    return balance;
}

// Obliczenie sumy konkretnego typu dochodu
double FinanceManager::getIncomeTotal(IncomeType type) const {
    double total = 0.0;
    for (const auto& t : transactions) {
        if (t->getType() == "Dochód") {
            const Income* income = dynamic_cast<const Income*>(t.get());
            if (income && income->getIncomeType() == type) {
                total += income->getAmount();
            }
        }
    }
    return total;
}

// Obliczenie sumy konkretnego typu wydatku
double FinanceManager::getExpenseTotal(ExpenseType type) const {
    double total = 0.0;
    for (const auto& t : transactions) {
        if (t->getType() == "Wydatek") {
            const Expense* expense = dynamic_cast<const Expense*>(t.get());
            if (expense && expense->getExpenseType() == type) {
                total += expense->getAmount();
            }
        }
    }
    return total;
}

// Podsumowanie wed³ug kategorii
void FinanceManager::summarizeByCategory() const {
    std::cout << "===== PODSUMOWANIE DOCHODÓW =====\n";
    std::cout << "Praca: " << std::fixed << std::setprecision(2) << getIncomeTotal(IncomeType::Work) << " z³\n";
    std::cout << "Dodatkowe: " << std::fixed << std::setprecision(2) << getIncomeTotal(IncomeType::Additional) << " z³\n";

    std::cout << "\n===== PODSUMOWANIE WYDATKÓW =====\n";
    std::cout << "Rachunki: " << std::fixed << std::setprecision(2) << getExpenseTotal(ExpenseType::Bills) << " z³\n";
    std::cout << "Jedzenie: " << std::fixed << std::setprecision(2) << getExpenseTotal(ExpenseType::Food) << " z³\n";
    std::cout << "Ubrania: " << std::fixed << std::setprecision(2) << getExpenseTotal(ExpenseType::Clothes) << " z³\n";
    std::cout << "Inne: " << std::fixed << std::setprecision(2) << getExpenseTotal(ExpenseType::Other) << " z³\n";

    std::cout << "\nSALDO OGÓLNE: " << std::fixed << std::setprecision(2) << getBalance() << " z³\n";
}

// Zapisywanie danych do pliku CSV
bool FinanceManager::saveToDatabase() const {
    std::ofstream file(databaseFile);
    if (!file.is_open()) {
        std::cerr << "Nie mo¿na otworzyæ pliku bazy danych do zapisu: " << databaseFile << std::endl;
        return false;
    }

    file << "Data,Typ,Podtyp,Opis,Kwota\n";

    for (const auto& t : transactions) {
        file << t->toCSV() << "\n";
    }

    file.close();
    std::cout << "Dane zapisano pomyœlnie do pliku: " << databaseFile << std::endl;
    return true;
}

// Wczytywanie danych z pliku CSV
bool FinanceManager::loadFromDatabase() {
    std::ifstream file(databaseFile);
    if (!file.is_open()) {
        std::cout << "Plik bazy danych nie istnieje: " << databaseFile << ". Zostanie utworzony nowy plik." << std::endl;
        return false;
    }

    transactions.clear();
    std::string line;

    // SprawdŸ czy plik nie jest pusty
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Plik bazy danych jest pusty." << std::endl;
        file.close();
        return true;
    }

    // Wczytaj nag³ówek
    std::getline(file, line);

    // Wczytaj dane
    while (std::getline(file, line)) {
        try {
            std::stringstream ss(line);
            std::string date, type, subtype, desc, amountStr;

            std::getline(ss, date, ',');
            std::getline(ss, type, ',');
            std::getline(ss, subtype, ',');
            std::getline(ss, desc, ',');
            std::getline(ss, amountStr, ',');

            double amount = std::stod(amountStr);

            if (type == "Dochód") {
                IncomeType incomeType = IncomeType::Additional; // domyœlnie
                if (subtype == "Praca") incomeType = IncomeType::Work;
                addIncome(date, desc, amount, incomeType);
            }
            else if (type == "Wydatek") {
                ExpenseType expenseType = ExpenseType::Other; // domyœlnie
                if (subtype == "Rachunki") expenseType = ExpenseType::Bills;
                else if (subtype == "Jedzenie") expenseType = ExpenseType::Food;
                else if (subtype == "Ubrania") expenseType = ExpenseType::Clothes;
                addExpense(date, desc, amount, expenseType);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "B³¹d podczas przetwarzania linii: " << line << " - " << e.what() << std::endl;
            // Kontynuuj z nastêpn¹ lini¹
        }
    }

    std::cout << "Wczytano " << transactions.size() << " transakcji z pliku: " << databaseFile << std::endl;
    file.close();
    return true;
}

// Przeci¹¿enie operatora + – ³¹czy dane z dwóch menad¿erów
FinanceManager FinanceManager::operator+(const FinanceManager& other) const {
    FinanceManager merged(*this); // kopiujemy bie¿¹ce transakcje
    for (const auto& t : other.transactions) {
        merged.addTransaction(t->clone());
    }
    return merged;
}

// Przeci¹¿enie operatora +=
FinanceManager& FinanceManager::operator+=(const FinanceManager& other) {
    for (const auto& t : other.transactions) {
        addTransaction(t->clone());
    }
    return *this;
}

// Operator wypisania – u¿ywa przekazanego strumienia, nie std::cout
std::ostream& operator<<(std::ostream& os, const FinanceManager& fm) {
    os << "Lista transakcji:\n";
    if (fm.transactions.empty()) {
        os << "Brak transakcji.\n";
    }
    else {
        for (const auto& t : fm.transactions) {
            os << *t << "\n";
        }
    }
    os << "\nSaldo: " << std::fixed << std::setprecision(2) << fm.getBalance() << "\n";
    return os;
}

// Implementacja metody getTransactions
const std::vector<std::unique_ptr<Transaction>>& FinanceManager::getTransactions() const {
    return transactions;
}
