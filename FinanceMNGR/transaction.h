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

// Abstrakcyjna klasa bazowa reprezentuj¹ca transakcjê
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

    // Funkcja wirtualna zwracaj¹ca podtyp transakcji jako string
    virtual std::string getSubtype() const = 0;

    double getAmount() const;
    const std::string& getDate() const;
    const std::string& getDescription() const;

    // Settery
    void setDate(const std::string& newDate);
    void setDescription(const std::string& newDesc);
    void setAmount(double newAmt);

    // Metoda umo¿liwiaj¹ca klonowanie obiektów (wspiera kopiowanie polimorficzne)
    virtual Transaction* clone() const = 0;

    // Metoda serializuj¹ca obiekt do formatu CSV
    virtual std::string toCSV() const;

    // Funkcja zaprzyjaŸniona – umo¿liwia wypisanie transakcji
    friend std::ostream& operator<<(std::ostream& os, const Transaction& t);
};

// Klasa reprezentuj¹ca dochód
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

// Klasa reprezentuj¹ca wydatek
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

