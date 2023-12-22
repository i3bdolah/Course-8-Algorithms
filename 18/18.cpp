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

int CalcDatesDifference(sDate sDate1, sDate sDate2, bool IncludeEndDay = false) {
	int diff = 0;
	while (!IsDatesEquals(sDate1, sDate2))
	{
		sDate1 = IncreaseDateByOneDay(sDate1);
		diff++;
	}
	return IncludeEndDay ? ++diff : diff;
}

sDate GetSystemDate() {
	sDate sDate;

	time_t t = time(0);
	tm* now = localtime(&t);

	sDate.years = now->tm_year + 1900;
	sDate.months = now->tm_mon + 1;
	sDate.days = now->tm_mday;

	return sDate;
}

int CalcAgeInDays(sDate sDateAge) {
	sDate sDateCurrent = GetSystemDate();
	return CalcDatesDifference(sDateAge, sDateCurrent);
}


int main()
{
	sDate sDate;

	printf("\nPlease Enter Your Date of Birth : -\n");
	sDate = FillDateInfo();

	cout << "\nYour Age is: " << CalcAgeInDays(sDate) << " Day(s)." << endl;
}
