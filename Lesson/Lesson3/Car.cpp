#include"Car.h"

Car::Car(){}

Car::~Car(){}

Car::Car(int id, string name, Position p):DynamicObject(id, name, p){}
