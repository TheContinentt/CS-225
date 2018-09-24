// main.cpp

#include "pet.h"
#include <iostream>
#include <string>
#include "animal.h"

using namespace std;

int main() {
	//Pet pp();
   Pet p("cat","fish","Garfield","John");
//Animal pp("cat","fish");
    cout << Animal(p).print() << endl;
    cout << p.print() << endl;
}
