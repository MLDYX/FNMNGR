#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <iomanip>
#include <algorithm>
#include "FinanceManager.h"
#include "Transaction.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glfw3.h>
#include <ctime>
#include <fstream>
#include <vector>


void setMBankStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    ImVec4 mBankRed = ImVec4(0.85f, 0.09f, 0.18f, 1.00f);        // Czerwony mBank
    ImVec4 mBankRedLight = ImVec4(0.95f, 0.19f, 0.28f, 1.00f);    // Jaœniejszy czerwony
    ImVec4 mBankRedDark = ImVec4(0.75f, 0.05f, 0.12f, 1.00f);     // Ciemniejszy czerwony
    ImVec4 mBankGray = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);        // Ciemny szary
    ImVec4 mBankLightGray = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);   // Jasny szary
    ImVec4 textColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);        // Bia³y tekst
    ImVec4 textDarkColor = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);    // Ciemny tekst
    ImVec4 bgColor = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);          // T³o - ciemny grafit

    // G³ówne kolory
    colors[ImGuiCol_Text] = textColor;
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg] = bgColor;
    colors[ImGuiCol_ChildBg] = ImVec4(0.16f, 0.17f, 0.20f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.15f, 0.16f, 0.19f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.27f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.20f, 0.25f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.24f, 0.29f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.28f, 0.32f, 1.00f);
    colors[ImGuiCol_TitleBg] = mBankRedDark;
    colors[ImGuiCol_TitleBgActive] = mBankRed;
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.15f, 0.15f, 0.15f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);

    // Przyciski - w stylu mBank (czerwone)
    colors[ImGuiCol_Button] = mBankRed;
    colors[ImGuiCol_ButtonHovered] = mBankRedLight;
    colors[ImGuiCol_ButtonActive] = mBankRedDark;

    // Nag³ówki - w stylu mBank
    colors[ImGuiCol_Header] = mBankRed;
    colors[ImGuiCol_HeaderHovered] = mBankRedLight;
    colors[ImGuiCol_HeaderActive] = mBankRedDark;

    // Zak³adki
    colors[ImGuiCol_Tab] = mBankRedDark;
    colors[ImGuiCol_TabHovered] = mBankRed;
    colors[ImGuiCol_TabActive] = mBankRedLight;
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

    // Pasek przewijania
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = mBankRed;
    colors[ImGuiCol_SliderGrab] = mBankRed;
    colors[ImGuiCol_SliderGrabActive] = mBankRedDark;

    // Pozosta³e elementy
    colors[ImGuiCol_Separator] = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.53f, 0.55f, 0.57f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = mBankRed;
    colors[ImGuiCol_ResizeGripHovered] = mBankRedLight;
    colors[ImGuiCol_ResizeGripActive] = mBankRedDark;
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = mBankRed;
    colors[ImGuiCol_PlotHistogram] = mBankRed;
    colors[ImGuiCol_PlotHistogramHovered] = mBankRedLight;
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

    // Zaokr¹glenia i marginesy dla nowoczesnego wygl¹du
    style.FrameRounding = 4.0f;        // Zaokr¹glone ramki
    style.GrabRounding = 4.0f;         // Zaokr¹glone slidery
    style.WindowRounding = 6.0f;       // Zaokr¹glone okna
    style.ChildRounding = 4.0f;        // Zaokr¹glone panele
    style.PopupRounding = 4.0f;        // Zaokr¹glone menu
    style.ScrollbarRounding = 9.0f;    // Zaokr¹glone scrollbary
    style.TabRounding = 4.0f;          // Zaokr¹glone zak³adki

    // Dodatkowe marginesy dla lepszej czytelnoœci
    style.WindowPadding = ImVec2(12.0f, 12.0f);
    style.FramePadding = ImVec2(8.0f, 6.0f);
    style.ItemSpacing = ImVec2(10.0f, 6.0f);
    style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
    style.TouchExtraPadding = ImVec2(2.0f, 2.0f);

    // Inne ustawienia
    style.IndentSpacing = 22.0f;
    style.ScrollbarSize = 14.0f;
    style.GrabMinSize = 10.0f;

    // Odstêpy w menu
    style.DisplayWindowPadding = ImVec2(22.0f, 22.0f);
    style.DisplaySafeAreaPadding = ImVec2(4.0f, 4.0f);
}

// Funkcja pomocnicza do rysowania wykresu salda
void plotBalanceHistory(const FinanceManager& manager) {
    const auto& transactions = manager.getTransactions();
    if (transactions.empty()) {
        ImGui::Text("Brak danych do wykresu.");
        return;
    }

    // Zbieramy dane o saldzie w czasie
    std::vector<float> balanceValues;
    std::vector<std::string> dates;
    float cumulativeBalance = 0.0f;

    for (const auto& t : transactions) {
        if (t->getType() == "Dochod") {
            cumulativeBalance += static_cast<float>(t->getAmount());
        }
        else {
            cumulativeBalance -= static_cast<float>(t->getAmount());
        }
        balanceValues.push_back(cumulativeBalance);
        dates.push_back(t->getDate());
    }

    // Rysujemy wykres
    ImGui::PlotLines("##BalanceHistory", balanceValues.data(), static_cast<int>(balanceValues.size()),
        0, "Saldo w czasie",
        *std::min_element(balanceValues.begin(), balanceValues.end()),
        *std::max_element(balanceValues.begin(), balanceValues.end()),
        ImVec2(ImGui::GetContentRegionAvail().x, 200));

    // Wyswietlamy daty pod wykresem
    if (!dates.empty()) {
        ImGui::Text("Od %s do %s", dates.front().c_str(), dates.back().c_str());
    }
}

// Funkcja inicjalizujaca Dear ImGui
void initImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    setMBankStyle();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

// Funkcja czyszczaca Dear ImGui
void cleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

