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

string GetFullDate(int year, int month, int day) {
	return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}

int GetDayOrder(int year, int month, int day) {
	int a = (14 - month) / 12;
	int y = year - a;
	int m = month + (12 * a) - 2;

	int d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	return d;
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

void PrintDateDetails(int year, int month, int day) {
	cout << setw(15) << right << "Date : ";
	cout << GetFullDate(year, month, day) << endl;

	cout << setw(15) << right << "Day Order : ";
	cout << GetDayOrder(year, month, day) << endl;

	cout << setw(15) << right << "Day Name : ";
	cout << GetDayNameByOrder(GetDayOrder(year, month, day)) << endl;
}

int main()
{
	int year = EnterInt("Enter The Year : ");
	int month = EnterInt("Enter The Month [1-12] : ");
	int day = EnterInt("Enter The Day [1-30] : ");

	PrintDateDetails(year, month, day);
}