#ifndef EVENT_CLASS
#define EVENT_CLASS
class event
{
private:
    /* data */
public:
    //constract set time of events
    event(unsigned int t): time(t){}

    //execute event by invoking this method

    int id;
    const unsigned int time;
    ~event();
};


struct eventComparator
{
    /* this function used for  priority qued to sort events  */
    bool operator()(const event *left,const event *right) const {
     return left->time > right->time;   
    }
};
#endif
