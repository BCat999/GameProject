#include<list>
#include<iostream>
using namespace std;

#include "Tree.h"
#include "House.h"
#include "Car.h"
#include "Motobike.h"

int main() {
	list<BaseObject*> ls;

	BaseObject* objTree1 = new Tree(1, "Birch", Position(1,1));
	BaseObject* objHouse1 = new House(2, "WareHouse", Position(5, 6));
	BaseObject* objCar1 = new Car(2, "Xichlo", Position(2, 1));
	BaseObject* objMoto1 = new Motobike(3, "Vision", Position(4, 2));

	ls.push_back(objTree1);
	ls.push_back(objHouse1);
	ls.push_back(objCar1);
	ls.push_back(objMoto1);

	for (auto obj : ls) cout << obj->getName() << " ";
	cout << endl;

	for (auto obj : ls) obj->printPosition();
	cout << endl<<"Move obj:\n";
	for (auto obj : ls) obj->move(1, 2);	
	cout << endl<<"Obj after move: \n";

	for (auto obj : ls) obj->printPosition();
}