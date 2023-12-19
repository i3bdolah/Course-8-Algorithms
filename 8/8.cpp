#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int EnterInt(string msg) {
	int temp;
	cout << msg;
	cin >> temp;
	return temp;
}

bool isLeapYear(int num) {
	return ((num % 400) == 0) || ((num % 4) == 0 && (num % 100) != 0);
}

int DaysInMonth(int enteredYear, int enteredMonth) {
	int NumberOfDaysInAllMonths[12] = { 31, (isLeapYear(enteredYear) ? 29 : 28), 31, 30, 31, 30, 31 ,31, 30, 31, 30, 31 };
	return NumberOfDaysInAllMonths[enteredMonth - 1];
}

int GetDayOrder(int year, int month, int day) {
	int a = (14 - month) / 12;
	int y = year - a;
	int m = month + (12 * a) - 2;

	int d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	return d;
}

string GetMonthNameByOrder(int monthOrder) {
	string MonthsByIndex[12] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	return MonthsByIndex[monthOrder - 1];
}

string GetDayNameByOrder(int dayOrder) {
	string DaysByIndex[7] = {
		"Sun",
		"Mon",
		"Tue",
		"Wed",
		"Thu",
		"Fri",
		"Sat" };

	return DaysByIndex[dayOrder];
}

void PrintMonthAndDaysRows(int month) {
	cout << "_____________" << GetMonthNameByOrder(month) << "____________" << endl;
	cout << "\n";
	for (int i = 0; i < 7; i++)
	{
		cout << setw(4) << GetDayNameByOrder(i);
	}
	cout << "\n";
	cout << "\n";

}

void PrintCalendarArray(string CalendarArr[6][7], int rows, int cols) {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << setw(4) << CalendarArr[i][j];
		}
		cout << "\n";
	}
}

void PrintDateDetails(int year, int month) {
	int totalNumOfDays = DaysInMonth(year, month);
	string CalendarArr[6][7] = {
		{" ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " "},
	};
	int daysCounter = 1;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (daysCounter == 1) {
				j = GetDayOrder(year, month, 1);
			}
			if (daysCounter > totalNumOfDays) {
				break;
			}

			CalendarArr[i][j] = to_string(daysCounter);
			daysCounter++;
		}
	}

	// Printing
	PrintMonthAndDaysRows(month);
	PrintCalendarArray(CalendarArr, 6, 7);
	cout << "_____________" << "____" << "____________" << endl;
}

int main()
{
	int year = EnterInt("Enter The Year : ");
	int month = EnterInt("Enter The Month [1-12] : ");

	PrintDateDetails(year, month);
}