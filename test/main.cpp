/*
	Припустимо, що є дві вулиці, що перетинаються, з двостороннім рухом
	, світлофорами і пішохідними переходами. Потрібно створити віртуальну модель
	, щоб визначити, чи дозволить зміна частоти подачі сигналу світлофора зробити дорожній рух рівномірнішим
	. Які об'єкти та які класи будуть потрібні для імітації цієї ситуації?
*/

#include <iostream>
#include <memory>
#include <string>
#include <ctime>
#include <chrono>

enum class Traffic {
    ONE_WAY,
    TWO_WAY
};

enum class TrafficLight {
    GREEN,
    YELLOW,
    RED
};

class Street {
public:
    Street(const std::string& name, Traffic road = Traffic::TWO_WAY)
        : name(name), road(road) 
    {
        crosswalk++;
    }
    ~Street(){}
private:
    std::string name;
    Traffic road;
    static int crosswalk;
};

int Street::crosswalk = 0;

class Crossroads {
public:
    Crossroads(std::shared_ptr<Street> street1, std::shared_ptr<Street> street2)
        : street1(street1), street2(street2) {}

    ~Crossroads(){}

    void controlTrafficLights() {
        // Отримуємо поточний час
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm localTime;

        // Використовуємо localtime_s для отримання локального часу
        localtime_s(&localTime, &currentTime);

        // Отримуємо поточні хвилини
        int currentMinutes = localTime.tm_min;
        if (currentMinutes % 2 == 0) {
            std::cout << "The traffic light on the first street is green." << std::endl;
            std::cout << "The traffic light on the second street is red." << std::endl;
        }
        else {
            std::cout << "The traffic light on the first street is red." << std::endl;
            std::cout << "The traffic light on the second street is green." << std::endl;
        }
    }

private:
    std::shared_ptr<Street> street1;
    std::shared_ptr<Street> street2;
};

int main() {
    auto street1 = std::make_shared<Street>("Street1", Traffic::TWO_WAY);
    auto street2 = std::make_shared<Street>("Street2", Traffic::TWO_WAY);

    Crossroads myMove(street1, street2);
    myMove.controlTrafficLights();

    return 0;
}
