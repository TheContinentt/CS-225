// your code here
#include "foo.h"
#include "bar.h"
#include <string>
#include <iostream>

using namespace std;
using namespace potd;

bar::bar(string name) {
	foo *f = new foo(name);
	f_ = f;
    //f->//foo(name);
}
bar::bar(const bar &that) 
{
	string s = (&that)->f_->get_name();
	//foo *f = this->f_;
	//f->foo(s);
	//foo::foo(s);
    	//this->name_ = that.name_;
	//bar(s);
	foo *f = new foo(s);
	this->f_ = f;
	//delete f_;
}
bar & bar::operator=(const potd::bar &that) {
	/*string s = (&that)->f_->get_name();
	foo(s);
	this->f_ = f;*/
	//bar::bar(that);
	delete f_;
	this->f_= new foo(*that.f_);
	//delete f;
    //this->name_ = that.name_;
    return *this;
}
bar::~bar()
{
	cout << "Object is being deleted" << endl;
	//delete f_;
	//f_->~foo();
	//f_ = NULL;
	//delete f_;
	delete f_;
	f_ = NULL;
}
string bar::get_name() {
	string s = f_->get_name();
    return s;
}

