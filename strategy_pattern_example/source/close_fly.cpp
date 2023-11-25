#include "../header/close_fly.h"


c_close_fly::c_close_fly()
{
    this->name = "closely" ; 
}
void c_close_fly::fly () 
{
    std::cout << "this duck flies " << this->name  << std::endl ; 
} 
