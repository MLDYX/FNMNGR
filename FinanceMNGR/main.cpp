#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <iomanip>
#include "FinanceManager.h"
#include "Transaction.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glfw3.h>

// Funkcja inicjalizujaca Dear ImGui
void initImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Wlacz nawigacje klawiatura
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

// Funkcja czyszczaca Dear ImGui
void cleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

// Funkcja do zbierania wyniku cout do stringa
std::string captureCout(const std::function<void()>& func) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

int main() {
    // Inicjalizacja GLFW
    if (!glfwInit()) {
        std::cerr << "Nie mozna zainicjalizowac GLFW" << std::endl;
        return -1;
    }

    // Tworzenie okna GLFW
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Personalny Menadzer Finansow", NULL, NULL);
    if (!window) {
        std::cerr << "Nie mozna utworzyc okna GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Inicjalizacja Dear ImGui
    initImGui(window);

    FinanceManager manager;
    enum class View {
        None,
        AddIncome,
        AddExpense,
        EditTransaction,
        RemoveTransaction,
        FilterTransactions,
        GenerateReport,
        DisplayTransactions,
        DisplayBalance,
        DisplaySummary
    };
    View currentView = View::None;
    std::string outputText = "";

    // Usuniecie domyslnego paska tytulowego ImGui
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Tworzenie pelnoekranowego dockspace
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("MainWindow", NULL, window_flags);
        ImGui::PopStyleVar(3);

        // Menu po lewej stronie
        ImGui::BeginChild("Menu", ImVec2(300, ImGui::GetContentRegionAvail().y), true);
        ImGui::Text("Personalny Menadzer Finansow");
        ImGui::Separator();
        ImGui::Text("Wybierz opcje:");
        ImGui::Separator();
        if (ImGui::Button("Dodaj dochod", ImVec2(280, 40))) {
            currentView = View::AddIncome;
        }
        if (ImGui::Button("Dodaj wydatek", ImVec2(280, 40))) {
            currentView = View::AddExpense;
        }
        if (ImGui::Button("Wyswietl transakcje", ImVec2(280, 40))) {
            currentView = View::DisplayTransactions;
            outputText = ""; // Czyszczenie wynikow
            if (manager.getTransactions().empty()) {
                outputText = "Brak transakcji.";
            }
            else {
                for (const auto& t : manager.getTransactions()) {
                    outputText += t->toCSV() + "\n";
                }
            }
        }
        if (ImGui::Button("Wyswietl saldo", ImVec2(280, 40))) {
            currentView = View::DisplayBalance;
            std::stringstream ss;
            ss << "Saldo: " << std::fixed << std::setprecision(2) << manager.getBalance() << " zl";
            outputText = ss.str();
        }
        if (ImGui::Button("Podsumowanie wedlug kategorii", ImVec2(280, 40))) {
            currentView = View::DisplaySummary;
            outputText = captureCout([&]() {
                manager.summarizeByCategory();
                });
        }
        if (ImGui::Button("Zapisz dane", ImVec2(280, 40))) {
            if (manager.saveToDatabase()) {
                ImGui::OpenPopup("Zapisano");
            }
            else {
                ImGui::OpenPopup("Blad zapisu");
            }
        }
        if (ImGui::Button("Edytuj transakcje", ImVec2(280, 40))) {
            currentView = View::EditTransaction;
        }
        if (ImGui::Button("Usun transakcje", ImVec2(280, 40))) {
            currentView = View::RemoveTransaction;
        }
        if (ImGui::Button("Filtruj transakcje wedlug daty", ImVec2(280, 40))) {
            currentView = View::FilterTransactions;
        }
        if (ImGui::Button("Generuj raport", ImVec2(280, 40))) {
            currentView = View::GenerateReport;
        }
        if (ImGui::Button("Wyjscie", ImVec2(280, 40))) break;
        ImGui::EndChild();

        // Opcje po prawej stronie
        ImGui::SameLine();
        ImGui::BeginChild("Opcje", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);

        // Okno dodawania dochodu
        if (currentView == View::AddIncome) {
            ImGui::Text("Dodaj dochod");
            ImGui::Separator();
            static char date[64] = "";
            static char desc[128] = "";
            static double amt = 0.0;
            static int typeChoice = 0;

            ImGui::InputText("Data", date, IM_ARRAYSIZE(date));
            ImGui::InputText("Opis", desc, IM_ARRAYSIZE(desc));
            ImGui::InputDouble("Kwota", &amt);
            ImGui::RadioButton("Praca", &typeChoice, 0);
            ImGui::RadioButton("Dodatkowy", &typeChoice, 1);

            if (ImGui::Button("Dodaj")) {
                IncomeType incomeType = typeChoice == 0 ? IncomeType::Work : IncomeType::Additional;
                manager.addIncome(date, desc, amt, incomeType);
                currentView = View::None;
                // Wyczysc pola po dodaniu
                memset(date, 0, sizeof(date));
                memset(desc, 0, sizeof(desc));
                amt = 0.0;
            }
        }

        // Okno dodawania wydatku
        else if (currentView == View::AddExpense) {
            ImGui::Text("Dodaj wydatek");
            ImGui::Separator();
            static char date[64] = "";
            static char desc[128] = "";
            static double amt = 0.0;
            static int typeChoice = 0;

            ImGui::InputText("Data", date, IM_ARRAYSIZE(date));
            ImGui::InputText("Opis", desc, IM_ARRAYSIZE(desc));
            ImGui::InputDouble("Kwota", &amt);
            ImGui::RadioButton("Rachunki", &typeChoice, 0);
            ImGui::RadioButton("Jedzenie", &typeChoice, 1);
            ImGui::RadioButton("Ubrania", &typeChoice, 2);
            ImGui::RadioButton("Inne", &typeChoice, 3);

            if (ImGui::Button("Dodaj")) {
                ExpenseType expenseType;
                switch (typeChoice) {
                case 0: expenseType = ExpenseType::Bills; break;
                case 1: expenseType = ExpenseType::Food; break;
                case 2: expenseType = ExpenseType::Clothes; break;
                default: expenseType = ExpenseType::Other; break;
                }
                manager.addExpense(date, desc, amt, expenseType);
                currentView = View::None;
                // Wyczysc pola po dodaniu
                memset(date, 0, sizeof(date));
                memset(desc, 0, sizeof(desc));
                amt = 0.0;
            }
        }

        // Okno edycji transakcji
        else if (currentView == View::EditTransaction) {
            ImGui::Text("Edytuj transakcje");
            ImGui::Separator();
            static int index = 0;
            static char newDate[64] = "";
            static char newDesc[128] = "";
            static double newAmt = 0.0;

            ImGui::InputInt("Indeks", &index);
            ImGui::InputText("Nowa data", newDate, IM_ARRAYSIZE(newDate));
            ImGui::InputText("Nowy opis", newDesc, IM_ARRAYSIZE(newDesc));
            ImGui::InputDouble("Nowa kwota", &newAmt);

            if (ImGui::Button("Edytuj")) {
                if (manager.editTransaction(index, newDate, newDesc, newAmt)) {
                    ImGui::Text("Transakcja zostala zaktualizowana.");
                }
                else {
                    ImGui::Text("Nieprawidlowy indeks transakcji.");
                }
                currentView = View::None;
            }
        }

        // Okno usuwania transakcji
        else if (currentView == View::RemoveTransaction) {
            ImGui::Text("Usun transakcje");
            ImGui::Separator();
            static int index = 0;

            ImGui::InputInt("Indeks", &index);

            if (ImGui::Button("Usun")) {
                if (manager.removeTransaction(index)) {
                    ImGui::Text("Transakcja zostala usunieta.");
                }
                else {
                    ImGui::Text("Nieprawidlowy indeks transakcji.");
                }
                currentView = View::None;
            }
        }

        // Okno filtrowania transakcji wedlug daty
        else if (currentView == View::FilterTransactions) {
            ImGui::Text("Filtruj transakcje wedlug daty");
            ImGui::Separator();
            static char startDate[64] = "";
            static char endDate[64] = "";

            ImGui::InputText("Data poczatkowa", startDate, IM_ARRAYSIZE(startDate));
            ImGui::InputText("Data koncowa", endDate, IM_ARRAYSIZE(endDate));

            if (ImGui::Button("Filtruj")) {
                outputText = captureCout([&]() {
                    manager.listTransactionsByDate(startDate, endDate);
                    });
                currentView = View::DisplayTransactions;
            }
        }

        // Okno generowania raportu
        else if (currentView == View::GenerateReport) {
            ImGui::Text("Generuj raport");
            ImGui::Separator();
            static char startDate[64] = "";
            static char endDate[64] = "";

            ImGui::InputText("Data poczatkowa", startDate, IM_ARRAYSIZE(startDate));
            ImGui::InputText("Data koncowa", endDate, IM_ARRAYSIZE(endDate));

            if (ImGui::Button("Generuj")) {
                outputText = captureCout([&]() {
                    manager.generateReport(startDate, endDate);
                    });
                currentView = View::DisplayTransactions;
            }
        }

        // Wyswietl transakcje
        else if (currentView == View::DisplayTransactions) {
            ImGui::Text("Lista Transakcji:");
            ImGui::Separator();
            ImGui::TextWrapped("%s", outputText.c_str());
        }

        // Wyswietl saldo
        else if (currentView == View::DisplayBalance) {
            ImGui::Text("Informacja o saldzie:");
            ImGui::Separator();
            ImGui::TextWrapped("%s", outputText.c_str());
        }

        // Wyswietl podsumowanie wedlug kategorii
        else if (currentView == View::DisplaySummary) {
            ImGui::Text("Podsumowanie wedlug kategorii:");
            ImGui::Separator();
            ImGui::TextWrapped("%s", outputText.c_str());
        }

        else {
            ImGui::Text("Witaj w Personalnym Menadzerze Finansow!");
            ImGui::Text("Wybierz opcje z menu po lewej stronie.");
        }

        ImGui::EndChild();

        // Popupy
        if (ImGui::BeginPopup("Lista Transakcji")) {
            ImGui::Text("Lista Transakcji:");
            ImGui::Separator();
            if (manager.getTransactions().empty()) {
                ImGui::Text("Brak transakcji.");
            }
            else {
                for (const auto& t : manager.getTransactions()) {
                    ImGui::Text("%s", t->toCSV().c_str());
                }
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("Saldo")) {
            ImGui::Text("Saldo: %.2f", manager.getBalance());
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("Zapisano")) {
            ImGui::Text("Dane zostaly zapisane pomyslnie.");
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("Blad zapisu")) {
            ImGui::Text("Wystapil blad podczas zapisywania danych.");
            ImGui::EndPopup();
        }

        ImGui::End();

        // Renderowanie Dear ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Czyszczenie Dear ImGui
    cleanupImGui();

    // Czyszczenie GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
