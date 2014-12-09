#include <iostream>
#include <string>
#include <cstring>

#include "calculatorFunc.h"

using namespace std;

int funNum = 0, curPos = 0;

int calculatorManager(string tg, int st, char prevOper)
{
	int x=0, y=0, rsltVar = 0;
	char oper = 0x00, nextOper = 0x00;

	funNum ++;
	cout << " Start Function [" << funNum << "] \n";

	while (curPos < tg.length()) {

		if (checkEntity(tg, curPos) == 'N') {

			if (checkEntity(tg,curPos-1) == 'S' && tg[curPos-1] == '-') {
				if (oper == 0x00)
					x = -1*(tg[curPos]-48);
				else
					y = -1*(tg[curPos]-48);
			} else {

				if (oper == 0x00)
					x = x * 10 + (tg[curPos]-48);
				else
					y = y * 10 + (tg[curPos]-48);
			}			

			rsltVar = x;
			cout << "tg[" << curPos <<"] Number " << x << ' ' << oper << ' ' << y << endl;

			if (oper != 0x00 && checkEntity(tg, curPos+1) != 'N' ) {
				nextOper = findNextOper(tg, curPos);
				cout << " Next Operator is " << nextOper << endl;

				if (checkPriority(oper, nextOper) < 0) {
					
					cout << "checkPriority -> " << checkPriority(oper, nextOper) << endl;
					y = calculatorManager(tg, curPos, oper);

				}

				rsltVar = calculator(x, y, oper);

				x = rsltVar ;
				oper = 0;
				nextOper = 0;
				y = 0;
			}

		} else if (checkEntity(tg, curPos) == 'O') {
			
			oper = tg[curPos];
			cout << "tg[" << curPos <<"] Operator " << x << ' ' << oper << ' ' << y << endl;

		} else if (checkEntity(tg, curPos) == 'S') {

			cout << "tg[" << curPos <<"] Signal " << tg[curPos] << endl;
		
		} else if (checkEntity(tg, curPos) == '(') {

			cout << "tg[" << curPos <<"] openParenthe " << tg[curPos] << endl;

			char sign = 0x00;

			if (checkEntity(tg, curPos-1) == 'S') 
				sign = tg[curPos-1];

			rsltVar = calculatorManager(tg, curPos++, oper);

			if (sign != 0x00 && sign == '-')
				rsltVar = -1 * rsltVar;

			if (oper == 0x00) {

				x = rsltVar;

			} else {
				
				y = rsltVar;
				
				rsltVar = calculator(x, y, oper);	
				
				nextOper = findNextOper(tg, curPos+1);

			}			

			if (prevOper != 0x00 && checkPriority(prevOper, nextOper) == 0) {
				cout << " #check " << prevOper << ' ' << oper << ' ' << nextOper << endl;
				break;
			}

			x = rsltVar;
			oper = 0;
			nextOper = 0;
			y = 0;			
		
		} else if (checkEntity(tg, curPos) == ')') {
			cout << "tg[" << curPos <<"] closeParenthe " << tg[curPos] << endl;

			nextOper = findNextOper(tg, curPos+1);
			cout << " #check2 prevOper = " << prevOper << ", oper = " << oper << ", nextOper = " << nextOper << endl;
			cout << "checkPriority = " << checkPriority(prevOper, nextOper) << endl;

			if (checkPriority(prevOper, nextOper) >= 0) {
				cout << " break..\n";
				break;
			}

		}

		curPos++;
	}

	cout << "function [" << funNum << "] return [ " << rsltVar << " ] \n";
	funNum --;
	return rsltVar;
}

/* if nextOper is Greater than oper, return value is '-1' */
int checkPriority(char oper, char nextOper)
{
	if ((oper == '+' || oper == '-') && (nextOper == '+' || nextOper == '-')) {
		return 0;
	
	} else if ((oper == '+' || oper == '-') && (nextOper == '*' || nextOper == '/')) {
		return -1;
	
	} else if ((oper == '*' || oper == '/') && (nextOper == '+' || nextOper == '-')) {
		return 1;
	
	} else if ((oper == '*' || oper == '/') && (nextOper == '*' || nextOper == '/')) {
		return 0;
	
	} else if (nextOper == '(') {
		return -1;
	}

	return 0;
}

char checkEntity(string ce, int pt)
{
	char entityType = 0;

	if (ce[pt] >= '0' && ce[pt] <= '9') {

		entityType = 'N';

	} else if (ce[pt] == '(' || ce[pt] == ')') {

		entityType = ce[pt];

	} else {

		if (pt==0 || ((ce[pt-1] < '0' || ce[pt-1] > '9') && ce[pt-1] == '(')) {			
			entityType = 'S';
		} else {
			entityType = 'O';
		}
	}			
	
	return entityType;
}

char findNextOper(string no, int pt)
{
	int i = pt ;

	while (checkEntity(no, i) != 'O') {		
		if (checkEntity(no, i) == '(' || checkEntity(no, i) == ')')
			break;
		i++;
	}

	return no[i];
}

char findPrevOper(string no, int pt)
{
	int i = pt;
	int operCount = 0;

	while (true) {		
		if (checkEntity(no, i) == 'O') {
			operCount = operCount + 1;
			
			if (operCount >= 2)
				break;
		}
		i--;
	}

	return no[i];
}

int calculator(int x, int y, char oper)
{
	int rsltVar = 0;

	switch(oper) {
	case '+' :
		rsltVar = x + y;
		break;
	case '-' :
		rsltVar = x - y;
		break;
	case '*' :
		rsltVar = x * y;
		break;
	case '/' :
		rsltVar = x / y;
		break;
	default :
		break;
	}

	return rsltVar;
}