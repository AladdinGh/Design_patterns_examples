
#include "./header/duck.h"
#include "./header/distant_fly.h"
#include "./header/close_fly.h"

int main ()
{


c_duck * highduck = new c_duck(new c_distant_fly());

c_duck * lowduck = new c_duck(new c_close_fly()); 


highduck->Execute(); 
lowduck->Execute(); 
return(0); 

}

