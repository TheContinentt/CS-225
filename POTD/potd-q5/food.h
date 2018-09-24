// Your code here
#ifndef food_H
#define food_H
#include <string>
//#include "circle.h"

using namespace std;

class food
{
  public:
	food();
	void set_name(string newName);
	string get_name();
	void set_quantity(int newQuantity);
	int get_quantity();

  private:
	string name_;
	int quantity_;
};

#endif
