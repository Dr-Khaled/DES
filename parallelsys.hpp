#ifndef PSYS_CLASS
#define PSYS_CLASS

#include "system.hpp"

class psys : public sys
{
protected:
    int minReqItems;

public:
    psys():minReqItems(0){
      itemType = "parallelSys";
      }
    psys(string name):psys(){
      id = name;
    }
    virtual Status getStatus ();
    virtual int start();
    void setMinReqItems(int i){minReqItems = i;}
    ~psys(){sys::~sys();}
};

Status psys::getStatus(){
  int unavailableItem = 0, availableItem = 0 , workingItem = 0;
          for (auto x =subSystems.begin();x != subSystems.end(); x++)
         {
           switch (x->second->getStatus())
           {
            case Status::unavailable:unavailableItem++; 
            break;
            case Status::available: availableItem++;
            break;
            case Status::working: workingItem++;
            break;
           }

          }

        if(workingItem == minReqItems) return status = Status::working;
        else if (availableItem+workingItem >= minReqItems)
            return status = Status::available;
        else{
            fail();
            return status;
          }
         }

int psys::start(){
    int index = 0;
    if(getStatus() == Status::available){ 
      for(auto x = subSystems.begin(); x != subSystems.end() || (index == minReqItems); x++){
        if(x->second->start()) index++;
        } 
      if(index<minReqItems) return 0;
      availableHrs += (clock - logBook.back()->clock);
      status = Status::working;
      addLog(clock, Event::start,status);
     return 1;
    } else if(getStatus() == Status::working) return 1;
      else return 0;
}

#endif