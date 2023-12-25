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

void IncreaseDateByOneDayVoid(sDate& sDate) {
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
}

// Questions Begins

void IncreaseDateByXDays(sDate& date, int num) {
	while (num != 0)
	{
		IncreaseDateByOneDayVoid(date);
		num--;
	}
}

void IncreaseDateByOneWeek(sDate& date) {
	IncreaseDateByXDays(date, 7);
}

void IncreaseDateByXWeeks(sDate& date, int num) {
	while (num != 0)
	{
		IncreaseDateByOneWeek(date);
		num--;
	}
}

void IncreaseDateByOneMonth(sDate& date) {
	IncreaseDateByXDays(date, DaysInMonth(date.years, date.months));
}

void IncreaseDateByXMonths(sDate& date, int num) {
	while (num != 0)
	{
		IncreaseDateByOneMonth(date);
		num--;
	}
}

void IncreaseDateByOneYear(sDate& date) {
	IncreaseDateByXMonths(date, 12);
}

void IncreaseDateByXYears(sDate& date, int num) {
	while (num != 0)
	{
		IncreaseDateByOneYear(date);
		num--;
	}
}

void IncreaseDateByXYearsFaster(sDate& date, int num) {
	date.years += num;
}

void IncreaseDateByOneDecade(sDate& date) {
	IncreaseDateByXYears(date, 10);
}

void IncreaseDateByXDecades(sDate& date, int num) {
	while (num != 0)
	{
		IncreaseDateByOneDecade(date);
		num--;
	}
}

void IncreaseDateByXDecadesFaster(sDate& date, int num) {
	date.years += (num * 10);
}

void IncreaseDateByOneCentury(sDate& date) {
	IncreaseDateByXDecades(date, 10);
}

void IncreaseDateByOneMillennium(sDate& date) {
	date.years += 1000;
}

void PrintDate(sDate date) {
	cout << date.days << "/" << date.months << "/" << date.years << endl;
}

int main()
{
	sDate date;

	printf("\n");
	date = FillDateInfo();

	printf("\n\nDate After:\n\n");

	IncreaseDateByOneDayVoid(date);
	cout << "01" << "-Adding One Day: "; PrintDate(date);

	IncreaseDateByXDays(date, 10);
	cout << "02" << "-Adding 10 Days: "; PrintDate(date);

	IncreaseDateByOneWeek(date);
	cout << "03" << "-Adding One Week: "; PrintDate(date);

	IncreaseDateByXWeeks(date, 10);
	cout << "04" << "-Adding 10 Weeks: "; PrintDate(date);

	IncreaseDateByOneMonth(date);
	cout << "05" << "-Adding One Month: "; PrintDate(date);

	IncreaseDateByXMonths(date, 5);
	cout << "06" << "-Adding 5 Months: "; PrintDate(date);

	IncreaseDateByOneYear(date);
	cout << "07" << "-Adding One Year: "; PrintDate(date);

	IncreaseDateByXYears(date, 10);
	cout << "08" << "-Adding 10 Years: "; PrintDate(date);

	IncreaseDateByXYearsFaster(date, 10);
	cout << "09" << "-Adding 10 Years (Faster): "; PrintDate(date);

	IncreaseDateByOneDecade(date);
	cout << "10" << "-Adding One Decade: "; PrintDate(date);

	IncreaseDateByXDecades(date, 10);
	cout << "11" << "-Adding 10 Decades: "; PrintDate(date);

	IncreaseDateByXDecadesFaster(date, 10);
	cout << "12" << "-Adding 10 Decades (Faster): "; PrintDate(date);

	IncreaseDateByOneCentury(date);
	cout << "13" << "-Adding One Century: "; PrintDate(date);

	IncreaseDateByOneMillennium(date);
	cout << "14" << "-Adding One Millennium: "; PrintDate(date);
}
