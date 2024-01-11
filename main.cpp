#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <queue>

using namespace std;

enum class SensorType
{
    Altitude,
    SpeedInKmh,
    FuelConsumption
};

class SensorData
{
    float value;
    SensorType sensorType;
    time_t time;

public:
    SensorType GetSensorType() const { return sensorType; }
    float GetValue() const { return value; }
    void SetValue(float v) { value = v; }
    time_t GetTime() const { return time; }
    SensorData(SensorType sensorType, float value, time_t time)
    {
        this->value = value;
        this->sensorType = sensorType;
        this->time = time;
    }
};

void FillData(vector<SensorData> &v);
time_t CreateTime(int year, int month, int day, int hour, int minute, int second);

int main()
{
    vector<SensorData> sensorData;
    FillData(sensorData);

    // DEL 1
    int altitudeRecordsCount = count_if(sensorData.begin(), sensorData.end(), [](const SensorData &data) {
        time_t localTime = data.GetTime();
        struct tm *timeInfo = localtime(&localTime);

        return data.GetSensorType() == SensorType::Altitude &&
               timeInfo->tm_year + 1900 == 2012 &&
               timeInfo->tm_mon + 1 == 1 &&
               timeInfo->tm_mday == 2;
    });
    cout << "Altitude records on 2012-01-02: " << altitudeRecordsCount << endl;

    // DEL 2
    auto maxSpeedIt = max_element(sensorData.begin(), sensorData.end(), [](const SensorData &a, const SensorData &b) {
        return a.GetSensorType() == SensorType::SpeedInKmh &&
               b.GetSensorType() == SensorType::SpeedInKmh &&
               a.GetValue() < b.GetValue();
    });

    if (maxSpeedIt != sensorData.end() && maxSpeedIt->GetValue() > 99.9)
    {
        cout << "Maximum speed reached" << endl;
    }
    else
    {
        cout << "No maximum speed reached" << endl;
    }

    // DEL 3
    auto fuelIt = find_if(sensorData.begin(), sensorData.end(), [](const SensorData& data) {
        return data.GetSensorType() == SensorType::FuelConsumption;
    });

    if (fuelIt != sensorData.end())
    {
        float originalFuelConsumption = fuelIt->GetValue();
        cout << "Original fuel consumption: " << originalFuelConsumption << endl;

        for_each(sensorData.begin(), sensorData.end(), [](SensorData& data) {
            if (data.GetSensorType() == SensorType::FuelConsumption)
            {
                data.SetValue(data.GetValue() * 1.75f);
            }
        });

        auto updatedFuelIt = find_if(sensorData.begin(), sensorData.end(), [](const SensorData& data) {
            return data.GetSensorType() == SensorType::FuelConsumption;
        });

        if (updatedFuelIt != sensorData.end())
        {
            cout << "Updated fuel consumption: " << updatedFuelIt->GetValue() << endl;
        }
    }

    return 0;
}

void FillData(vector<SensorData> &v)
{
    srand(time(NULL));

    time_t tid = CreateTime(2012, 1, 1, 1, 1, 1);
    for (int i = 0; i < 100000; i++)
    {
        SensorType type = static_cast<SensorType>(rand() % 3);
        float value = 0.0f;
        if (type == SensorType::Altitude)
            value = rand() % 1000;
        else if (type == SensorType::FuelConsumption)
            value = static_cast<float>(rand()) / RAND_MAX * 10.0f; // Adjusted fuel value generation
        else if (type == SensorType::SpeedInKmh)
            value = rand() % 110;
        else
        {
            value = 99;
        }
        v.push_back(SensorData(type, value, tid));
        tid = tid + rand() % 10 + 1;
    }
}

time_t CreateTime(int year, int month, int day, int hour, int minute, int second)
{
    struct tm tid = {0};
    tid.tm_year = year - 1900;
    tid.tm_mon = month - 1;
    tid.tm_mday = day;
    tid.tm_hour = hour;
    tid.tm_min = minute;
    tid.tm_sec = second;
    return mktime(&tid);
}


// Sjukhus
// #include <iostream>
// #include <queue>
// #include <ctime>

// class Patient {
// public:
//   int queueNumber;
//   std::string name;
//   std::time_t timeOfArrival;

//   Patient(int queueNumber, std::string name, std::time_t timeOfArrival) :
//     queueNumber(queueNumber),
//     name(name),
//     timeOfArrival(timeOfArrival) {}
// };

// int main() {
//   // Skapa en kö för patienter
//   std::queue<Patient> queue;

//   // Infinite loop
//   while (true) {
//     // Meny
//     std::cout << "What do you want to do?\n"
//               << "1. Enter new patient in queue\n"
//               << "2. Remove patient from queue\n"
//               << "3. Exit\n"
//               << "Enter choice: ";

//     int choice;
//     std::cin >> choice;

//     // Hanterar anvöndarens val
//     switch (choice) 
//     {
//       case 1: 
//       {

