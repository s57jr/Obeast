#include "basicwarmup.h"
#include <string>

basicWarmUp::basicWarmUp(int a, std::string b):exerciseBase(a)
{
    std::cout << "Hello basicWarmUp! with variable :  " << b <<  std::endl;
}