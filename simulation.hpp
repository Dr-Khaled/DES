#ifndef SIM_CLASS
#define SIM_CLASS

#include <string>
#include <iostream>
#include <map>

#include "item.hpp"
#include "system.hpp"
#include "parallelsys.hpp"


using std::string;
using std::cout;

class simulation
{
protected:
  int clock;
  std::map<string, item*> itemsList;
  item* simBounday;
         
public:
    simulation(/* args */): clock(0){} 

    void run();

    void addItem(string id, item* i){itemsList.insert({id,i});}
    void setSimulationBoundary(item *i){simBounday = i;}
    ~simulation();

};

//managing extract event from priority queue list, update simulation time and initiate event process
void simulation::run(){
   switch(simBounday->getStatus()){
       case Status::unavailable:{
         cout<<"system unavailable \n";
         //cout<<"stop subsystem \n";
         //simBounday->stop();
         }
        break;
        case Status::available:{
          cout<<"system available \n";
          cout<<"system Started \n";
          if(simBounday->start()) cout << "system start successfully \n";
          }
        break;
        case Status::working: cout<<"system working \n";
        break;
   }

   }
    

#endif
