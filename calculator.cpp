#include <iostream>
#include <string>

#include "calculatorFunc.h"
using namespace std;

string cal_target = "2*(30+1)-6*5*(12/2)+(3*2)*2";

int main()
{
	int result;

	cout << cal_target <<endl ;

	result = calculatorManager(cal_target, 0, 0);

	cout << "result is " << result << endl;

	return 0;
}