// Bezpieczna funkcja kopiowania ci¹gów znaków
void safeStrCopy(char* dest, const char* src, size_t destSize) {
    size_t i;
    for (i = 0; i < destSize - 1 && src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

// Funkcja do zbierania wyniku cout do stringa
std::string captureCout(const std::function<void()>& func) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

std::string addMonths(const std::string& date, int months) {
    int d, m, y;
    sscanf_s(date.c_str(), "%d.%d.%d", &d, &m, &y);
    m += months;
    while (m > 12) { m -= 12; y++; }
    char buf[16];
    snprintf(buf, sizeof(buf), "%02d.%02d.%04d", d, m, y);
    return std::string(buf);
}

void processStandingOrders(FinanceManager& manager, const std::string& standingOrdersFile) {
    struct StandingOrder {
        std::string startDate, type, category, desc;
        double amount;
    };
    std::vector<StandingOrder> standingOrders;
    std::ifstream f(standingOrdersFile);
    std::string line;
    while (std::getline(f, line)) {
        std::istringstream iss(line);
        std::string startDate, type, category, desc, amountStr;
        if (std::getline(iss, startDate, ',') &&
            std::getline(iss, type, ',') &&
            std::getline(iss, category, ',') &&
            std::getline(iss, desc, ',') &&
            std::getline(iss, amountStr)) {
            standingOrders.push_back({ startDate, type, category, desc, std::stod(amountStr) });
        }
    }

    auto getLastTransactionDate = [&manager]() -> std::string {
        const auto& txs = manager.getTransactions();
        if (txs.empty()) return "";
        std::string maxDate = txs.front()->getDate();
        for (const auto& t : txs) {
            if (t->getDate() > maxDate) maxDate = t->getDate();
        }
        return maxDate;
        };

    std::string lastDate = getLastTransactionDate();
    for (const auto& so : standingOrders) {
        if (lastDate.empty() || lastDate < so.startDate) continue;
        int d1, m1, y1, d2, m2, y2;
        sscanf_s(so.startDate.c_str(), "%d.%d.%d", &d1, &m1, &y1);
        sscanf_s(lastDate.c_str(), "%d.%d.%d", &d2, &m2, &y2);
        int monthsPassed = (y2 - y1) * 12 + (m2 - m1);

        for (int i = 0; i <= monthsPassed; ++i) {
            std::string txDate = addMonths(so.startDate, i);
            // SprawdŸ, czy ju¿ istnieje transakcja o tej dacie, opisie i kwocie
            bool exists = false;
            for (const auto& t : manager.getTransactions()) {
                if (t->getDate() == txDate && t->getDescription() == so.desc && t->getAmount() == so.amount) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                if (so.type == "Przychod") {
                    IncomeType typ = (so.category == "Praca") ? IncomeType::Work : IncomeType::Additional;
                    manager.addIncome(txDate, so.desc, so.amount, typ);
                }
                else {
                    ExpenseType typ;
                    if (so.category == "Rachunki") typ = ExpenseType::Bills;
                    else if (so.category == "Jedzenie") typ = ExpenseType::Food;
                    else if (so.category == "Ubrania") typ = ExpenseType::Clothes;
                    else typ = ExpenseType::Other;
                    manager.addExpense(txDate, so.desc, so.amount, typ);
                }
            }
        }
    }
    manager.saveToDatabase();
}



int main() {
    // Inicjalizacja GLFW

    if (!glfwInit()) {
        std::cerr << "Nie mozna zainicjalizowac GLFW" << std::endl;
        return -1;
    }

    // Tworzenie okna GLFW
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Personalny Menedzer Finansow", NULL, NULL);
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

	manager.loadFromDatabase();
    processStandingOrders(manager, "standing_orders.csv");

    // Zwraca datê najnowszej transakcji lub pusty string
    auto getLastTransactionDate = [&manager]() -> std::string {
        const auto& txs = manager.getTransactions();
        if (txs.empty()) return "";
        std::string maxDate = txs.front()->getDate();
        for (const auto& t : txs) {
            if (t->getDate() > maxDate) maxDate = t->getDate();
        }
        return maxDate;
    };

    // Wczytaj zlecenia sta³e z pliku
    struct StandingOrder {
        std::string startDate, type, category, desc;
        double amount;
    };
    std::vector<StandingOrder> standingOrders;
    {
        std::ifstream f("standing_orders.csv");
        std::string line;
        while (std::getline(f, line)) {
            std::istringstream iss(line);
            std::string startDate, type, category, desc, amountStr;
            if (std::getline(iss, startDate, ',') &&
                std::getline(iss, type, ',') &&
                std::getline(iss, category, ',') &&
                std::getline(iss, desc, ',') &&
                std::getline(iss, amountStr)) {
                standingOrders.push_back({ startDate, type, category, desc, std::stod(amountStr) });
            }
        }
    }

    // Dodaj brakuj¹ce transakcje zleceñ sta³ych
    std::string lastDate = getLastTransactionDate();
    for (const auto& so : standingOrders) {
        if (lastDate.empty() || lastDate < so.startDate) continue;
        // Oblicz ile miesiêcy minê³o od startDate do lastDate
        int d1, m1, y1, d2, m2, y2;
        sscanf_s(so.startDate.c_str(), "%d.%d.%d", &d1, &m1, &y1);
        sscanf_s(lastDate.c_str(), "%d.%d.%d", &d2, &m2, &y2);
        int monthsPassed = (y2 - y1) * 12 + (m2 - m1);
        // SprawdŸ, ile ju¿ jest transakcji tego zlecenia
        int alreadyAdded = 0;
        for (const auto& t : manager.getTransactions()) {
            if (t->getDescription() == so.desc && t->getAmount() == so.amount && t->getDate() >= so.startDate) {
                alreadyAdded++;
            }
        }
        for (int i = alreadyAdded; i <= monthsPassed; ++i) {
            std::string txDate = addMonths(so.startDate, i);
            if (so.type == "Przychod") {
                IncomeType typ = (so.category == "Praca") ? IncomeType::Work : IncomeType::Additional;
                manager.addIncome(txDate, so.desc, so.amount, typ);
            }
            else {
                ExpenseType typ;
                if (so.category == "Rachunki") typ = ExpenseType::Bills;
                else if (so.category == "Jedzenie") typ = ExpenseType::Food;
                else if (so.category == "Ubrania") typ = ExpenseType::Clothes;
                else typ = ExpenseType::Other;
                manager.addExpense(txDate, so.desc, so.amount, typ);
            }
        }
    }
    manager.saveToDatabase();


    enum class View {
        Home,
        Transactions,
        AddIncome,
        AddExpense,
        GenerateReport,
        DisplaySummary,
		AddStandingOrder
    };
    View currentView = View::Home; 
    std::string outputText = "";

    // Zmienne do edycji transakcji
    static int selectedIndex = -1;
    static char editDate[64] = "";
    static char editDesc[128] = "";
    static double editAmt = 0.0;
    static bool showEditPopup = false;
    static bool showDeleteConfirmation = false;
    static bool showFilterOptions = false;

    // Zmienne do filtrowania
    static char filterStartDate[64] = "";
    static char filterEndDate[64] = "";
    static bool filterActive = false;

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

        // Stylowy naglowek menu
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.00f));
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Personalny Menedzer Finansow").x) / 2);
        ImGui::Text("Personalny Menedzer Finansow");
        ImGui::PopStyleColor();

        // Stylowy separator
        ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
        ImGui::Separator();
        ImGui::PopStyleColor();

        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Wybierz opcje:").x) / 2);
        ImGui::Text("Wybierz opcje:");

        // Stylowy separator
        ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
        ImGui::Separator();
        ImGui::PopStyleColor();

        // Przyciski menu
        if (ImGui::Button("Strona Glowna", ImVec2(280, 40))) {
            currentView = View::Home;
        }
        if (ImGui::Button("Transakcje", ImVec2(280, 40))) {
            currentView = View::Transactions;
            filterActive = false;
            memset(filterStartDate, 0, sizeof(filterStartDate));
            memset(filterEndDate, 0, sizeof(filterEndDate));
        }
        if (ImGui::Button("Dodaj dochod", ImVec2(280, 40))) {
            currentView = View::AddIncome;
        }
        if (ImGui::Button("Dodaj wydatek", ImVec2(280, 40))) {
            currentView = View::AddExpense;
        }
        if (ImGui::Button("Dodaj Zlecenie Stale", ImVec2(280, 40))) {
            currentView = View::AddStandingOrder;
        }
        if (ImGui::Button("Podsumowanie wedlug kategorii", ImVec2(280, 40))) {
            currentView = View::DisplaySummary;
        }
        if (ImGui::Button("Generuj raport", ImVec2(280, 40))) {
            currentView = View::GenerateReport;
        }
        if (ImGui::Button("Wyjscie", ImVec2(280, 40))) break;
        ImGui::EndChild();

        // Opcje po prawej stronie
        ImGui::SameLine();
        ImGui::BeginChild("Opcje", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
        // Strona glowna
        if (currentView == View::Home) {
            // Sekcja gorna - Saldo
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.00f));
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Aktualne Saldo").x) / 2);
            ImGui::Text("Aktualne Saldo");
            ImGui::PopStyleColor();

            // Stylowy separator
            ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::Separator();
            ImGui::PopStyleColor();

            // Wartosc salda
            double balance = manager.getBalance();
            ImVec4 balanceColor = balance >= 0 ?
                ImVec4(0.10f, 0.74f, 0.61f, 1.00f) :
                ImVec4(0.85f, 0.09f, 0.18f, 1.00f);

            ImGui::PushStyleColor(ImGuiCol_Text, balanceColor);
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << balance;
            std::string balanceText = ss.str() + " zl";
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(balanceText.c_str()).x) / 2);
            ImGui::Text("%s", balanceText.c_str());
            ImGui::PopStyleColor();

            ImGui::Spacing();
            ImGui::Spacing();

            // Sekcja srodkowa - Ostatnie transakcje
            const float childWidth = (ImGui::GetContentRegionAvail().x - 10.0f) / 2.0f;

            // Ostatnie dochody (lewa strona)
            ImGui::BeginChild("OstatnieDochody", ImVec2(childWidth, 200), true);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
            ImGui::Text("Ostatnie Dochody");
            ImGui::PopStyleColor();
            ImGui::Separator();

            // Wyswietl liste ostatnich dochodow
            int incomeCount = 0;
            for (auto it = manager.getTransactions().rbegin(); it != manager.getTransactions().rend() && incomeCount < 5; ++it) {
                if ((*it)->getType() == "Dochod") {
                    ImGui::Text("%s | %s", (*it)->getDate().c_str(), (*it)->getDescription().c_str());
                    ImGui::SameLine(ImGui::GetWindowWidth() - 100);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
                    ImGui::Text("%.2f zl", (*it)->getAmount());
                    ImGui::PopStyleColor();
                    incomeCount++;
                }
            }
            if (incomeCount == 0) {
                ImGui::Text("Brak ostatnich dochodow");
            }
            ImGui::EndChild();

            // Ostatnie wydatki (prawa strona)
            ImGui::SameLine();
            ImGui::BeginChild("OstatnieWydatki", ImVec2(childWidth, 200), true);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::Text("Ostatnie Wydatki");
            ImGui::PopStyleColor();
            ImGui::Separator();

            // Wyswietl liste ostatnich wydatkow
            int expenseCount = 0;
            for (auto it = manager.getTransactions().rbegin(); it != manager.getTransactions().rend() && expenseCount < 5; ++it) {
                if ((*it)->getType() == "Wydatek") {
                    ImGui::Text("%s | %s", (*it)->getDate().c_str(), (*it)->getDescription().c_str());
                    ImGui::SameLine(ImGui::GetWindowWidth() - 100);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                    ImGui::Text("%.2f zl", (*it)->getAmount());
                    ImGui::PopStyleColor();
                    expenseCount++;
                }
            }
            if (expenseCount == 0) {
                ImGui::Text("Brak ostatnich wydatkow");
            }
            ImGui::EndChild();

            ImGui::Spacing();
            ImGui::Spacing();

            // Sekcja dolna - Wykres salda
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.00f));
            ImGui::Text("Historia Salda");
            ImGui::PopStyleColor();
            ImGui::Separator();

            // Wykres
            plotBalanceHistory(manager);

            ImGui::Spacing();
            ImGui::Spacing();

            // Sekcja z tabelka wszystkich transakcji
            ImGui::Text("Wszystkie Transakcje");
            ImGui::Separator();

            // Tabela transakcji
            if (ImGui::BeginTable("TransactionTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable)) {
                // Naglowki
                ImGui::TableSetupColumn("Data");
                ImGui::TableSetupColumn("Typ");
                ImGui::TableSetupColumn("Kategoria");
                ImGui::TableSetupColumn("Opis");
                ImGui::TableSetupColumn("Kwota");
                ImGui::TableHeadersRow();

                // Dane
                for (int i = 0; i < manager.getTransactions().size(); i++) {
                    const auto& transaction = manager.getTransactions()[i];
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%s", transaction->getDate().c_str());

                    ImGui::TableSetColumnIndex(1);
                    if (transaction->getType() == "Dochod") {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
                        ImGui::Text("%s", transaction->getType().c_str());
                        ImGui::PopStyleColor();
                    }
                    else {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                        ImGui::Text("%s", transaction->getType().c_str());
                        ImGui::PopStyleColor();
                    }

                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%s", transaction->getSubtype().c_str());

                    ImGui::TableSetColumnIndex(3);
                    ImGui::Text("%s", transaction->getDescription().c_str());

                    ImGui::TableSetColumnIndex(4);
                    if (transaction->getType() == "Dochod") {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
                        ImGui::Text("%.2f zl", transaction->getAmount());
                        ImGui::PopStyleColor();
                    }
                    else {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                        ImGui::Text("%.2f zl", transaction->getAmount());
                        ImGui::PopStyleColor();
                    }
                }

                ImGui::EndTable();
            }

            if (manager.getTransactions().empty()) {
                ImGui::Text("Brak transakcji do wyswietlenia");
            }
        }

        // Strona z transakcjami (po³¹czone: Wyœwietl/Edytuj/Usuñ transakcje)
        else if (currentView == View::Transactions) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.00f));
            ImGui::Text("Transakcje");
            ImGui::PopStyleColor();
            ImGui::Separator();

            // Opcje filtrowania
            if (ImGui::Button("Filtry")) {
                showFilterOptions = !showFilterOptions;
            }

            if (showFilterOptions) {
                ImGui::BeginChild("FilterOptions", ImVec2(ImGui::GetContentRegionAvail().x, 80), true);
                ImGui::Text("Filtruj transakcje wedlug daty:");

                ImGui::InputText("Data poczatkowa", filterStartDate, IM_ARRAYSIZE(filterStartDate));
                ImGui::InputText("Data koncowa", filterEndDate, IM_ARRAYSIZE(filterEndDate));

                if (ImGui::Button("Zastosuj filtr")) {
                    filterActive = true;
                    showFilterOptions = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("Wyczysc filtr")) {
                    filterActive = false;
                    memset(filterStartDate, 0, sizeof(filterStartDate));
                    memset(filterEndDate, 0, sizeof(filterEndDate));
                    showFilterOptions = false;
                }

                ImGui::EndChild();
                ImGui::Spacing();
            }

            // Tabela transakcji z opcjami edycji/usuwania
            if (ImGui::BeginTable("TransactionsTable", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable)) {
                ImGui::TableSetupColumn("Indeks");
                ImGui::TableSetupColumn("Data");
                ImGui::TableSetupColumn("Typ");
                ImGui::TableSetupColumn("Kategoria");
                ImGui::TableSetupColumn("Opis");
                ImGui::TableSetupColumn("Kwota");
                ImGui::TableSetupColumn("Akcje");
                ImGui::TableHeadersRow();

                // Dane
                int visibleIndex = 0;
                for (int i = 0; i < manager.getTransactions().size(); i++) {
                    const auto& transaction = manager.getTransactions()[i];

                    // SprawdŸ filtr daty jeœli jest aktywny
                    if (filterActive) {
                        if (!filterStartDate[0] && !filterEndDate[0]) {
                            // Brak filtrów - poka¿ wszystko
                        }
                        else if (filterStartDate[0] && !filterEndDate[0]) {
                            // Tylko pocz¹tkowa data
                            if (transaction->getDate() < filterStartDate) continue;
                        }
                        else if (!filterStartDate[0] && filterEndDate[0]) {
                            // Tylko koñcowa data
                            if (transaction->getDate() > filterEndDate) continue;
                        }
                        else {
                            // Obydwie daty
                            if (transaction->getDate() < filterStartDate || transaction->getDate() > filterEndDate) continue;
                        }
                    }

                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%d", i);

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%s", transaction->getDate().c_str());

                    ImGui::TableSetColumnIndex(2);
                    if (transaction->getType() == "Dochod") {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
                        ImGui::Text("%s", transaction->getType().c_str());
                        ImGui::PopStyleColor();
                    }
                    else {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                        ImGui::Text("%s", transaction->getType().c_str());
                        ImGui::PopStyleColor();
                    }

                    ImGui::TableSetColumnIndex(3);
                    ImGui::Text("%s", transaction->getSubtype().c_str());

                    ImGui::TableSetColumnIndex(4);
                    ImGui::Text("%s", transaction->getDescription().c_str());

                    ImGui::TableSetColumnIndex(5);
                    if (transaction->getType() == "Dochod") {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
                        ImGui::Text("%.2f zl", transaction->getAmount());
                        ImGui::PopStyleColor();
                    }
                    else {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                        ImGui::Text("%.2f zl", transaction->getAmount());
                        ImGui::PopStyleColor();
                    }

                    // Kolumna z przyciskami akcji
                    ImGui::TableSetColumnIndex(6);
                    ImGui::PushID(i);
                    if (ImGui::Button("Edytuj")) {
                        selectedIndex = i;
                        safeStrCopy(editDate, transaction->getDate().c_str(), sizeof(editDate));
                        safeStrCopy(editDesc, transaction->getDescription().c_str(), sizeof(editDesc));
                        editAmt = transaction->getAmount();
                        showEditPopup = true;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Usun")) {
                        selectedIndex = i;
                        showDeleteConfirmation = true;
                    }
                    ImGui::PopID();

                    visibleIndex++;
                }

                ImGui::EndTable();
            }

            if (manager.getTransactions().empty()) {
                ImGui::Text("Brak transakcji do wyswietlenia");
            }
        }

        // Okno dodawania dochodu
        else if (currentView == View::AddIncome) {
            // Stylowy nag³ówek
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Dodaj Dochod").x) / 2);
            ImGui::Text("Dodaj Dochod");
            ImGui::PopStyleColor();

            // Stylowy separator
            ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
            ImGui::Separator();
            ImGui::PopStyleColor();

            ImGui::Spacing();
            ImGui::Spacing();

            // Zmienne do przechowywania danych
            static char date[64] = "";
            static char desc[128] = "";
            static double amt = 0.0;
            static int typeChoice = 0;

            // Centralna sekcja formularza
            const float formWidth = ImGui::GetWindowWidth() * 0.7f;
            const float leftIndent = (ImGui::GetWindowWidth() - formWidth) * 0.5f;

            // Data - wyœrodkowana
            ImGui::SetCursorPosX(leftIndent);
            ImGui::Text("Data:");
            ImGui::SameLine(leftIndent + 150);
            ImGui::PushItemWidth(formWidth - 150);
            ImGui::InputText("##Date", date, IM_ARRAYSIZE(date));
            ImGui::PopItemWidth();

            ImGui::Spacing();

            // Opis - wyœrodkowany
            ImGui::SetCursorPosX(leftIndent);
            ImGui::Text("Opis:");
            ImGui::SameLine(leftIndent + 150);
            ImGui::PushItemWidth(formWidth - 150);
            ImGui::InputText("##Desc", desc, IM_ARRAYSIZE(desc));
            ImGui::PopItemWidth();

            ImGui::Spacing();

            // Kwota - wyœrodkowana
            ImGui::SetCursorPosX(leftIndent);
            ImGui::Text("Kwota:");
            ImGui::SameLine(leftIndent + 150);
            ImGui::PushItemWidth(formWidth - 150);
            ImGui::InputDouble("##Amount", &amt, 0.0, 0.0, "%.2f");
            ImGui::PopItemWidth();

            ImGui::Spacing();
            ImGui::Spacing();

            // Wybór kategorii - wyœrodkowany w formularzu
            ImGui::SetCursorPosX(leftIndent + (formWidth - ImGui::CalcTextSize("Kategoria:").x) / 2);
            ImGui::Text("Kategoria:");

            ImGui::Spacing();

            // Przyciski radio wyœrodkowane
            float radioButtonWidth = ImGui::CalcTextSize("Dodatkowy").x + 30.0f;
            float radioIndent = leftIndent + (formWidth - radioButtonWidth * 2) / 2;

            ImGui::SetCursorPosX(radioIndent);
            ImGui::RadioButton("Praca", &typeChoice, 0);
            ImGui::SameLine(radioIndent + radioButtonWidth);
            ImGui::RadioButton("Dodatkowy", &typeChoice, 1);

            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();

            // Przycisk "Dodaj" - du¿y i wyœrodkowany
            const float buttonWidth = 200.0f;
            const float buttonHeight = 50.0f;
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - buttonWidth) * 0.5f);
            if (ImGui::Button("Dodaj", ImVec2(buttonWidth, buttonHeight))) {
                IncomeType incomeType = typeChoice == 0 ? IncomeType::Work : IncomeType::Additional;
                manager.addIncome(date, desc, amt, incomeType);
                // Automatyczne zapisanie po dodaniu
                manager.saveToDatabase();

                std::string newDate(date);
                std::string lastDate = getLastTransactionDate();
                if (newDate > lastDate) {
                    processStandingOrders(manager, "standing_orders.csv");
                }
                // Przejœcie do strony g³ównej
                currentView = View::Home;
                // Wyczyszczenie pól
                memset(date, 0, sizeof(date));
                memset(desc, 0, sizeof(desc));
                amt = 0.0;
            }
        }

        // Okno dodawania wydatku
        else if (currentView == View::AddExpense) {
            // Stylowy nag³ówek
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Dodaj Wydatek").x) / 2);
            ImGui::Text("Dodaj Wydatek");
            ImGui::PopStyleColor();

            // Stylowy separator
            ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::Separator();
            ImGui::PopStyleColor();

            ImGui::Spacing();
            ImGui::Spacing();

            // Zmienne do przechowywania danych
            static char date[64] = "";
            static char desc[128] = "";
            static double amt = 0.0;
            static int typeChoice = 0;

            // Centralna sekcja formularza
            const float formWidth = ImGui::GetWindowWidth() * 0.7f;
            const float leftIndent = (ImGui::GetWindowWidth() - formWidth) * 0.5f;

            // Data - wyœrodkowana
            ImGui::SetCursorPosX(leftIndent);
            ImGui::Text("Data:");
            ImGui::SameLine(leftIndent + 150);
            ImGui::PushItemWidth(formWidth - 150);
            ImGui::InputText("##Date", date, IM_ARRAYSIZE(date));
            ImGui::PopItemWidth();

            ImGui::Spacing();

            // Opis - wyœrodkowany
            ImGui::SetCursorPosX(leftIndent);
            ImGui::Text("Opis:");
            ImGui::SameLine(leftIndent + 150);
            ImGui::PushItemWidth(formWidth - 150);
            ImGui::InputText("##Desc", desc, IM_ARRAYSIZE(desc));
            ImGui::PopItemWidth();

            ImGui::Spacing();

            // Kwota - wyœrodkowana
            ImGui::SetCursorPosX(leftIndent);
            ImGui::Text("Kwota:");
            ImGui::SameLine(leftIndent + 150);
            ImGui::PushItemWidth(formWidth - 150);
            ImGui::InputDouble("##Amount", &amt, 0.0, 0.0, "%.2f");
            ImGui::PopItemWidth();

            ImGui::Spacing();
            ImGui::Spacing();

            // Wybór kategorii - wyœrodkowany w formularzu
            ImGui::SetCursorPosX(leftIndent + (formWidth - ImGui::CalcTextSize("Kategoria:").x) / 2);
            ImGui::Text("Kategoria:");

            ImGui::Spacing();

            // Przyciski radio - 2 wiersze po 2 przyciski, wyœrodkowane
            float radioButtonWidth = ImGui::CalcTextSize("Rachunki").x + 30.0f;
            float radioWidth2 = ImGui::CalcTextSize("Jedzenie").x + 30.0f;
            float radioMaxWidth = std::max(radioButtonWidth, radioWidth2);
            float radioIndent = leftIndent + (formWidth - radioMaxWidth * 2) / 2;

            // Pierwszy wiersz
            ImGui::SetCursorPosX(radioIndent);
            ImGui::RadioButton("Rachunki", &typeChoice, 0);
            ImGui::SameLine(radioIndent + radioMaxWidth);
            ImGui::RadioButton("Jedzenie", &typeChoice, 1);

            // Drugi wiersz
            ImGui::SetCursorPosX(radioIndent);
            ImGui::RadioButton("Ubrania", &typeChoice, 2);
            ImGui::SameLine(radioIndent + radioMaxWidth);
            ImGui::RadioButton("Inne", &typeChoice, 3);

            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();

            // Przycisk "Dodaj" - du¿y i wyœrodkowany
            const float buttonWidth = 200.0f;
            const float buttonHeight = 50.0f;
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - buttonWidth) * 0.5f);
            if (ImGui::Button("Dodaj", ImVec2(buttonWidth, buttonHeight))) {
                ExpenseType expenseType;
                switch (typeChoice) {
                case 0: expenseType = ExpenseType::Bills; break;
                case 1: expenseType = ExpenseType::Food; break;
                case 2: expenseType = ExpenseType::Clothes; break;
                default: expenseType = ExpenseType::Other; break;
                }
                manager.addExpense(date, desc, amt, expenseType);
                // Automatyczne zapisanie po dodaniu
                manager.saveToDatabase();

                std::string newDate(date);
                std::string lastDate = getLastTransactionDate();
                if (newDate > lastDate) {
                    processStandingOrders(manager, "standing_orders.csv");
                }
                // Przejœcie do strony g³ównej
                currentView = View::Home;
                // Wyczyszczenie pól
                memset(date, 0, sizeof(date));
                memset(desc, 0, sizeof(desc));
                amt = 0.0;
            }
        }

        else if (currentView == View::AddStandingOrder) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.00f));
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Dodaj Zlecenie Stale").x) / 2);
            ImGui::Text("Dodaj Zlecenie Stale");
            ImGui::PopStyleColor();

            ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::Separator();
            ImGui::PopStyleColor();

            ImGui::Spacing();
            ImGui::Spacing();

            // Zmienne statyczne do formularza
            static int typZlecenia = 0;
            static int kategoriaPrzychod = 0;
            static int kategoriaWydatek = 0;
            static char opis[128] = "";
            static double kwota = 0.0;
            static bool showStandingOrderAdded = false;

            // Wyœrodkowanie formularza
            const float formWidth = 400.0f;
            const float formStartX = (ImGui::GetWindowWidth() - formWidth) * 0.5f;

            ImGui::SetCursorPosX(formStartX);
            ImGui::BeginChild("StandingOrderForm", ImVec2(formWidth, 0), false);

            // Wybór typu zlecenia
            ImGui::SetCursorPosX((formWidth - ImGui::CalcTextSize("Przychod   Wydatek").x) / 2);
            ImGui::RadioButton("Przychod", &typZlecenia, 0); ImGui::SameLine();
            ImGui::RadioButton("Wydatek", &typZlecenia, 1);

            ImGui::Spacing();

            // Wybór kategorii
            if (typZlecenia == 0) {
                ImGui::SetCursorPosX((formWidth - ImGui::CalcTextSize("Kategoria przychodu:").x) / 2);
                ImGui::Text("Kategoria przychodu:");
                ImGui::SetCursorPosX((formWidth - ImGui::CalcTextSize("Praca   Dodatkowy").x) / 2);
                ImGui::RadioButton("Praca", &kategoriaPrzychod, 0); ImGui::SameLine();
                ImGui::RadioButton("Dodatkowy", &kategoriaPrzychod, 1);
            }
            else {
                ImGui::SetCursorPosX((formWidth - ImGui::CalcTextSize("Kategoria wydatku:").x) / 2);
                ImGui::Text("Kategoria wydatku:");
                ImGui::SetCursorPosX((formWidth - ImGui::CalcTextSize("Rachunki   Jedzenie").x) / 2);
                ImGui::RadioButton("Rachunki", &kategoriaWydatek, 0); ImGui::SameLine();
                ImGui::RadioButton("Jedzenie", &kategoriaWydatek, 1);
                ImGui::SetCursorPosX((formWidth - ImGui::CalcTextSize("Ubrania   Inne").x) / 2);
                ImGui::RadioButton("Ubrania", &kategoriaWydatek, 2); ImGui::SameLine();
                ImGui::RadioButton("Inne", &kategoriaWydatek, 3);
            }

            ImGui::Spacing();

            // Opis
            ImGui::SetCursorPosX((formWidth - ImGui::CalcTextSize("Opis:").x) / 2);
            ImGui::Text("Opis:");
            ImGui::SetCursorPosX((formWidth - 300) / 2);
            ImGui::PushItemWidth(300);
            ImGui::InputText("##OpisZlecenie", opis, IM_ARRAYSIZE(opis));
            ImGui::PopItemWidth();

            ImGui::Spacing();

            // Kwota
            ImGui::SetCursorPosX((formWidth - ImGui::CalcTextSize("Kwota:").x) / 2);
            ImGui::Text("Kwota:");
            ImGui::SetCursorPosX((formWidth - 150) / 2);
            ImGui::PushItemWidth(150);
            ImGui::InputDouble("##KwotaZlecenie", &kwota, 0.0, 0.0, "%.2f");
            ImGui::PopItemWidth();

            ImGui::Spacing();
            ImGui::Spacing();

            // Przycisk Dodaj (powiadomienie i zapis do pliku)
            ImGui::SetCursorPosX((formWidth - 200) / 2);
            if (ImGui::Button("Dodaj", ImVec2(200, 40))) {
                // Ustal typ i kategoriê
                std::string typ = (typZlecenia == 0) ? "Przychod" : "Wydatek";
                std::string kategoria;
                if (typZlecenia == 0)
                    kategoria = (kategoriaPrzychod == 0) ? "Praca" : "Dodatkowy";
                else {
                    switch (kategoriaWydatek) {
                    case 0: kategoria = "Rachunki"; break;
                    case 1: kategoria = "Jedzenie"; break;
                    case 2: kategoria = "Ubrania"; break;
                    default: kategoria = "Inne"; break;
                    }
                }

                // Pobierz dzisiejsz¹ datê jako startDate
                char dzis[32];
                std::time_t t = std::time(nullptr);
                std::tm tm_buf;
                localtime_s(&tm_buf, &t);
                std::strftime(dzis, sizeof(dzis), "%d.%m.%Y", &tm_buf);

                // Zapisz do pliku CSV
                std::ofstream f("standing_orders.csv", std::ios::app);
                if (f) {
                    f << dzis << "," << typ << "," << kategoria << "," << opis << "," << kwota << "\n";
                    f.close();
                    showStandingOrderAdded = true;
                    // Resetuj formularz
                    typZlecenia = 0; kategoriaPrzychod = 0; kategoriaWydatek = 0; kwota = 0.0; opis[0] = 0;
                }
            }


            // Przycisk Wykonaj (dodaje transakcjê)
            ImGui::SetCursorPosX((formWidth - 200) / 2);
            if (ImGui::Button("Wykonaj", ImVec2(200, 40))) {
                char dzis[32];
                std::time_t t = std::time(nullptr);
                std::tm tm_buf;
                localtime_s(&tm_buf, &t);
                std::strftime(dzis, sizeof(dzis), "%d.%m.%Y", &tm_buf);

                if (typZlecenia == 0) {
                    IncomeType typ = (kategoriaPrzychod == 0) ? IncomeType::Work : IncomeType::Additional;
                    manager.addIncome(dzis, opis, kwota, typ);
                }
                else {
                    ExpenseType typ;
                    switch (kategoriaWydatek) {
                    case 0: typ = ExpenseType::Bills; break;
                    case 1: typ = ExpenseType::Food; break;
                    case 2: typ = ExpenseType::Clothes; break;
                    default: typ = ExpenseType::Other; break;
                    }
                    manager.addExpense(dzis, opis, kwota, typ);
                }
                manager.saveToDatabase();
                // Resetuj formularz i wróæ do strony g³ównej
                typZlecenia = 0; kategoriaPrzychod = 0; kategoriaWydatek = 0; kwota = 0.0; opis[0] = 0;
                currentView = View::Home;
            }

            ImGui::EndChild();

            // Popup po klikniêciu Dodaj
            if (showStandingOrderAdded) {
                ImGui::OpenPopup("ZlecenieStaleDodane");
                showStandingOrderAdded = false;
            }
            if (ImGui::BeginPopupModal("ZlecenieStaleDodane", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Dodane zlecenie stale!");
                if (ImGui::Button("OK", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }



        // Okno generowania raportu
        else if (currentView == View::GenerateReport) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.00f));
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Generuj Raport Finansowy").x) / 2);
            ImGui::Text("Generuj Raport Finansowy");
            ImGui::PopStyleColor();

            ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::Separator();
            ImGui::PopStyleColor();

            ImGui::Spacing();
            ImGui::Spacing();

            static char startDate[64] = "";
            static char endDate[64] = "";

            // Centralna sekcja formularza
            const float formWidth = ImGui::GetWindowWidth();
            const float leftIndent = (ImGui::GetWindowWidth() - formWidth) * 0.5f;

            // Panel z datami
            ImGui::BeginChild("ReportDates", ImVec2(ImGui::GetContentRegionAvail().x, 120), true);

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.00f));
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Zakres dat raportu").x) / 2);
            ImGui::Text("Zakres dat raportu");
            ImGui::PopStyleColor();
            ImGui::Separator();

            // Data pocz¹tkowa
            ImGui::SetCursorPosX(20);
            ImGui::Text("Data poczatkowa:");
            ImGui::SameLine(ImGui::GetWindowWidth() - 220);
            ImGui::PushItemWidth(200);
            ImGui::InputText("##StartDate", startDate, IM_ARRAYSIZE(startDate));
            ImGui::PopItemWidth();

            ImGui::Spacing();

            // Data koñcowa
            ImGui::SetCursorPosX(20);
            ImGui::Text("Data koncowa:");
            ImGui::SameLine(ImGui::GetWindowWidth() - 220);
            ImGui::PushItemWidth(200);
            ImGui::InputText("##EndDate", endDate, IM_ARRAYSIZE(endDate));
            ImGui::PopItemWidth();

            ImGui::EndChild();

            ImGui::Spacing();
            ImGui::Spacing();

            // Przycisk "Generuj"
            const float buttonWidth = 200.0f;
            const float buttonHeight = 50.0f;
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - buttonWidth) * 0.5f);

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.15f, 0.84f, 0.71f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.05f, 0.64f, 0.51f, 1.00f));

            if (ImGui::Button("Generuj Raport", ImVec2(buttonWidth, buttonHeight))) {
                outputText = captureCout([&]() {
                    manager.generateReport(startDate, endDate);
                    });

                ImGui::OpenPopup("Raport");
            }
            ImGui::PopStyleColor(3);

            // Wizualizacja wyników dla podanego przedzia³u
            ImGui::Spacing();
            ImGui::Spacing();

            if (!manager.getTransactions().empty()) {
                // Podgl¹d danych
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.00f));
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Podglad danych").x) / 2);
                ImGui::Text("Podglad danych");
                ImGui::PopStyleColor();
                ImGui::Separator();

                // Wykres salda
                plotBalanceHistory(manager);
            }

            // Wyœwietlanie raportu jako popup z ³adnym formatowaniem
            if (ImGui::BeginPopupModal("Raport", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.00f));
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Raport Finansowy").x) / 2);
                ImGui::Text("Raport Finansowy");
                ImGui::PopStyleColor();

                ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                ImGui::Separator();
                ImGui::PopStyleColor();

                ImGui::BeginChild("ReportContent", ImVec2(500, 350), true);

                // Pobierz sumy
                double dochodPraca = manager.getIncomeTotal(IncomeType::Work);
                double dochodDodatkowe = manager.getIncomeTotal(IncomeType::Additional);
                double sumaDochodow = dochodPraca + dochodDodatkowe;

                double wydatekRachunki = manager.getExpenseTotal(ExpenseType::Bills);
                double wydatekJedzenie = manager.getExpenseTotal(ExpenseType::Food);
                double wydatekUbrania = manager.getExpenseTotal(ExpenseType::Clothes);
                double wydatekInne = manager.getExpenseTotal(ExpenseType::Other);
                double sumaWydatkow = wydatekRachunki + wydatekJedzenie + wydatekUbrania + wydatekInne;

                double saldo = sumaDochodow - sumaWydatkow;

                if (ImGui::BeginTable("RaportTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingStretchProp)) {
                    ImGui::TableSetupColumn("Kategoria");
                    ImGui::TableSetupColumn("Kwota");
                    ImGui::TableHeadersRow();

                    // Dochody
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("Praca");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
                    ImGui::Text("%.2f zl", dochodPraca);
                    ImGui::PopStyleColor();

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("Dodatkowe");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
                    ImGui::Text("%.2f zl", dochodDodatkowe);
                    ImGui::PopStyleColor();

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("Suma dochodow");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
                    ImGui::Text("%.2f zl", sumaDochodow);
                    ImGui::PopStyleColor();

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("");
                    ImGui::TableSetColumnIndex(1); ImGui::Text("");

                    // Wydatki
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("Rachunki");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                    ImGui::Text("%.2f zl", wydatekRachunki);
                    ImGui::PopStyleColor();

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("Jedzenie");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                    ImGui::Text("%.2f zl", wydatekJedzenie);
                    ImGui::PopStyleColor();

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("Ubrania");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                    ImGui::Text("%.2f zl", wydatekUbrania);
                    ImGui::PopStyleColor();

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("Inne");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                    ImGui::Text("%.2f zl", wydatekInne);
                    ImGui::PopStyleColor();

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("Suma wydatkow");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
                    ImGui::Text("%.2f zl", sumaWydatkow);
                    ImGui::PopStyleColor();

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("");
                    ImGui::TableSetColumnIndex(1); ImGui::Text("");

                    // Saldo
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("SALDO");
                    ImGui::TableSetColumnIndex(1);
                    ImVec4 saldoColor = saldo >= 0 ? ImVec4(0.10f, 0.74f, 0.61f, 1.00f) : ImVec4(0.85f, 0.09f, 0.18f, 1.00f);
                    ImGui::PushStyleColor(ImGuiCol_Text, saldoColor);
                    ImGui::Text("%.2f zl", saldo);
                    ImGui::PopStyleColor();

                    ImGui::EndTable();
                }

                ImGui::EndChild();

                ImGui::Spacing();

                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 120) / 2);
                if (ImGui::Button("Zamknij", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }


        }


        // Wyswietl podsumowanie wedlug kategorii
        else if (currentView == View::DisplaySummary) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.95f, 0.95f, 1.00f));
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Podsumowanie wedlug kategorii").x) / 2);
            ImGui::Text("Podsumowanie wedlug kategorii");
            ImGui::PopStyleColor();
            ImGui::Separator();

            // Sekcja z dwoma panelami
            const float childWidth = (ImGui::GetContentRegionAvail().x - 10.0f) / 2.0f;

            // Panel dochodów
            ImGui::BeginChild("PanelDochodow", ImVec2(childWidth, 200), true);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
            ImGui::Text("Dochody");
            ImGui::PopStyleColor();
            ImGui::Separator();

            ImGui::Text("Praca:");
            ImGui::SameLine(150);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
            ImGui::Text("%.2f zl", manager.getIncomeTotal(IncomeType::Work));
            ImGui::PopStyleColor();

            ImGui::Text("Dodatkowe:");
            ImGui::SameLine(150);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
            ImGui::Text("%.2f zl", manager.getIncomeTotal(IncomeType::Additional));
            ImGui::PopStyleColor();

            ImGui::Separator();
            ImGui::Text("Suma dochodow:");
            ImGui::SameLine(150);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.74f, 0.61f, 1.00f));
            ImGui::Text("%.2f zl", manager.getIncomeTotal(IncomeType::Work) + manager.getIncomeTotal(IncomeType::Additional));
            ImGui::PopStyleColor();

            ImGui::EndChild();

            // Panel wydatków
            ImGui::SameLine();
            ImGui::BeginChild("PanelWydatkow", ImVec2(childWidth, 200), true);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::Text("Wydatki");
            ImGui::PopStyleColor();
            ImGui::Separator();

            ImGui::Text("Rachunki:");
            ImGui::SameLine(150);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::Text("%.2f zl", manager.getExpenseTotal(ExpenseType::Bills));
            ImGui::PopStyleColor();

            ImGui::Text("Jedzenie:");
            ImGui::SameLine(150);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::Text("%.2f zl", manager.getExpenseTotal(ExpenseType::Food));
            ImGui::PopStyleColor();

            ImGui::Text("Ubrania:");
            ImGui::SameLine(150);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::Text("%.2f zl", manager.getExpenseTotal(ExpenseType::Clothes));
            ImGui::PopStyleColor();

            ImGui::Text("Inne:");
            ImGui::SameLine(150);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            ImGui::Text("%.2f zl", manager.getExpenseTotal(ExpenseType::Other));
            ImGui::PopStyleColor();

            ImGui::Separator();
            ImGui::Text("Suma wydatkow:");
            ImGui::SameLine(150);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.09f, 0.18f, 1.00f));
            double totalExpenses = manager.getExpenseTotal(ExpenseType::Bills) +
                manager.getExpenseTotal(ExpenseType::Food) +
                manager.getExpenseTotal(ExpenseType::Clothes) +
                manager.getExpenseTotal(ExpenseType::Other);
            ImGui::Text("%.2f zl", totalExpenses);
            ImGui::PopStyleColor();

            ImGui::EndChild();

            // Saldo
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Text("Saldo ogolne:");
            ImGui::SameLine(150);
            double balance = manager.getBalance();
            ImVec4 balanceColor = balance >= 0 ?
                ImVec4(0.10f, 0.74f, 0.61f, 1.00f) :
                ImVec4(0.85f, 0.09f, 0.18f, 1.00f); 
            ImGui::PushStyleColor(ImGuiCol_Text, balanceColor);
            ImGui::Text("%.2f zl", balance);
            ImGui::PopStyleColor();

            // Wykresy
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("Wizualizacja wydatkow");
            ImGui::Separator();

            // Wykres salda
            plotBalanceHistory(manager);
        }

        ImGui::EndChild();

        // Popupy
        if (showEditPopup) {
            ImGui::OpenPopup("Edytuj Transakcje");
            showEditPopup = false;
        }

        if (ImGui::BeginPopupModal("Edytuj Transakcje", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Edytuj dane transakcji:");
            ImGui::Separator();

            ImGui::InputText("Nowa data", editDate, IM_ARRAYSIZE(editDate));
            ImGui::InputText("Nowy opis", editDesc, IM_ARRAYSIZE(editDesc));
            ImGui::InputDouble("Nowa kwota", &editAmt);

            ImGui::Separator();
            if (ImGui::Button("Zapisz", ImVec2(120, 0))) {
                if (manager.editTransaction(selectedIndex, editDate, editDesc, editAmt)) {
                    // Automatycznie zapisz do bazy danych
                    manager.saveToDatabase();
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Anuluj", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        if (showDeleteConfirmation) {
            ImGui::OpenPopup("Potwierdz usuniecie");
            showDeleteConfirmation = false;
        }

        if (ImGui::BeginPopupModal("Potwierdz usuniecie", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Czy na pewno chcesz usunac te transakcje?");
            ImGui::Separator();

            if (ImGui::Button("Tak", ImVec2(120, 0))) {
                if (manager.removeTransaction(selectedIndex)) {
                    // Automatycznie zapisz do bazy danych
                    manager.saveToDatabase();
                }
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Nie", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        // Popup zapisania
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
        glClearColor(0.13f, 0.14f, 0.17f, 1.00f);
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
