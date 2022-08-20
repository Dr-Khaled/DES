#include "item.hpp"
#include <vector>

class seriesSys : public item
{
private:
   std::vector<item> subSystem;
 
public:
    seriesSys(/* args */);
    ~seriesSys();
};

seriesSys::seriesSys(/* args */)
{
}

seriesSys::~seriesSys()
{
}
