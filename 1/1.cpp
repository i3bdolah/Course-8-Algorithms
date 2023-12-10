#include <iostream>
using namespace std;

string PrintNumberTextName(int num) {
	if (num == 0)
	{
		return "";
	}
	if (num >= 1 && num <= 19)
	{
		string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven", "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen", "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
		return arr[num] + " ";
	}
	if (num >= 20 && num <= 99)
	{
		string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
		return arr[num] + " " + PrintNumberTextName(num % 10);
	}
	if (num >= 100 && num <= 199)
	{
		return "One Hundred " + PrintNumberTextName(num % 100);
	}
	if (num >= 200 && num <= 999)
	{
		return PrintNumberTextName(num / 100) + "Hundreds " + PrintNumberTextName(num % 100);
	}
	if (num >= 1000 && num <= 1999)
	{
		return "One Thousand " + PrintNumberTextName(num % 1000);
	}
	if (num >= 2000 && num <= 999999)
	{
		return PrintNumberTextName(num / 1000) + "Thousands " + PrintNumberTextName(num % 1000);
	}
	if (num >= 1000000 && num <= 1999999)
	{
		return "One Million " + PrintNumberTextName(num % 1000000);
	}
	if (num >= 2000000 && num <= 999999999)
	{
		return PrintNumberTextName(num / 1000000) + "Millions " + PrintNumberTextName(num % 1000000);
	}
	if (num >= 1000000000 && num <= 1999999999)
	{
		return "One Billion " + PrintNumberTextName(num % 1000000000);
	}
	else
	{
		return PrintNumberTextName(num / 1000000000) + "Billions " + PrintNumberTextName(num % 1000000000);

	}
}

int main()
{
	cout << PrintNumberTextName(10009) << endl;
}