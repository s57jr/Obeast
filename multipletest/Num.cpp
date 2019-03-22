#include <iostream>
#include "Num.h"
using namespace std;

Num::Num()
	{
		intnum = 0;
		cout << "created with intnum = 0";
	}

Num::Num(int n)
{
	intnum = n;
	cout << "created with and int";
}

int Num::getNum()
{
 return intnum;
} 
