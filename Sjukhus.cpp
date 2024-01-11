#include <iostream>
#include <queue>
#include <ctime>

class Patient {
public:
  int queueNumber;
  std::string name;
  std::time_t timeOfArrival;

  Patient(int queueNumber, std::string name, std::time_t timeOfArrival) :
    queueNumber(queueNumber),
    name(name),
    timeOfArrival(timeOfArrival) {}
};

int main() {
  // Skapa en kö för patienter
  std::queue<Patient> queue;

  // Infinite loop
  while (true) {
    // Meny
    std::cout << "What do you want to do?\n"
              << "1. Enter new patient in queue\n"
              << "2. Remove patient from queue\n"
              << "3. Exit\n"
              << "Enter choice: ";

    int choice;
    std::cin >> choice;

    // Hanterar anvöndarens val
    switch (choice) 
    {
      case 1: 
      {

        int queueNumber;
        std::string name;
        std::cout << "Enter queue number: ";
        std::cin >> queueNumber;
        std::cout << "Enter name: ";
        std::cin >> name;

        // Skapa ny patient och lägg till i kön
        Patient newPatient(queueNumber, name, std::time(nullptr));
        queue.push(newPatient);

        // Visa meddelande "Kalla in nästa kund!"
        std::cout << "Calling in the next customer!" << std::endl;
        break;
      }
      case 2: 
      {
       
        if (!queue.empty()) 
        {    
          Patient patient = queue.front();
          // Visa information om patienten
          std::cout << "Patient " << patient.queueNumber << ", " << patient.name << ", arrived at " << std::ctime(&patient.timeOfArrival) << std::endl;

          // Beräkna tiden som patienten har väntat
          std::time_t now = std::time(nullptr);
          double timeWaited = difftime(now, patient.timeOfArrival);

          // Visa meddelande "Denna kund har väntat i"
          std::cout << "This customer has been waiting for " << timeWaited << " seconds." << std::endl;
          queue.pop();
        } else {
          // Visa meddelande "Kön är tom"
          std::cout << "Queue is empty" << std::endl;
        }
        break;
      }
      case 3: {
        return 0;
      }
      default: {
        std::cout << "Invalid choice" << std::endl;
        break;
      }
    }
  }

  return 0;
}