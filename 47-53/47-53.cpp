#pragma warning(disable : 4996)
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

struct sDate
{
	int days = 1;
	int months = 1;
	int years = 1;
};

sDate FillDateInfo() {
	sDate sDate;
	sDate.days = EnterInt("Day: ");
	sDate.months = EnterInt("Month: ");
	sDate.years = EnterInt("Year: ");
	return sDate;
}

bool isLeapYear(int num) {
	return ((num % 400) == 0) || ((num % 4) == 0 && (num % 100) != 0);
}

int DaysInMonth(int enteredYear, int enteredMonth) {
	int NumberOfDaysInAllMonths[12] = { 31, (isLeapYear(enteredYear) ? 29 : 28), 31, 30, 31, 30, 31 ,31, 30, 31, 30, 31 };
	return NumberOfDaysInAllMonths[enteredMonth - 1];
}

bool IsLastDay(sDate sDate) {
	return (sDate.days == DaysInMonth(sDate.years, sDate.months));
}

bool IsLastMonth(int month) {
	return (month == 12);
}

bool IsDate1LessDate2(sDate sDate1, sDate sDate2) {
	if (sDate1.years < sDate2.years) {
		return true;
	}
	else if (sDate1.years == sDate2.years) {
		if (sDate1.months < sDate2.months)
			return true;
		else if (sDate1.days < sDate2.days)
			return true;
	}
	return false;
}

bool IsDatesEquals(sDate sDate1, sDate sDate2) {
	return (sDate1.years == sDate2.years && sDate1.months == sDate2.months && sDate1.days == sDate2.days);
}

sDate IncreaseDateByOneDay(sDate sDate) {
	if (IsLastDay(sDate)) {
		sDate.days = 1;

		if (IsLastMonth(sDate.months)) {
			sDate.months = 1;
			sDate.years++;
		}
		else {
			sDate.months++;
		}
	}
	else
	{
		sDate.days++;
	}

	return sDate;
}

sDate DecreaseDateByOneDay(sDate sDate) {
	if (IsLastDay(sDate)) {
		sDate.days = 1;

		if (IsLastMonth(sDate.months)) {
			sDate.months = 1;
			sDate.years++;
		}
		else {
			sDate.months++;
		}
	}
	else
	{
		sDate.days++;
	}

	return sDate;
}

void PrintDate(sDate date) {
	cout << date.days << "/" << date.months << "/" << date.years << endl;
}

string GetDayNameByOrder(int dayOrder) {
	string DaysByIndex[7] = {
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday" };

	return DaysByIndex[dayOrder];
}

// Questions Begins

int GetDayOrder(sDate date) {
	int a = (14 - date.months) / 12;
	int y = date.years - a;
	int m = date.months + (12 * a) - 2;

	int d = (date.days + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	return d;
}

bool isEndOfWeek(int dayOrder) {
	return (dayOrder == 6);
}

bool IsWeekend(int dayOrder) {
	return (dayOrder == 5 || dayOrder == 6);
}

bool IsBusinessDay(int dayOrder) {
	return !IsWeekend(dayOrder);
}

int DaysUntilEndOfWeek(int dayOrder) {
	return (7 - (dayOrder + 1));
}

int DaysUntilEndOfMonth(sDate date) {
	return DaysInMonth(date.years, date.months) - date.days;
}

int DaysUntilEndOfYear(sDate date) {
	int sum = DaysUntilEndOfMonth(date);
	date.months++;

	while (date.months <= 12)
	{
		sum += DaysInMonth(date.years, date.months);
		date.months++;
	}
	return sum;
}

int main()
{
	sDate date;

	printf("\n");
	date = FillDateInfo();
	int dayOrder = GetDayOrder(date);

	cout << "\n\n" << "Today is " << GetDayNameByOrder(dayOrder) << ", ";
	PrintDate(date);
	cout << "\n\n";

	printf("Is it End of Week?\n");
	if (isEndOfWeek(dayOrder))
		printf("Yes, It is End of Week\n");
	else
		printf("No, It is not End of Week\n");

	printf("\n");

	printf("Is it Weekend?\n");
	if (IsWeekend(dayOrder))
		printf("Yes, It is Weekend\n");
	else
		printf("No, It is not Weekend\n");

	printf("\n");

	printf("Is it Business Day?\n");
	if (IsBusinessDay(dayOrder))
		printf("Yes, It is Business Day\n");
	else
		printf("No, It is not Business Day\n");

	printf("\n");

	cout << "Days Until End Of Week : " << DaysUntilEndOfWeek(dayOrder) << " Day(s).\n";
	cout << "Days Until End Of Month : " << DaysUntilEndOfMonth(date) << " Day(s).\n";
	cout << "Days Until End Of Year : " << DaysUntilEndOfYear(date) << " Day(s).\n";
}
