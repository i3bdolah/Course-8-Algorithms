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

void PrintMonthCalendar(int year, int month) {
	int NumberOfDaysInMonth = DaysInMonth(year, month);
	int DayOrder = GetDayOrder(year, month, 1);

	printf("\n  _______________%s_______________\n\n", GetMonthNameByOrder(month).c_str());

	printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

	int i;
	for (i = 0; i < DayOrder; i++)
		printf("     ");

	for (int j = 1; j <= NumberOfDaysInMonth; j++)
	{
		printf("%5d", j);

		if (++i == 7)
		{
			i = 0;
			printf("\n");
		}
	}

	printf("\n  _________________________________\n");
}

void PrintFullYearCalendar(int year) {
	printf("\n  ________________________________\n\n");
	printf("\n	_________Calendar Year__________\n\n");
	printf("\n  ________________________________\n\n");

	for (int month = 1; month <= 12; month++)
	{
		PrintMonthCalendar(year, month);
	}
}

int PrintTotalFromBeginning(int year, int month, int day) {
	int TotalNumberOfDays = 0;
	for (int currMonth = 1; currMonth < month; currMonth++)
	{
		TotalNumberOfDays += DaysInMonth(year, currMonth);
	}
	TotalNumberOfDays += day;

	return TotalNumberOfDays;
}

struct sDateFromTotalDays
{
	int days = 1;
	int months = 1;
	int years = 1;
};

sDateFromTotalDays PrintDateOfTotalFromBeginning(int TotalNumberOfDays, int year) {
	sDateFromTotalDays sDate;
	int remainingDays = TotalNumberOfDays;
	sDate.years = year;

	while (true)
	{
		int currMonthDays = DaysInMonth(sDate.years, sDate.months);

		if (remainingDays > currMonthDays) {
			remainingDays -= currMonthDays;
			sDate.months++;
		}
		else {
			sDate.days = remainingDays;
			break;
		}
	}

	return sDate;
}

int main()
{
	printf("Kindly Enter The Following Information.\n");
	int day = EnterInt("Day   : ");
	int month = EnterInt("Month : ");
	int year = EnterInt("Year  : ");
	int TotalNumberOfDays = PrintTotalFromBeginning(year, month, day);

	cout << "\nNumber Of Days form The Beginning of The Year is ";
	cout << TotalNumberOfDays << endl;

	sDateFromTotalDays sDate;
	sDate = PrintDateOfTotalFromBeginning(TotalNumberOfDays, year);
	cout << "\nDate for [" << TotalNumberOfDays << "] is: ";
	cout << sDate.days << "/" << sDate.months << "/" << sDate.years << endl;


}
