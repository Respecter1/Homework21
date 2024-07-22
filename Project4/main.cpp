/*
	Спроектуйте інтерфейси до класів до програми, що ви описали у вправі 3, яка стосується резервування 
	готельних номерів.
*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Користувач
class User {
public:
    User(const std::string& name) : name(name) {}
    std::string getName() const { return name; }
private:
    std::string name;
};

// Управління користувачами
class UserManager {
public:
    void registerUser(const std::string& name) {
        users.push_back(std::make_shared<User>(name));
    }

    void listUsers() {
        for (const auto& user : users) {
            std::cout << "User: " << user->getName() << std::endl;
        }
    }

private:
    std::vector<std::shared_ptr<User>> users;
};

// Конференція
class Conference {
public:
    Conference(const std::string& title) : title(title) {}
    std::string getTitle() const { return title; }
private:
    std::string title;
};

// Управління конференціями
class ConferenceManager {
public:
    void createConference(const std::string& title) {
        conferences.push_back(std::make_shared<Conference>(title));
    }

    void listConferences() {
        for (const auto& conference : conferences) {
            std::cout << "Conference: " << conference->getTitle() << std::endl;
        }
    }

private:
    std::vector<std::shared_ptr<Conference>> conferences;
};

// Готельний номер
class HotelRoom {
public:
    HotelRoom(int number) : number(number), available(true) {}
    int getNumber() const { return number; }
    bool isAvailable() const { return available; }
    void book() { available = false; }

private:
    int number;
    bool available;
};

// Управління готелем
class HotelManager {
public:
    void addRoom(int number) {
        rooms.push_back(std::make_shared<HotelRoom>(number));
    }

    void listRooms() {
        for (const auto& room : rooms) {
            std::cout << "Room " << room->getNumber()
                << " is " << (room->isAvailable() ? "available" : "booked")
                << std::endl;
        }
    }

    void bookRoom(int number) {
        for (const auto& room : rooms) {
            if (room->getNumber() == number && room->isAvailable()) {
                room->book();
                std::cout << "Room " << number << " booked successfully." << std::endl;
                return;
            }
        }
        std::cout << "Room " << number << " is not available." << std::endl;
    }

private:
    std::vector<std::shared_ptr<HotelRoom>> rooms;
};

// Основний клас системи
class ConferenceSystem {
public:
    ConferenceSystem()
        : userManager(std::make_shared<UserManager>()),
        conferenceManager(std::make_shared<ConferenceManager>()),
        hotelManager(std::make_shared<HotelManager>()) {}

    std::shared_ptr<UserManager> getUserManager() { return userManager; }
    std::shared_ptr<ConferenceManager> getConferenceManager() { return conferenceManager; }
    std::shared_ptr<HotelManager> getHotelManager() { return hotelManager; }

private:
    std::shared_ptr<UserManager> userManager;
    std::shared_ptr<ConferenceManager> conferenceManager;
    std::shared_ptr<HotelManager> hotelManager;
};

int main() {
    ConferenceSystem system;

    // Реєстрація користувачів
    system.getUserManager()->registerUser("Alice");
    system.getUserManager()->registerUser("Bob");

    // Створення конференцій
    system.getConferenceManager()->createConference("Tech Conference");

    // Додавання готельних номерів
    system.getHotelManager()->addRoom(101);
    system.getHotelManager()->addRoom(102);

    // Бронювання номерів
    system.getHotelManager()->bookRoom(101);

    // Вивід списку користувачів, конференцій та номерів
    std::cout << "Users:" << std::endl;
    system.getUserManager()->listUsers();

    std::cout << "\nConferences:" << std::endl;
    system.getConferenceManager()->listConferences();

    std::cout << "\nHotel Rooms:" << std::endl;
    system.getHotelManager()->listRooms();

    return 0;
}
