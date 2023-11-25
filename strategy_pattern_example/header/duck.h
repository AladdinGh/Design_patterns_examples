#include <iostream>
#include <string>
#include "I_Fly_behavior.h"

class c_duck
{
public: 
    c_duck(I_Fly_Behavior *fb); 
    std::string mame; 
    void print_name (); 
    void Execute(); 

private : 
    I_Fly_Behavior * I_FB; 
    

}; 

