//#include "event.hpp"
//#include "simulation.hpp"

#include <iostream>
#include <string>

#include "item.hpp"
#include "system.hpp"
#include "simulation.hpp"
#include "parallelsys.hpp"

using std::cout;

int main(){

std::cout << "besm allah" << "\n";

simulation* sim = new simulation();

item* separator = new item("separator");
item* boostPump = new item("boostPump");
item* molPump1 = new item("pump1");
item* molPump2 = new item("pump2");
item* molPump3 = new item("pump3");
item* molPump4 = new item("pump4");
item* tank = new item("tank");
item* pipe = new item("pipe");

psys* molPump = new psys("molPump");
molPump->setMinReqItems(1);

sys* pumps1 = new sys();
sys* pumps2 = new sys();
pumps1->addItem("pump1",molPump1);
pumps1->addItem("pump2",molPump2);
pumps2->addItem("pump1",molPump1);
pumps2->addItem("pump4",molPump4);

molPump->addItem("pumps1", pumps1);
molPump->addItem("pumps2", pumps2);

sys* upstreamSys = new sys("upstreamSys");
upstreamSys->addItem("separator",separator);
upstreamSys->addItem("boostPump",boostPump);
upstreamSys->addItem("molPump",molPump);
upstreamSys->addItem("tank",tank);
upstreamSys->addItem("pipe",pipe);

//separator->fail();
//upstreamSys->fail();
//molPump->stop();
sim->setSimulationBoundary(upstreamSys);
//sim->run();
cout<<"molpump1 fail \n";
molPump1->fail();
//separator->repiared();
sim->run();
cout<<"molpump1 repaired \n";
molPump1->repiared();
sim->run();
cout<<"molpump4 fail \n";
molPump4->fail();
sim->run();
cout<<"molpump2 fail \n";
molPump2->fail();
sim->run();

separator->printLog(); cout << std::endl;
boostPump->printLog(); cout << std::endl;
molPump1->printLog(); cout << std::endl;
molPump2->printLog(); cout << std::endl;
molPump3->printLog(); cout << std::endl;
molPump4->printLog(); cout << std::endl;
tank->printLog(); cout << std::endl;
pipe->printLog(); cout << std::endl;
pumps1->printLog(); cout << std::endl;
pumps2->printLog(); cout << std::endl;
molPump->printLog(); cout << std::endl;
upstreamSys->printLog(); cout << std::endl;

return 0;

}