//         int queueNumber;
//         std::string name;
//         std::cout << "Enter queue number: ";
//         std::cin >> queueNumber;
//         std::cout << "Enter name: ";
//         std::cin >> name;

//         // Skapa ny patient och lägg till i kön
//         Patient newPatient(queueNumber, name, std::time(nullptr));
//         queue.push(newPatient);

//         // Visa meddelande "Kalla in nästa kund!"
//         std::cout << "Calling in the next customer!" << std::endl;
//         break;
//       }
//       case 2: 
//       {
       
//         if (!queue.empty()) 
//         {    
//           Patient patient = queue.front();
//           // Visa information om patienten
//           std::cout << "Patient " << patient.queueNumber << ", " << patient.name << ", arrived at " << std::ctime(&patient.timeOfArrival) << std::endl;

//           // Beräkna tiden som patienten har väntat
//           std::time_t now = std::time(nullptr);
//           double timeWaited = difftime(now, patient.timeOfArrival);

//           // Visa meddelande "Denna kund har väntat i"
//           std::cout << "This customer has been waiting for " << timeWaited << " seconds." << std::endl;
//           queue.pop();
//         } else {
//           // Visa meddelande "Kön är tom"
//           std::cout << "Queue is empty" << std::endl;
//         }
//         break;
//       }
//       case 3: {
//         return 0;
//       }
//       default: {
//         std::cout << "Invalid choice" << std::endl;
//         break;
//       }
//     }
//   }

//   return 0;
// }

// Bankomat
// #include <iostream>
// #include <map>

// // Skapa en typedef för att göra koden mer läsbar
// typedef std::map<int, double> BankMap;

// // Funktion för att skapa ett nytt konto
// void createAccount(BankMap &bank) 
// {
//     int accNum;
//     double balance;

//     std::cout << "Enter account number: ";
//     std::cin >> accNum;

//     // Kontrollera om kontonumret redan existerar
//     if (bank.find(accNum) != bank.end()) 
//     {
//         std::cout << "Account already exist.\n";
//     } else {
//         std::cout << "Enter balance: ";
//         std::cin >> balance;
//         bank[accNum] = balance;
//         std::cout << "Account created.\n";
//     }
// }

// // Funktion för att logga in på ett befintligt konto
// void login(BankMap &bank) 
// {
//     int accNum;
//     std::cout << "Enter account number: ";
//     std::cin >> accNum;

//     // Kontrollera om kontot finns
//     if (bank.find(accNum) != bank.end()) 
//     {
//         double balance = bank[accNum];
//         std::cout << "Login successful. Balance: " << balance << "\n";
//     } else {
//         std::cout << "The account does not exist.\n";
//     }
// }

// // Funktion för att sätta in pengar på ett konto
// void depositMoney(BankMap &bank) 
// {
//     int accNum;
//     double amount;

//     std::cout << "Enter account number: ";
//     std::cin >> accNum;

//     // Kontrollera om kontot finns
//     if (bank.find(accNum) != bank.end()) 
//     {
//         std::cout << "Enter amount to deposit: ";
//         std::cin >> amount;
//         bank[accNum] += amount;
//         std::cout << "Deposit successful. New balance: " << bank[accNum] << "\n";
//     } else {
//         std::cout << "Account does not exist.\n";
//     }
// }

// // Funktion för att ta ut pengar från ett konto
// void withdrawMoney(BankMap &bank) 
// {
//     int accNum;
//     double amount;

//     std::cout << "Enter account number: ";
//     std::cin >> accNum;

//     // Kontrollera om kontot finns
//     if (bank.find(accNum) != bank.end()) 
//     {
//         std::cout << "Enter amount to deposit: ";
//         std::cin >> amount;

//         // Kontrollera om tillräckligt med saldo finns
//         if (bank[accNum] >= amount) 
//         {
//             bank[accNum] -= amount;
//             std::cout << "Withdrawal successful. New balance: " << bank[accNum] << "\n";
//         } else {
//             std::cout << "Insufficient balance.\n";
//         }
//     } else {
//         std::cout << "Account does not exist.\n";
//     }
// }

// int main() 
// {
//     BankMap bank;

//     int choice;
//     do {
//         // Visa meny
//         std::cout << "\n1. Create account\n";
//         std::cout << "2. Login\n";
//         std::cout << "3. Deposit money\n";
//         std::cout << "4. Withdraw money\n";
//         std::cout << "0. Exit\n";
//         std::cout << "Choose an option: ";
//         std::cin >> choice;

//         // Utför önskad handling baserat på användarens val
//         switch (choice) 
//         {
//             case 1:
//                 createAccount(bank);
//                 break;
//             case 2:
//                 login(bank);
//                 break;
//             case 3:
//                 depositMoney(bank);
//                 break;
//             case 4:
//                 withdrawMoney(bank);
//                 break;
//             case 0:
//                 std::cout << "Exit program.\n";
//                 break;
//             default:
//                 std::cout << "Invalid choice. Please try again.\n";
//         }
//     } while (choice != 0);

//     return 0;
// }
