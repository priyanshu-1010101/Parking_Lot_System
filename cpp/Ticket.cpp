#include "Ticket.h"

Ticket::Ticket(
    const std::string &ticketId, Vehicle *vehicle, ParkingSpot *spot,
    std::chrono::system_clock::time_point entryTime)
    : ticketId(ticketId), vehicle(vehicle), spot(spot), entryTime(entryTime), hasExited(false) {}

std::string Ticket::getTicketId() const
{
    return ticketId;
}

Vehicle *Ticket::getVehicle() const
{
    return vehicle;
}

ParkingSpot *Ticket::getSpot() const
{
    return spot;
}

std::chrono::system_clock::time_point Ticket::getEntryTime() const
{
    return entryTime;
}

void Ticket::setExitTime(std::chrono::system_clock::time_point time)
{
    exitTime = time;
    hasExited = true;
}

std::chrono::system_clock::time_point Ticket::getExitTime() const
{
    return exitTime;
}
