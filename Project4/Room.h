#pragma once
#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>

// ���� ��� ����� ������ � �����
class Room {
public:
    Room(int number, int floor, int beds, bool vip);

    int getNumber() const;
    int getFloor() const;
    int getBeds() const;
    bool isVip() const;

private:
    int number_;
    int floor_;
    int beds_;
    bool vip_;
};

// ���� ��� ��������� �������� � �����
class Hotel {
public:
    void addRoom(const std::shared_ptr<Room>& room);
    void bookRoom(int number);
    void releaseRoom(int number);
    std::shared_ptr<Room> getRoom(int number) const;

    std::vector<std::shared_ptr<Room>> getAvailableRooms() const;

private:
    std::vector<std::shared_ptr<Room>> rooms_;
    std::map<int, bool> roomStatus_; // true - ������������, false - �����
};

// ���� ��� ��������� �����������
class Catering {
public:
    void setMeals(int roomNumber, const std::vector<std::string>& meals);
    std::vector<std::string> getMeals(int roomNumber) const;

private:
    std::map<int, std::vector<std::string>> roomMeals_;
};

