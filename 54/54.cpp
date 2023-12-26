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

int main()
{
	sDate VacationDateSatrt, VacationDateEnd;

	printf("\nVacation Start\n");
	VacationDateSatrt = FillDateInfo();

	printf("\nVacation End\n");
	VacationDateEnd = FillDateInfo();
	cout << "\n";

	cout << "Vacation From : " << GetDayNameByOrder(GetDayOrder(VacationDateSatrt)) << " ";
	PrintDate(VacationDateSatrt);
	cout << "Vacation To : " << GetDayNameByOrder(GetDayOrder(VacationDateEnd)) << " ";
	PrintDate(VacationDateEnd); cout << "\n\n";

	cout << "Actual Vacation Days is: ";
	cout << ActualVacationDays(VacationDateSatrt, VacationDateEnd); cout << "\n";

}
