#pragma once
#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <fstream>
#include "transaction.h"

// Klasa zarz¹dzaj¹ca finansami – logika biznesowa
class FinanceManager {
private:
    std::vector<std::unique_ptr<Transaction>> transactions;
    std::string databaseFile;
public:
    FinanceManager(const std::string& dbFile = "db.csv");
    FinanceManager(const FinanceManager& other);
    FinanceManager& operator=(const FinanceManager& other) = delete;
    ~FinanceManager() = default;

    // Dodaje nowy dochód
    void addIncome(const std::string& date, const std::string& desc, double amt, IncomeType type);

    // Dodaje nowy wydatek
    void addExpense(const std::string& date, const std::string& desc, double amt, ExpenseType type);

    // Dodaje now¹ transakcjê (w³aœciciel obiektu zostaje przekazany do FinanceManagera)
    void addTransaction(Transaction* t);

    // Wypisuje transakcje na podany strumieñ (domyœlnie std::cout)
    void listTransactions() const;

    // Wypisuje transakcje w podanym zakresie dat
    void listTransactionsByDate(const std::string& startDate, const std::string& endDate) const;

    // Edytuje transakcjê na podanym indeksie
    bool editTransaction(int index, const std::string& newDate, const std::string& newDesc, double newAmt);

    // Usuwa transakcjê na podanym indeksie
    bool removeTransaction(int index);

    // Generuje raport finansowy za podany okres
    void generateReport(const std::string& startDate, const std::string& endDate) const;

    // Oblicza saldo (suma dochodów minus suma wydatków)
    double getBalance() const;

    // Zwraca sumê dla konkretnego typu dochodu
    double getIncomeTotal(IncomeType type) const;

    // Zwraca sumê dla konkretnego typu wydatku
    double getExpenseTotal(ExpenseType type) const;

    // Podsumowanie wed³ug kategorii
    void summarizeByCategory() const;

    // Zapisanie danych do pliku
    bool saveToDatabase() const;

    // Wczytanie danych z pliku
    bool loadFromDatabase();

    // Przeci¹¿enia operatorów do ³¹czenia danych finansowych
    FinanceManager operator+(const FinanceManager& other) const;
    FinanceManager& operator+=(const FinanceManager& other);

    // Funkcja zaprzyjaŸniona – umo¿liwia wypisanie stanu menad¿era finansów
    friend std::ostream& operator<<(std::ostream& os, const FinanceManager& fm);

    // Nowa metoda zwracaj¹ca listê transakcji
    const std::vector<std::unique_ptr<Transaction>>& getTransactions() const;
};

#endif // FINANCEMANAGER_H
