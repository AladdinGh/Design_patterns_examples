#include <iostream>
#include "FibLib.h"
int main()
{
    fibonacci_init(1,1); 

    do {
          std::cout << fibonacci_index() << ": " << fibonacci_current() << std::endl ; 
        }
    while (fibonacci_next());     


    std::cout << fibonacci_index() + 1 << "Fibo sequence fits in an unsigned 64 bit int" << std::endl ; 

    

    return(0); 
}


