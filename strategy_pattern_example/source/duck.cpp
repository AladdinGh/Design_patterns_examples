#include "../header/duck.h"
#include "../header/I_Fly_behavior.h"


c_duck::c_duck(I_Fly_Behavior *fb)
{
this->I_FB = fb ; 
}

void c_duck::print_name()
{
std::cout << "the duck flies" << this->mame; 
}

void c_duck::Execute()
{
this->I_FB->fly(); 

}
