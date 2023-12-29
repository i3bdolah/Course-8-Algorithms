#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

int EnterInt(string msg) {
	int temp;
	cout << msg;
	cin >> temp;
	return temp;
}

string EnterString(string msg) {
	string temp;
	cout << msg;
	getline(cin, temp);

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

sDate ReadDate() {
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

sPeriod ReadPeriod() {
	sPeriod per;
	cout << "- Period Start\n\n";
	per.start = ReadDate();

	cout << "\n\n";

	cout << "- Period End\n\n";
	per.end = ReadDate();
	return per;
}

bool IsPeriodsOverlapped(sPeriod per1, sPeriod per2) {
	return !(IsDate1AfterDate2(per2.start, per1.end) || IsDate1BeforeDate2(per2.end, per1.start));
}

int PeriodLengthInDays(sPeriod per, bool IncludeEndDay = false) {
	return CalcDatesDifference(per.start, per.end, IncludeEndDay);
}

bool IsDateWithinPeriod(sDate date, sPeriod per) {
	return !(IsDate1BeforeDate2(date, per.start) || IsDate1AfterDate2(date, per.end));
}

int CountOverlapPeriods(sPeriod per1, sPeriod per2) {
	int OverlappedDays = 0;
	int per1Length = PeriodLengthInDays(per1);
	int per2Length = PeriodLengthInDays(per2);

	if (!IsPeriodsOverlapped) return 0; // Catch The 0 Case.

	if (per1Length < per2Length)
	{
		while (!IsDatesEquals(per1.start, per1.end))
		{
			if (IsDateWithinPeriod(per1.start, per2)) {
				OverlappedDays += 1;
			}
			per1.start = IncreaseDateByOneDay(per1.start);
		}
	}
	else
	{
		while (!IsDatesEquals(per2.start, per2.end))
		{
			if (IsDateWithinPeriod(per2.start, per1)) {
				OverlappedDays += 1;
			}
			per2.start = IncreaseDateByOneDay(per2.start);
		}
	}
	return OverlappedDays;
}

bool IsDateValid(sDate date) {
	return !((date.days < 1 || date.days > DaysInMonth(date.years, date.months)) || (date.months < 1 || date.months > 12) || (date.years < 1));
}

vector <string> splitToVector(string sentence, string seperator) {
	vector <string> wordsSeperated;
	int pos = 0;
	string strTemp;

	while ((pos = sentence.find(seperator)) != string::npos)
	{
		strTemp = sentence.substr(0, pos);
		if (strTemp != seperator)
		{
			wordsSeperated.push_back(strTemp.substr(0, (pos)));
		}

		sentence.erase(0, pos + seperator.length());
	}

	if (sentence != "" && sentence != seperator)
	{
		wordsSeperated.push_back(sentence);
	}

	return wordsSeperated;
}

sDate StringToDate(string date_str) {
	sDate date;
	vector <string> dateSeperated = splitToVector(date_str, "/");

	date.days = stoi(dateSeperated.at(0));
	date.months = stoi(dateSeperated.at(1));
	date.years = stoi(dateSeperated.at(2));

	return date;
}

string DateToString(sDate date) {
	return to_string(date.days) + "/" + to_string(date.months) + "/" + to_string(date.years);
}

enum FormatNumber
{
	D_M_Y_BS = 1,
	Y_M_D_BS = 2,
	M_D_Y_BS = 3,
	D_M_Y_H = 4,
	Y_M_D_H = 5,
	M_D_Y_H = 6,
	D_COL_M_COL_Y_COL = 7
};

// My Soltion
string FormatDate(sDate date, FormatNumber format) {
	string Day = to_string(date.days);
	string Month = to_string(date.months);
	string Year = to_string(date.years);

	switch (format)
	{
	case FormatNumber::D_M_Y_BS:
		return Day + "/" + Month + "/" + Year;
	case FormatNumber::Y_M_D_BS:
		return Year + "/" + Month + "/" + Day;
	case FormatNumber::M_D_Y_BS:
		return Month + "/" + Day + "/" + Year;
	case FormatNumber::D_M_Y_H:
		return Day + "-" + Month + "-" + Year;
	case FormatNumber::Y_M_D_H:
		return Year + "-" + Month + "-" + Day;
	case FormatNumber::M_D_Y_H:
		return Month + "-" + Day + "-" + Year;
	case FormatNumber::D_COL_M_COL_Y_COL:
		return "Day:" + Day + ", Month:" + Month + ", Year:" + Year;
	default:
		return Day + "/" + Month + "/" + Year;
	}
}

// Abu-Hadhoud Solution, The BEST

string toLowerCase(string str) {
	bool isFirstLetter = true;

	for (int i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}

string JoinVector(vector <string> vector, string seperator) {
	string wordsJoined;

	for (string& name : vector)
	{
		wordsJoined = wordsJoined + name + seperator;
	}

	return wordsJoined.substr(0, wordsJoined.length() - seperator.length());
}

string ReplaceWordInString(string StringToReplace, string RepalceTo, string FullString) {
	short pos = FullString.find(StringToReplace);

	while (pos != std::string::npos) {
		FullString = FullString.replace(pos, StringToReplace.length(), RepalceTo);         
		pos = FullString.find(StringToReplace);
	}
	return FullString;
}

string FormatDate(sDate date, string format = "dd/mm/yyyy") {
	string temp;

	temp = ReplaceWordInString("dd", to_string(date.days), format);
	temp = ReplaceWordInString("mm", to_string(date.months), temp);
	temp = ReplaceWordInString("yyyy", to_string(date.years), temp);

	return temp;
}


int main()
{
	string date_str = EnterString("Enter Date [DD/MM/YYYY]: ");

	sDate sDate = StringToDate(date_str);

	cout << "\n\n";
	//cout << FormatDate(sDate, FormatNumber::D_M_Y_BS) << endl;
	//cout << FormatDate(sDate, FormatNumber::Y_M_D_BS) << endl;
	//cout << FormatDate(sDate, FormatNumber::M_D_Y_BS) << endl;
	//cout << FormatDate(sDate, FormatNumber::D_M_Y_H) << endl;
	//cout << FormatDate(sDate, FormatNumber::Y_M_D_H) << endl;
	//cout << FormatDate(sDate, FormatNumber::M_D_Y_H) << endl;
	//cout << FormatDate(sDate, FormatNumber::D_COL_M_COL_Y_COL) << endl;

	cout << FormatDate(sDate, "yyyy-mm-dd") << endl;
	cout << FormatDate(sDate) << endl;

	cout << "\n\n";
}

