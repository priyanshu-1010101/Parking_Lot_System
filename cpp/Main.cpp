#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "ParkingLot.h"
#include "ParkingFloor.h"
#include "ParkingSpot.h"
#include "VehicleFactory.h"

VehicleType readType()
{
    int c;
    std::cout << "Type (1=Bike, 2=Car, 3=Truck): ";
    std::cin >> c;
    if (c == 1)
        return VehicleType::BIKE;
    if (c == 3)
        return VehicleType::TRUCK;
    return VehicleType::CAR;
}

int main()
{
    ParkingLot &lot = ParkingLot::getInstance();

    std::map<int, ParkingFloor *> floors;

    std::vector<std::unique_ptr<Vehicle>> vehicles;

    int choice = -1;
    while (choice != 0)
    {
        std::cout << "\n===== PARKING LOT MENU =====\n"
                  << "1. Add floor\n"
                  << "2. Add parking spot\n"
                  << "3. Park a vehicle\n"
                  << "4. Unpark a vehicle\n"
                  << "5. Show occupancy\n"
                  << "0. Exit\n"
                  << "Choice: ";
        if (!(std::cin >> choice))
            break;

        if (choice == 1)
        {
            int n;
            std::cout << "Floor number: ";
            std::cin >> n;
            if (floors.count(n))
            {
                std::cout << "Floor " << n << " already exists.\n";
                continue;
            }
            auto f = std::make_unique<ParkingFloor>(n);
            floors[n] = f.get();
            lot.addFloor(std::move(f));
            std::cout << "Floor " << n << " added.\n";
        }
        else if (choice == 2)
        {
            int n;
            std::string spotId;
            std::cout << "Floor number: ";
            std::cin >> n;
            if (!floors.count(n))
            {
                std::cout << "Floor " << n << " does not exist. Add it first.\n";
                continue;
            }
            std::cout << "Spot ID (e.g. C-01): ";
            std::cin >> spotId;
            VehicleType t = readType();
            floors[n]->addSpot(std::make_unique<ParkingSpot>(spotId, t));
            std::cout << "Spot " << spotId << " added to floor " << n << ".\n";
        }
        else if (choice == 3)
        {
            std::string plate;
            std::cout << "License plate: ";
            std::cin >> plate;
            VehicleType t = readType();
            auto v = VehicleFactory::createVehicle(t, plate);
            std::string ticketId = lot.parkVehicle(v.get());
            if (!ticketId.empty())
            {
                vehicles.push_back(std::move(v));
            }
        }
        else if (choice == 4)
        {
            std::string ticketId;
            std::cout << "Ticket ID (e.g. T1001): ";
            std::cin >> ticketId;
            lot.unparkVehicle(ticketId);
        }
        else if (choice == 5)
        {
            lot.printOccupancyStatus();
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}