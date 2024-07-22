/*
	����������, �� � �� ������, �� �������������, � ����������� �����, ����������� � ���������� ����������
	. ������� �������� ��������� ������, ��� ���������, �� ��������� ���� ������� ������ ������� ���������
	  ������� ������� ��� ����������. �� ��'���� �� �� ����� ������ ������ ��� ������� ���� ��������?
*/
#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <ctime>
#include <chrono>

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

    void controlTrafficLights(MyTraffic& traffic) {
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
    myMove.controlTrafficLights(traffic);

    return 0;
}
