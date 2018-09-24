#include <iostream>
#include "Chara.h"
using namespace std;


int main() {
  Chara q;
  string r;

  cout<<"enqueue(3) to the queue..."<<endl;
  q.addToQueue("jack");
  cout<<"Queue size: "<<q.size()<<endl;

  cout<<"enqueue(2) to the queue..."<<endl;
  q.addToQueue("Bob");
  cout<<"Queue size: "<<q.size()<<endl;

  cout<<"enqueue(1) to the queue..."<<endl;
  q.addToQueue("Tom");
  cout<<"Queue size: "<<q.size()<<endl;


  cout<<"dequeue()"<<endl;
  r = q.popFromQueue();
  cout<<"Returned Value: "<<r<<", Queue size: "<<q.size()<<endl;

  cout<<"dequeue()"<<endl;
  r = q.popFromQueue();
  cout<<"Returned Value: "<<r<<", Queue size: "<<q.size()<<endl;

  cout<<"dequeue()"<<endl;
  r = q.popFromQueue();
  cout<<"Returned Value: "<<r<<", Queue size: "<<q.size()<<endl;

  return 0;
}
