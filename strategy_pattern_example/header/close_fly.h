#include "I_Fly_behavior.h"
#include <string>
#include <iostream>

class c_close_fly : public I_Fly_Behavior 
{
public :
    c_close_fly() ;
    ~c_close_fly(){};
    void fly () ; 
}; 