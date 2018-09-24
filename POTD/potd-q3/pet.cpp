#include <string>
#include "pet.h"

using namespace std;

// Put your constructor code here!
Pet::Pet()
{
	/*string name;
	int birth_year;
	string type;
	string owner_name;*/
    name = "Rover";
    birth_year = 2017;
    type = "dog";
    owner_name = "Cinda";

}

Pet::Pet(string namee, int birth_yearr, string typee, string owner_namee)
{	
    name = namee;
    birth_year = birth_yearr;
    type = typee;
    owner_name = owner_namee;

}

void Pet::setName(string newName) {
  name = newName;
}

void Pet::setBY(int newBY) {
  birth_year = newBY;
}

void Pet::setType(string newType) {
  type = newType;
}

void Pet::setOwnerName(string newName) {
  owner_name = newName;
}

string Pet::getName() {
  return name;
}

int Pet::getBY() {
  return birth_year;
}

string Pet::getType() {
  return type;
}

string Pet::getOwnerName() {
  return owner_name;
}
