#include <iostream>
#include <map>

// Skapa en typedef för att göra koden mer läsbar
typedef std::map<int, double> BankMap;

// Funktion för att skapa ett nytt konto
void createAccount(BankMap &bank) 
{
    int accNum;
    double balance;

    std::cout << "Enter account number: ";
    std::cin >> accNum;

    // Kontrollera om kontonumret redan existerar
    if (bank.find(accNum) != bank.end()) 
    {
        std::cout << "Account already exist.\n";
    } else {
        std::cout << "Enter balance: ";
        std::cin >> balance;
        bank[accNum] = balance;
        std::cout << "Account created.\n";
    }
}

// Funktion för att logga in på ett befintligt konto
void login(BankMap &bank) 
{
    int accNum;
    std::cout << "Enter account number: ";
    std::cin >> accNum;

    // Kontrollera om kontot finns
    if (bank.find(accNum) != bank.end()) 
    {
        double balance = bank[accNum];
        std::cout << "Login successful. Balance: " << balance << "\n";
    } else {
        std::cout << "The account does not exist.\n";
    }
}

// Funktion för att sätta in pengar på ett konto
void depositMoney(BankMap &bank) 
{
    int accNum;
    double amount;

    std::cout << "Enter account number: ";
    std::cin >> accNum;

    // Kontrollera om kontot finns
    if (bank.find(accNum) != bank.end()) 
    {
        std::cout << "Enter amount to deposit: ";
        std::cin >> amount;
        bank[accNum] += amount;
        std::cout << "Deposit successful. New balance: " << bank[accNum] << "\n";
    } else {
        std::cout << "Account does not exist.\n";
    }
}

// Funktion för att ta ut pengar från ett konto
void withdrawMoney(BankMap &bank) 
{
    int accNum;
    double amount;

    std::cout << "Enter account number: ";
    std::cin >> accNum;

    // Kontrollera om kontot finns
    if (bank.find(accNum) != bank.end()) 
    {
        std::cout << "Enter amount to deposit: ";
        std::cin >> amount;

        // Kontrollera om tillräckligt med saldo finns
        if (bank[accNum] >= amount) 
        {
            bank[accNum] -= amount;
            std::cout << "Withdrawal successful. New balance: " << bank[accNum] << "\n";
        } else {
            std::cout << "Insufficient balance.\n";
        }
    } else {
        std::cout << "Account does not exist.\n";
    }
}

int main() 
{
    BankMap bank;

    int choice;
    do {
        // Visa meny
        std::cout << "\n1. Create account\n";
        std::cout << "2. Login\n";
        std::cout << "3. Deposit money\n";
        std::cout << "4. Withdraw money\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        // Utför önskad handling baserat på användarens val
        switch (choice) 
        {
            case 1:
                createAccount(bank);
                break;
            case 2:
                login(bank);
                break;
            case 3:
                depositMoney(bank);
                break;
            case 4:
                withdrawMoney(bank);
                break;
            case 0:
                std::cout << "Exit program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}