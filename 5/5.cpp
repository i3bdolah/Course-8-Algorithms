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
	if (enteredMonth < 1 || enteredMonth > 12) return 0;

	if (enteredMonth == 2) return isLeapYear(enteredYear) ? 29 : 28;

	int months_31Days[7] = { 1, 3, 5, 7, 8, 10, 12 };
	for (int i = 0; i <= 7; i++)
		if (months_31Days[i] == enteredMonth) return 31;

	return 30;
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
	cout << "Number of Days : " << DaysInMonth(inputYear, inputMonth) << endl;
	cout << "Number of Hours : " << HoursInMonth(inputYear, inputMonth) << endl;
	cout << "Number of Mins : " << MinsInMonth(inputYear, inputMonth) << endl;
	cout << "Number of Secs : " << SecsInMonth(inputYear, inputMonth) << endl;
}