# Parking Lot System

A multi-floor parking lot system built with object-oriented design. It has a **C++ console version** (the core project) and a **browser version** built with HTML, CSS and JavaScript.

## Overview

Parking Lot Management is a classic low-level design problem. This project lets you add floors and parking spots, park vehicles, and get a fee when they leave. Key features:

- **Add floors and spots:** build the lot yourself, floor by floor.
- **Auto spot assignment:** a vehicle gets the first free spot of the right type (Bike, Car, Truck).
- **Tickets:** every entry gets a ticket ID with an entry time.
- **Fee on exit:** hourly pricing per vehicle type, with a 1 hour minimum.
- **Full-lot handling:** entry is denied when no matching spot is free.
- **Occupancy view:** see how many spots are taken on each floor.

## Design Patterns Used

- **Factory:** `VehicleFactory` creates the right vehicle object from a type.
- **Strategy:** `PricingStrategy` lets you swap fee rules without touching the parking logic.
- **Singleton:** only one `ParkingLot` instance exists.

## Live Demo

<<<<<<< HEAD
Try the browser version here:    https://priyanshu-1010101.github.io/Parking_Lot_System/web/
=======
Try the browser version here: `   https://priyanshu-1010101.github.io/Parking_Lot_System/web/`
>>>>>>> 317f0a9 (Fix live demo link)

## Project Structure

```
parking-lot-system/
├── cpp/                 # C++ console version (.h and .cpp files)
├── web/
│   ├── index.html       # page structure
│   ├── style.css        # styling
│   └── script.js        # same classes, written in JavaScript
├── .gitignore
└── README.md
```

## How to Run

**C++ version** (needs g++ with C++17):
```bash
cd cpp
g++ -std=c++17 *.cpp -o Main
./Main         
```
`cpp/` should contain only one file with a `main()` function.

**Web version:** open `web/index.html` in any browser.

## Sample Output (C++)

```
[ENTRY] Car (KA-01-HH-1234) parked at Floor 1, Spot C-01
        Ticket ID: T1001
[ERROR] No available spot for vehicle type: Truck
[EXIT] Car (KA-01-HH-1234) left Spot C-01
       Fee Charged: Rs.50
```

## Tech Stack

C++17, HTML, CSS, JavaScript

## Future Improvements

- Handle several vehicles entering at the same time (multithreading)
- Save data in a database
- Add discount rules as new pricing strategies
