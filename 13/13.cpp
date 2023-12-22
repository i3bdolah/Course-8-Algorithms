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

int main()
{
	sDate sDate1, sDate2;

	printf("\nKindly Enter Date #1 Information : -\n");
	sDate1 = FillDateInfo();
	printf("\nKindly Enter Date #2 Information : -\n");
	sDate2 = FillDateInfo();

	if (IsDate1LessDate2(sDate1, sDate2))
		cout << "\nYes, Is Less ";
	else
		cout << "\nNo, Is NOT Less ";

}
