//Julian Frank, 4501607

#include "car.hpp"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

Car::Car()
{
    manufacturer = nullptr;
    model = nullptr;
    zeroToSixtyNs = 0;
    headonDragCoeff = 0;
    backseatDoors = None;
    horsepower = 0;
    seatCount = 0;
}

Car::Car(char const* const manufacturerName, char const* const modelName,
         PerformanceStats perf, uint8_t numSeats, DoorKind backseatDoorDesign)
{
    manufacturerChange(manufacturerName);
    modelNameChange(modelName);
    reevaluateStats(perf);
    recountSeats(numSeats);
    reexamineDoors(backseatDoorDesign);
}

Car::Car(Car const& o)
{
    char* *s1 = new char*(strdup(o.getManufacturer()));
    manufacturer = *s1;
    delete s1;

    char* *s2 = new char*(strdup(o.getModel()));
    model = *s2;
    delete s2;
    
    zeroToSixtyNs = o.getStats().zeroToSixtyNs;
    headonDragCoeff = o.getStats().headonDragCoeff;
    backseatDoors = o.getBackseatDoors();
    horsepower = o.getStats().horsepower;
    seatCount = o.getSeatCount();
}

Car& Car::operator=(Car const& o)
{
    char* *s1 = new char*(strdup(o.getManufacturer()));
    this->manufacturer = *s1;
    delete s1;

    char* *s2 = new char*(strdup(o.getModel()));
    this->model = *s2;
    delete s2;

    this -> zeroToSixtyNs = o.getStats().zeroToSixtyNs;
    this -> headonDragCoeff = o.getStats().headonDragCoeff;
    this -> backseatDoors = o.getBackseatDoors();
    this -> horsepower = o.getStats().horsepower;
    this -> seatCount = o.getSeatCount();

    return *this;
}

Car::~Car()
{
    free(manufacturer);
    free(model);
}

char const* Car::getManufacturer() const
{
    return const_cast<const char*>(manufacturer);
}

char const* Car::getModel() const {
    return const_cast<const char*>(model);
}

PerformanceStats Car::getStats() const
{
    PerformanceStats stats{horsepower, zeroToSixtyNs, headonDragCoeff};

    return stats;
}

uint8_t Car::getSeatCount() const
{
    return seatCount;
}

DoorKind Car::getBackseatDoors() const
{
    return backseatDoors;
}

void Car::manufacturerChange(char const* const newManufacturer)
{
    char* *s = new char*(strdup(newManufacturer));
    manufacturer = *s;
    delete s;
}

void Car::modelNameChange(char const* const newModelName)
{
    char* *s = new char*(strdup(newModelName));
    model = *s;
    delete s;
}

void Car::reevaluateStats(PerformanceStats newStats)
{
    zeroToSixtyNs = newStats.zeroToSixtyNs;
    headonDragCoeff = newStats.headonDragCoeff;
    horsepower = newStats.horsepower;
}

void Car::recountSeats(uint8_t newSeatCount)
{
    seatCount = newSeatCount;
}

void Car::reexamineDoors(DoorKind newDoorKind)
{
    backseatDoors = newDoorKind;
}

/*int main() {

    char const* man = "Manny";
    char const* mod = "Mod";
    PerformanceStats perf1{500,1000,1.234};
    uint8_t nums = 4;
    uint8_t num2 = 3;
    DoorKind doors = Hinge;

    Car car1;

    Car car2{man, mod, perf1, nums, doors};

    car1 = car2;

    cout << static_cast<string>(car1.getModel()) << endl;
    cout << static_cast<string>(car1.getManufacturer()) << endl;
    cout << static_cast<int>(car1.getSeatCount()) << endl;

    return 0;
}*/
