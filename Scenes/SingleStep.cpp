#include "SingleStep.h"
#include <iostream>

void SingleStep::init()
{
    float h = 0.1f;
    std::cout << "Initial Values:\n" << std::endl;
    SpringSystem initial;
    initial.print();

    std::cout << "After 0.1s using Midpoint Method:" << std::endl;
    SpringSystem midpoint;
    midpoint.midpointStep(h);
    midpoint.print();

    std::cout << "After 0.1s using Euler Method:" << std::endl;
    SpringSystem euler;
    euler.eulerStep(h);
    euler.print();

    springSystem = SpringSystem();
}
