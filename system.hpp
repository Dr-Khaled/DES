#ifndef SYS_CLASS
#define SYS_CLASS

#include "item.hpp"
#include <map>
#include <string>

using std::string;

class sys : public item
{
protected:
    std::map<string, item*> subSystems;

public:
    sys(){
      itemType = "seriesSys";
      }
    sys(string name): sys(){
      id =name;
    }
    void addItem(string id, item* i){subSystems.insert({id,i});}
    void removeItem(string id){subSystems.erase(id);}
    virtual Status getStatus();
    virtual int start();
    virtual void stop();
    virtual void fail();
    virtual ~sys(){item::~item();}
};



Status sys::getStatus(){
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

          if(unavailableItem > 0){
            sys::fail();
            return status ;
          }else if (availableItem > 0) return status = Status::available;
          else return status = Status::working;
           
}
         
int sys::start(){
            if(getStatus()== Status::available){
            for(auto x = subSystems.begin(); x != subSystems.end(); x++) 
              if(!x->second->start()) return 0;
              availableHrs += (clock - logBook.back()->clock);
              status = Status::working;
              addLog(clock, Event::start,status);
              return 1;
            }else if(getStatus() == Status::working) return 1;
            else return 0;
}

void sys::stop(){
    if(getStatus()==Status::working){
       for(auto x = subSystems.begin(); x != subSystems.end(); x++) 
            x->second->stop();
        workingHrs += (clock - logBook.back()->clock);
        status = Status::available;
        addLog(clock,Event::stop,Status::available);
    }
}

void sys::fail(){
   for(auto x = subSystems.begin(); x != subSystems.end(); x++) 
         x->second->stop();

    if(status == Status::working) {
        workingHrs += (clock - logBook.back()->clock);
        status = Status::unavailable;
        addLog(clock,Event::fail,status);
    } else if(status == Status::available){
      availableHrs += (clock - logBook.back()->clock);
      status = Status::unavailable;
      addLog(clock, Event::fail,status);
      } 
   
}

#endif