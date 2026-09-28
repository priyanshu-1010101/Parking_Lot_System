#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <chrono>
#include "Vehicle.h"
#include "ParkingSpot.h"

class Ticket
{
private:
    std::string ticketId;
    Vehicle *vehicle;
    ParkingSpot *spot;
    std::chrono::system_clock::time_point entryTime;
    std::chrono::system_clock::time_point exitTime;
    bool hasExited;

public:
    Ticket(const std::string &ticketId, Vehicle *vehicle, ParkingSpot *spot,
           std::chrono::system_clock::time_point entryTime);

    std::string getTicketId() const;
    Vehicle *getVehicle() const;
    ParkingSpot *getSpot() const;
    std::chrono::system_clock::time_point getEntryTime() const;

    void setExitTime(std::chrono::system_clock::time_point time);
    std::chrono::system_clock::time_point getExitTime() const;
};

#endif
