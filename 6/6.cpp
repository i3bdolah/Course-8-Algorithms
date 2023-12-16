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
	return ((num % 400) == 0) || ((num % 4) == 0 && (num % 100) != 0);
}

int DaysInMonth(int enteredYear, int enteredMonth) {
	int NumberOfDaysInAllMonths[12] = {31, (isLeapYear(enteredYear) ? 29 : 28), 31, 30, 31, 30, 31 ,31, 30, 31, 30, 31 };
	return NumberOfDaysInAllMonths[enteredMonth - 1];
}

int HoursInMonth(int enteredYear, int enteredMonth) {
	return DaysInMonth(enteredYear, enteredMonth) * 24;
}

int MinsInMonth(int enteredYear, int enteredMonth) {
	return HoursInMonth(enteredYear, enteredMonth) * 60;
}

int SecsInMonth(int enteredYear, int enteredMonth) {
	return MinsInMonth(enteredYear, enteredMonth) * 60;
}

int main()
{
	int inputYear = EnterString("Enter The Year : ");
	int inputMonth = EnterString("Enter The Month : ");

	cout << "\n";
	cout << "Number of Days in Month  ["<< inputMonth << "] : " << DaysInMonth(inputYear, inputMonth) << endl;
	cout << "Number of Hours in Month [" << inputMonth << "] : " << HoursInMonth(inputYear, inputMonth) << endl;
	cout << "Number of Mins in Month  [" << inputMonth << "] : " << MinsInMonth(inputYear, inputMonth) << endl;
	cout << "Number of Secs in Month  [" << inputMonth << "] : " << SecsInMonth(inputYear, inputMonth) << endl;
}