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

int DaysInYear(int year) {
	return isLeapYear(year) ? 366 : 365;
}

int HoursInYear(int year) {
	return DaysInYear(year) * 24;
}

int MinsInYear(int year) {
	return HoursInYear(year) * 60;
}

int SecsInYear(int year) {
	return MinsInYear(year) * 60;
}

int main()
{
	int userInput = EnterString("Enter The Year : ");
	
	cout << "\n";
	cout << "Number of Days : " << DaysInYear(userInput) << endl;
	cout << "Number of Hours : " << HoursInYear(userInput) << endl;
	cout << "Number of Mins : " << MinsInYear(userInput) << endl;
	cout << "Number of Secs : " << SecsInYear(userInput) << endl;
}