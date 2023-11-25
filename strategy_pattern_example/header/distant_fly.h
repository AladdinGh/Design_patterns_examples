#include "I_Fly_behavior.h"
#include <string>
#include <iostream>

class c_distant_fly : public I_Fly_Behavior 
{
public :
    c_distant_fly() ;
    ~c_distant_fly(){};
    void fly () ; 
};