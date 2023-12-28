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

short EnterShort(string msg) {
	short temp;
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

struct sPeriod
{
	sDate start;
	sDate end;
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

bool IsDate1BeforeDate2(sDate sDate1, sDate sDate2) {
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

int ActualVacationDays(sDate start, sDate end) {
	int BusinessDaysSum = 0;
	while (!IsDatesEquals(start, end))
	{
		if (IsBusinessDay(GetDayOrder(start)))	BusinessDaysSum++;
		start = IncreaseDateByOneDay(start);
	}
	return BusinessDaysSum;
}

sDate CalcReturnDate(sDate start, short vacationDays) {
	short WeekendCounter = 0;

	for (short i = 1; i <= vacationDays + WeekendCounter; i++)
	{
		if (IsWeekend(GetDayOrder(start))) WeekendCounter++;
		start = IncreaseDateByOneDay(start);
	}

	while (IsWeekend(GetDayOrder(start))) start = IncreaseDateByOneDay(start);

	return start;
}

void SwapTwoDates(sDate& sDate1, sDate& sDate2) {
	sDate sDateTemp;

	sDateTemp.days = sDate1.days;
	sDateTemp.months = sDate1.months;
	sDateTemp.years = sDate1.years;

	sDate1.days = sDate2.days;
	sDate1.months = sDate2.months;
	sDate1.years = sDate2.years;

	sDate2.days = sDateTemp.days;
	sDate2.months = sDateTemp.months;
	sDate2.years = sDateTemp.years;
}

int CalcDatesDifference(sDate sDate1, sDate sDate2, bool IncludeEndDay = false) {
	int diff = 0;
	int swapFlag = 1;

	if (!IsDate1BeforeDate2(sDate1, sDate2))
	{
		swapFlag = -1;
		SwapTwoDates(sDate1, sDate2);
	}

	while (IsDate1BeforeDate2(sDate1, sDate2))
	{
		sDate1 = IncreaseDateByOneDay(sDate1);
		diff++;
	}

	return (IncludeEndDay ? ++diff : diff) * swapFlag;
}

bool IsDate1AfterDate2(sDate date1, sDate date2) {
	return !IsDate1BeforeDate2(date1, date2) && !IsDatesEquals(date1, date2);
}

short CompareDates(sDate date1, sDate date2) {
	if (IsDate1BeforeDate2(date1, date2)) return -1;
	if (IsDatesEquals(date1, date2)) return 0;
	return 1;
}

void ReadPeriod(sPeriod per) {
	cout << "- Period Start\n\n";
	per.start = FillDateInfo();

	cout << "\n\n";

	cout << "- Period End\n\n";
	per.end = FillDateInfo();
}

// My Solution, Which is Impressive!
bool IsPeriodsOverlapped(sPeriod per1, sPeriod per2) {
	if (per1.end.years >= per2.start.years)
	{
		if (per1.end.months >= per2.start.months)
		{
			if (per1.end.days >= per2.start.days)
			{
				return true; // True
			}
			return false;
		}
		return false;
	}
	return false;
}

bool IsPeriodsOverlappedShort(sPeriod per1, sPeriod per2) {
	return (per1.end.years >= per2.start.years && per1.end.months >= per2.start.months && per1.end.days >= per2.start.days);
}

bool AbuHaddHoudOverlap(sPeriod per1, sPeriod per2) {
	return !(IsDate1AfterDate2(per2.start, per1.end) || IsDate1BeforeDate2(per2.end, per1.start));
}

int PeriodLengthInDays(sPeriod per, bool IncludeEndDay = false) {
	return CalcDatesDifference(per.start, per.end, IncludeEndDay);
}

int main()
{
	sPeriod period1;

	//printf("DATE #1\n");
	//ReadPeriod(period1);
	//cout << "\n________________\n";
	//printf("DATE #2\n");
	//ReadPeriod(period2);


		// First period: January 1, 2023 - January 10, 2023
	period1.start.days = 1;
	period1.start.months = 1;
	period1.start.years = 2023;
	period1.end.days = 10;
	period1.end.months = 1;
	period1.end.years = 2023;

	cout << "\n\n";

	cout << "Period Length is: " << PeriodLengthInDays(period1) << endl;
	cout << "Period Length is (Include End Date): " << PeriodLengthInDays(period1, true) << endl;

}

