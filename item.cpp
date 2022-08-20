//implement of item functions
//
#include <iostream>
#include <iomanip>

#include "item.hpp"


void item::addLog(int clock, Event e, Status s){

    log* l = new log();
    l->clock = clock;
    l->event = e;
    l->status = s;

    logBook.push_back(l);
}

void item::printLog(){
    std::cout<< "system: " << itemType << std::setw(10) << "id :" << id << std::endl;
    std::cout<< "Clock"<< std::setw(10) << "Event" << std::setw(10) << "Status \n";
    for(auto& i : logBook){
        std::cout << i->clock << std::setw(10);
        std::cout << (int)i->event << std::setw(10);
        std::cout << (int)i->status << std::endl ;
    }
}

void item::stop(){
    if(getStatus() == Status::working) {
        workingHrs += (clock - logBook.back()->clock);
        status = Status::available;
        addLog(clock,Event::stop,Status::available);
    }
} 

int item::start(){
    if(getStatus()== Status::available){
      availableHrs += (clock - logBook.back()->clock);
      status = Status::working;
      addLog(clock, Event::start,status);
      return 1;
      }else if(getStatus()== Status::working) return 1;
    else return 0; //return will be used in future to test fail to start 
    }

Status item::getStatus(){return status;}

void item::fail(){
    if(getStatus() == Status::working) {
        workingHrs += (clock - logBook.back()->clock);
        status = Status::unavailable;
        addLog(clock,Event::fail,status);
    } else if(status == Status::available){
      availableHrs += (clock - logBook.back()->clock);
      status = Status::unavailable;
      addLog(clock, Event::fail,status);
      } 
   
}

void item::repiared(){
    if(getStatus()== Status::unavailable){
        unavailableHrs += (clock - logBook.back()->clock);
        status = Status::available;
        addLog(clock,Event::repaired,status);
    }

}

