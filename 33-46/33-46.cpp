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

void DecreaseDateByOneDayVoid(sDate& sDate) {
	if (sDate.days == 1) {
		sDate.days = DaysInMonth(sDate.years, sDate.months);

		if (sDate.months == 1) {
			sDate.months = 12;
			sDate.years--;
		}
		else {
			sDate.months--;
		}
	}
	else
	{
		sDate.days--;
	}
}

// Questions Begins

void DecreaseDateByXDays(sDate& date, int num) {
	while (num != 0)
	{
		DecreaseDateByOneDayVoid(date);
		num--;
	}
}

void DecreaseDateByOneWeek(sDate& date) {
	DecreaseDateByXDays(date, 7);
}

void DecreaseDateByXWeeks(sDate& date, int num) {
	while (num != 0)
	{
		DecreaseDateByOneWeek(date);
		num--;
	}
}

void DecreaseDateByOneMonth(sDate& date) {
	DecreaseDateByXDays(date, DaysInMonth(date.years, date.months));
}

void DecreaseDateByXMonths(sDate& date, int num) {
	while (num != 0)
	{
		DecreaseDateByOneMonth(date);
		num--;
	}
}

void DecreaseDateByOneYear(sDate& date) {
	DecreaseDateByXMonths(date, 12);
}

void DecreaseDateByXYears(sDate& date, int num) {
	while (num != 0)
	{
		DecreaseDateByOneYear(date);
		num--;
	}
}

void DecreaseDateByXYearsFaster(sDate& date, int num) {
	date.years -= num;
}

void DecreaseDateByOneDecade(sDate& date) {
	DecreaseDateByXYears(date, 10);
}

void DecreaseDateByXDecades(sDate& date, int num) {
	while (num != 0)
	{
		DecreaseDateByOneDecade(date);
		num--;
	}
}

void DecreaseDateByXDecadesFaster(sDate& date, int num) {
	date.years -= (num * 10);
}

void DecreaseDateByOneCentury(sDate& date) {
	DecreaseDateByXDecades(date, 10);
}

void DecreaseDateByOneMillennium(sDate& date) {
	date.years -= 1000;
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

	DecreaseDateByOneDayVoid(date);
	cout << "01" << "-Substracting One Day: "; PrintDate(date);

	DecreaseDateByXDays(date, 10);
	cout << "02" << "-Substracting 10 Days: "; PrintDate(date);

	DecreaseDateByOneWeek(date);
	cout << "03" << "-Substracting One Week: "; PrintDate(date);

	DecreaseDateByXWeeks(date, 10);
	cout << "04" << "-Substracting 10 Weeks: "; PrintDate(date);

	DecreaseDateByOneMonth(date);
	cout << "05" << "-Substracting One Month: "; PrintDate(date);

	DecreaseDateByXMonths(date, 5);
	cout << "06" << "-Substracting 5 Months: "; PrintDate(date);

	DecreaseDateByOneYear(date);
	cout << "07" << "-Substracting One Year: "; PrintDate(date);

	DecreaseDateByXYears(date, 10);
	cout << "08" << "-Substracting 10 Years: "; PrintDate(date);

	DecreaseDateByXYearsFaster(date, 10);
	cout << "09" << "-Substracting 10 Years (Faster): "; PrintDate(date);

	DecreaseDateByOneDecade(date);
	cout << "10" << "-Substracting One Decade: "; PrintDate(date);

	DecreaseDateByXDecades(date, 10);
	cout << "11" << "-Substracting 10 Decades: "; PrintDate(date);

	DecreaseDateByXDecadesFaster(date, 10);
	cout << "12" << "-Substracting 10 Decades (Faster): "; PrintDate(date);

	DecreaseDateByOneCentury(date);
	cout << "13" << "-Substracting One Century: "; PrintDate(date);

	DecreaseDateByOneMillennium(date);
	cout << "14" << "-Substracting One Millennium: "; PrintDate(date);
}
