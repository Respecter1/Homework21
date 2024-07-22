/*
    ���������� �������� � ������ 1. ����������, �� � ��� ���� ��䳿�: ��������, �� ����������� ������� �� ������� �����; �� �����, �� ����� ������� �� ��������
    ; � �����, �� ������ ������ ��-������, ������� �� ������� ��� ���� "�������". ����� � ��� ���� �������: �����, �� ���������� ������, �� �� ����������
    , � �������, �� ���������� ������ ����� �� ������ �����. � ��� ����, � �� �������������, �� ���������� �� �� �������, �� �� ��䳿. �� �� ��������� ������ ������?
*/



#include <iostream>
#include <memory>
#include <string>
#include <ctime>
#include <chrono>
#include <vector>
#include <cstdlib> // ��� std::rand

// Enum ��� �������� ����
enum class Traffic {
    ONE_WAY,
    TWO_WAY
};

// Enum ��� ����� ���������
enum class TrafficLight {
    GREEN,
    YELLOW,
    RED
};

// ������� ���� ��� �������� ���������� ����
class Participant {
public:
    virtual void act() const = 0;
    virtual ~Participant() {}
};

// ����� ��� ��䳿�
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

// ����� ��� �������
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

// ���� ��� �������������
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

// ���� ��� ����������� ���������� ����
class MyTraffic {
public:
    MyTraffic() : light1(TrafficLight::RED), light2(TrafficLight::GREEN) {}
    ~MyTraffic() {}

    // ����� ��� ����������� ����� ���������
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

    // ����� ��� ��������� ����� ���������
    TrafficLight getLight1() const { return light1; }
    TrafficLight getLight2() const { return light2; }

private:
    TrafficLight light1;
    TrafficLight light2;
};

// ���� ��� ����������� ������
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

// ���� ��� ����������� ����������
class Crossroads {
public:
    Crossroads(std::shared_ptr<Street> street1, std::shared_ptr<Street> street2)
        : street1(street1), street2(street2) {}

    ~Crossroads() {}

    void controlTrafficLights(MyTraffic& traffic, const std::vector<std::shared_ptr<Participant>>& participants) {
        // �������� �������� ���
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm localTime;

        // ������������� localtime_s ��� ��������� ���������� ����
        localtime_s(&localTime, &currentTime);

        // �������� ������ �������
        int currentMinutes = localTime.tm_min;

        if (currentMinutes % 2 == 0) {
            traffic.switchLights();
        }

        // �������� ���� ���������
        std::cout << "The traffic light on the first street is "
            << (traffic.getLight1() == TrafficLight::GREEN ? "green." : "red.")
            << std::endl;
        std::cout << "The traffic light on the second street is "
            << (traffic.getLight2() == TrafficLight::GREEN ? "green." : "red.")
            << std::endl;

        // �������� 䳿 �������� ���������� ����
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

    // ��������� �������� ���������� ����
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
