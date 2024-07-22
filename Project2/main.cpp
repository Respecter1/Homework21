/*
    Ускладнимо ситуацію з вправи 1. Припустимо, що є три види водіїв: таксисти, які переїжджають перехід на червоне світло; не місцеві, які їдуть повільно та обережно
    ; і місцеві, які ведуть машини по-різному, залежно від уявлень про свою "крутість". Також є два типи пішоходів: місцеві, які переходять вулицю, де їм заманеться
    , і туристи, які переходять вулицю тільки на зелене світло. А крім того, є ще велосипедисти, які поводяться то як пішоходи, то як водії. Як ці міркування змінять модель?
*/



#include <iostream>
#include <memory>
#include <string>
#include <ctime>
#include <chrono>
#include <vector>
#include <cstdlib> // для std::rand

// Enum для напрямку руху
enum class Traffic {
    ONE_WAY,
    TWO_WAY
};

// Enum для станів світлофора
enum class TrafficLight {
    GREEN,
    YELLOW,
    RED
};

// Базовий клас для учасників дорожнього руху
class Participant {
public:
    virtual void act() const = 0;
    virtual ~Participant() {}
};

// Класи для водіїв
class Driver : public Participant {
public:
    virtual void drive() const = 0;
    void act() const override {
        drive();
    }
};

class TaxiDriver : public Driver {
public:
    void drive() const override {
        std::cout << "Taxi driver drives through red light!" << std::endl;
    }
};

class LocalDriver : public Driver {
public:
    void drive() const override {
        std::cout << "Local driver drives confidently." << std::endl;
    }
};

class NonLocalDriver : public Driver {
public:
    void drive() const override {
        std::cout << "Non-local driver drives cautiously." << std::endl;
    }
};

// Класи для пішоходів
class Pedestrian : public Participant {
public:
    virtual void walk() const = 0;
    void act() const override {
        walk();
    }
};

class LocalPedestrian : public Pedestrian {
public:
    void walk() const override {
        std::cout << "Local pedestrian crosses anywhere." << std::endl;
    }
};

class TouristPedestrian : public Pedestrian {
public:
    void walk() const override {
        std::cout << "Tourist pedestrian crosses at green light." << std::endl;
    }
};

// Клас для велосипедистів
class Cyclist : public Participant {
public:
    void act() const override {
        if (std::rand() % 2 == 0) {
            std::cout << "Cyclist behaves like a driver." << std::endl;
        }
        else {
            std::cout << "Cyclist behaves like a pedestrian." << std::endl;
        }
    }
};

// Клас для моделювання дорожнього руху
class MyTraffic {
public:
    MyTraffic() : light1(TrafficLight::RED), light2(TrafficLight::GREEN) {}
    ~MyTraffic() {}

    // Метод для перемикання стану світлофорів
    void switchLights() {
        if (light1 == TrafficLight::GREEN) {
            light1 = TrafficLight::RED;
            light2 = TrafficLight::GREEN;
        }
        else {
            light1 = TrafficLight::GREEN;
            light2 = TrafficLight::RED;
        }
    }

    // Метод для отримання стану світлофора
    TrafficLight getLight1() const { return light1; }
    TrafficLight getLight2() const { return light2; }

private:
    TrafficLight light1;
    TrafficLight light2;
};

// Клас для моделювання вулиці
class Street {
public:
    Street(const std::string& name, Traffic road = Traffic::TWO_WAY)
        : name(name), road(road)
    {
        crosswalk++;
    }
    ~Street() {}

private:
    std::string name;
    Traffic road;
    static int crosswalk;
};

int Street::crosswalk = 0;

// Клас для моделювання перехрестя
class Crossroads {
public:
    Crossroads(std::shared_ptr<Street> street1, std::shared_ptr<Street> street2)
        : street1(street1), street2(street2) {}

    ~Crossroads() {}

    void controlTrafficLights(MyTraffic& traffic, const std::vector<std::shared_ptr<Participant>>& participants) {
        // Отримуємо поточний час
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm localTime;

        // Використовуємо localtime_s для отримання локального часу
        localtime_s(&localTime, &currentTime);

        // Отримуємо поточні хвилини
        int currentMinutes = localTime.tm_min;

        if (currentMinutes % 2 == 0) {
            traffic.switchLights();
        }

        // Виводимо стан світлофорів
        std::cout << "The traffic light on the first street is "
            << (traffic.getLight1() == TrafficLight::GREEN ? "green." : "red.")
            << std::endl;
        std::cout << "The traffic light on the second street is "
            << (traffic.getLight2() == TrafficLight::GREEN ? "green." : "red.")
            << std::endl;

        // Виводимо дії учасників дорожнього руху
        for (const auto& participant : participants) {
            participant->act();
        }
    }

private:
    std::shared_ptr<Street> street1;
    std::shared_ptr<Street> street2;
};

int main() {
    auto street1 = std::make_shared<Street>("Street1", Traffic::TWO_WAY);
    auto street2 = std::make_shared<Street>("Street2", Traffic::TWO_WAY);
    MyTraffic traffic;

    Crossroads myMove(street1, street2);

    // Створюємо учасників дорожнього руху
    std::vector<std::shared_ptr<Participant>> participants = {
        std::make_shared<TaxiDriver>(),
        std::make_shared<LocalDriver>(),
        std::make_shared<NonLocalDriver>(),
        std::make_shared<LocalPedestrian>(),
        std::make_shared<TouristPedestrian>(),
        std::make_shared<Cyclist>()
    };

    myMove.controlTrafficLights(traffic, participants);

    return 0;
}
