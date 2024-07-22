#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>

// Клас для управління конференціями
class Conference {
public:
    Conference(const std::string& name, const std::string& date);

    void addParticipant(const std::string& participant);
    void addRoom(const std::string& room);
    void notifyParticipants() const;

    std::string getName() const;
    std::string getDate() const;
    std::vector<std::string> getParticipants() const;

private:
    std::string name_;
    std::string date_;
    std::vector<std::string> participants_;
    std::vector<std::string> rooms_;
};

// Клас для управління зустрічами
class Meeting {
public:
    Meeting(const std::string& name, const std::string& date);

    void addParticipant(const std::string& participant);
    void addRoom(const std::string& room);
    void notifyParticipants() const;

    std::string getName() const;
    std::string getDate() const;
    std::vector<std::string> getParticipants() const;

private:
    std::string name_;
    std::string date_;
    std::vector<std::string> participants_;
    std::vector<std::string> rooms_;
};

// Клас для управління розкладом
class Schedule {
public:
    void addConference(const std::shared_ptr<Conference>& conference);
    void addMeeting(const std::shared_ptr<Meeting>& meeting);

    std::vector<std::shared_ptr<Conference>> getConferences() const;
    std::vector<std::shared_ptr<Meeting>> getMeetings() const;

private:
    std::vector<std::shared_ptr<Conference>> conferences_;
    std::vector<std::shared_ptr<Meeting>> meetings_;
};
