#include <iostream>
#include <string>
using namespace std;

int EnterString(string msg) {
	int temp;
	cout << msg;
	cin >> temp;
	return temp;
}

bool isLeapYear(int num) {
	if ((num % 400) == 0)
	{
		return true;
	}
	if ((num % 4) == 0 && (num % 100) != 0)
	{
		return true;
	}
	return false;
}

int main()
{
	int userInput = EnterString("Enter The Year : ");
	cout << "\n";

	if (isLeapYear(userInput))
	{
		cout << "LEAP YEAR" << endl;
	}
	else
	{
		cout << "NOT LEAP YEAR" << endl;
	}
}