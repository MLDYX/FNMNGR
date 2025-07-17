#include "transaction.h"

// Konstruktor i destruktor klasy Transaction
Transaction::Transaction(const std::string& date, const std::string& desc, double amt)
    : date(date), description(desc), amount(amt) {
}

Transaction::~Transaction() {}

double Transaction::getAmount() const {
    return amount;
}

const std::string& Transaction::getDate() const {
    return date;
}

const std::string& Transaction::getDescription() const {
    return description;
}

void Transaction::setDate(const std::string& newDate) {
    date = newDate;
}

void Transaction::setDescription(const std::string& newDesc) {
    description = newDesc;
}

void Transaction::setAmount(double newAmt) {
    amount = newAmt;
}

std::string Transaction::toCSV() const {
    return date + "," + getType() + "," + getSubtype() + "," + description + "," +
        std::to_string(amount);
}

// Operator wypisania – umo¿liwia wygodne wyœwietlanie obiektów Transaction
std::ostream& operator<<(std::ostream& os, const Transaction& t) {
    os << "[" << t.getType() << " - " << t.getSubtype() << "] "
        << t.date << " - "
        << t.description << " : "
        << std::fixed << std::setprecision(2) << t.amount;
    return os;
}

// Implementacja klasy Income
Income::Income(const std::string& date, const std::string& desc, double amt, IncomeType type)
    : Transaction(date, desc, amt), incomeType(type) {
}

std::string Income::getType() const {
    return "Dochod";
}

std::string Income::getSubtype() const {
    switch (incomeType) {
    case IncomeType::Work: return "Praca";
    case IncomeType::Additional: return "Dodatkowy";
    default: return "Nieznany";
    }
}

IncomeType Income::getIncomeType() const {
    return incomeType;
}

Transaction* Income::clone() const {
    return new Income(*this);
}

std::string Income::toCSV() const {
    return Transaction::toCSV();
}

// Implementacja klasy Expense
Expense::Expense(const std::string& date, const std::string& desc, double amt, ExpenseType type)
    : Transaction(date, desc, amt), expenseType(type) {
}

std::string Expense::getType() const {
    return "Wydatek";
}

std::string Expense::getSubtype() const {
    switch (expenseType) {
    case ExpenseType::Bills: return "Rachunki";
    case ExpenseType::Food: return "Jedzenie";
    case ExpenseType::Clothes: return "Ubrania";
    case ExpenseType::Other: return "Inne";
    default: return "Nieznany";
    }
}

ExpenseType Expense::getExpenseType() const {
    return expenseType;
}

Transaction* Expense::clone() const {
    return new Expense(*this);
}

std::string Expense::toCSV() const {
    return Transaction::toCSV();
}

