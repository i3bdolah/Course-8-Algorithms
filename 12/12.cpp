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

struct sDate
{
	int days = 1;
	int months = 1;
	int years = 1;
	int daysAdded = 0;
};

sDate DateAfterDaysAdded(sDate sDate) {
	int DaysAdded = sDate.daysAdded;

	while (true)
	{
		int currMonthDays = DaysInMonth(sDate.years, sDate.months);

		if ((DaysAdded + sDate.days) > currMonthDays)
		{
			sDate.months++;
			if (sDate.months > 12) {
				sDate.months = 1;
				sDate.years++;
			}
			DaysAdded -= currMonthDays;
		}
		else
		{
			sDate.days += DaysAdded;
			break;
		}
	}
	return sDate;
}

int main()
{
	sDate sDate;
	printf("Kindly Enter The Following Information.\n");
	sDate.days = EnterInt("Day: ");
	sDate.months = EnterInt("Month: ");
	sDate.years = EnterInt("Year: ");
	sDate.daysAdded = EnterInt("Days to be added  : ");

	sDate = DateAfterDaysAdded(sDate);
	cout << "\nDate after adding [" << sDate.daysAdded << "] days is : ";
	cout << sDate.days << "/" << sDate.months << "/" << sDate.years << endl;
}
