#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <iomanip>

// Typy dochodów
enum class IncomeType {
    Work,
    Additional
};

// Typy wydatków
enum class ExpenseType {
    Bills,
    Food,
    Clothes,
    Other
};

// Klasa bazowa reprezentująca transakcję
class Transaction {
protected:
    std::string date;
    std::string description;
    double amount;
public:
    Transaction(const std::string& date, const std::string& desc, double amt);
    virtual ~Transaction();

    // Funkcja czysto wirtualna – zwraca typ transakcji jako string
    virtual std::string getType() const = 0;

    // Funkcja wirtualna zwracająca podtyp transakcji jako string
    virtual std::string getSubtype() const = 0;

    double getAmount() const;
    const std::string& getDate() const;
    const std::string& getDescription() const;

    // Settery
    void setDate(const std::string& newDate);
    void setDescription(const std::string& newDesc);
    void setAmount(double newAmt);

    // Metoda umożliwiająca klonowanie obiektów (wspiera kopiowanie polimorficzne)
    virtual Transaction* clone() const = 0;

    // Metoda serializująca obiekt do formatu CSV
    virtual std::string toCSV() const;

    // Funkcja zaprzyjaźniona – umożliwia wypisanie transakcji
    friend std::ostream& operator<<(std::ostream& os, const Transaction& t);
};

// Klasa reprezentująca dochód
class Income : public Transaction {
private:
    IncomeType incomeType;
public:
    Income(const std::string& date, const std::string& desc, double amt, IncomeType type);
    std::string getType() const override;
    std::string getSubtype() const override;
    IncomeType getIncomeType() const;
    Transaction* clone() const override;
    std::string toCSV() const override;
};

// Klasa reprezentująca wydatek
class Expense : public Transaction {
private:
    ExpenseType expenseType;
public:
    Expense(const std::string& date, const std::string& desc, double amt, ExpenseType type);
    std::string getType() const override;
    std::string getSubtype() const override;
    ExpenseType getExpenseType() const;
    Transaction* clone() const override;
    std::string toCSV() const override;
};

#endif // TRANSACTION_H

