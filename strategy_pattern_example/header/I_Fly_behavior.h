#ifndef _header
#define _header

#include <string>


class I_Fly_Behavior 
{

public:
    I_Fly_Behavior(){};
    ~I_Fly_Behavior(){}; 

//protected :     
    virtual void fly() = 0 ;  
    std::string name ; 
}; 

#endif 