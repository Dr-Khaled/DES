#ifndef ITEM_CLASS
#define ITEM_CLASS
//item is blue print for all other class
#include <string>
#include <vector>

enum class Status{unavailable,available,working};
enum class Event{stop,start,fail,repaired};
struct log{
    Event event;
    Status status;
    int clock;
};

using std::string;


class item
{
protected:
    /* data */
    int clock; // synchronise with global clock
    int workingHrs; // keep track of operating hours
    int availableHrs;
    int unavailableHrs;
    string itemType;
    Status status;// register current state of item
    std::string id;  	 
    std::vector<log*> logBook;

    int capacity;// register current capacity
    int designCapacity;
    float failureRate;
    
public:
    item(): clock{0}, workingHrs{0}, availableHrs(0), 
    unavailableHrs(0),status{Status::working}, itemType("item") {
        addLog(clock,Event::start,status);
    }
    item(string name):item() {
        id = name;
    }
    virtual void stop(); 
    virtual int start();
    virtual void fail();
    void repiared();

    item getNextEvent() ;
    virtual Status getStatus();
    void setStatus(Status s){status = s;}
    void addLog(int clock, Event e, Status s);
    void printLog();

    virtual ~item(){}
};





#endif