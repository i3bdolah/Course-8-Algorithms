#include <iostream>
#include <string>
#include <vector> 
#include <fstream> 
#include <iomanip>
using namespace std;

//const string ClientsFilePath = "C:\\Users\\Abdullah\\Desktop\\Clients-Table.txt";
//const string UsersFilePath = "C:\\Users\\Abdullah\\Desktop\\Users-Table.txt";

const string ClientsFilePath = "C:\\Users\\Abdullah\\source\\repos\\Course-8-Algorithms\\Clients-Table.txt";

enum QuickWithdrawOperations
{
	enOne = 20,
	enTwo = 50,
	enThree = 100,
	enFour = 200,
	enFive = 400,
	enSix = 600,
	enSeven = 800,
	enEight = 1000,
};

enum Operations
{
	enQuickWithdraw = 1,
	enNormalWithdraw = 2,
	enDeposit = 3,
	enCheckBalance = 4,
	enLogout = 5,
};


struct stClient
{
	string bank_acc;
	string pin_code;
	string name;
	string phone;
	double acc_balance = 0;
};

stClient CurrentClient; // Global Client

string EnterString(string msg) {
	string temp;
	cout << msg;
	getline(cin >> ws, temp);

	return temp;
}

void CheckCharInput(char& var, string msg) {
	cout << msg;
	cin >> var;
	cout << "\n";
	cin.ignore();
}

//** Draw Elements **//

void LineOfEquals() {
	cout << setw(50) << "==================================================" << endl;
}

void Headline(string headline) {
	LineOfEquals();
	cout << "\t\t" << headline << endl;
	LineOfEquals();
}

//** _____________ **//

// ** (Old) Helpers ** //

string ConvertStructureToLine(stClient client, string seperator = "#//#") {
	string tempRecord = "";

	tempRecord += client.bank_acc + seperator;
	tempRecord += client.pin_code + seperator;
	tempRecord += client.name + seperator;
	tempRecord += client.phone + seperator;
	tempRecord += to_string(client.acc_balance);

	return tempRecord;
}

void SaveDataToFile(string FilePath, string record) {
	fstream MyFile;
	MyFile.open(FilePath, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << record << endl;
		MyFile.close();
	}
	else
	{
		cout << "\nWe Couldn't open the File" << endl;
	}
}

string JoinVector(vector <string> vector, string seperator = "#//#") {
	string wordsJoined = "";

	for (string& name : vector)
	{
		wordsJoined = wordsJoined + name + seperator;
	}

	return wordsJoined.substr(0, wordsJoined.length() - seperator.length());
}

vector <string> splitToVector(string sentence, string seperator = "#//#") {
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

stClient ConvertLineToStructure(string line) {
	vector <string> splittedLine;
	stClient readyClient;
	splittedLine = splitToVector(line);

	readyClient.bank_acc = splittedLine[0];
	readyClient.pin_code = splittedLine[1];
	readyClient.name = splittedLine[2];
	readyClient.phone = splittedLine[3];
	readyClient.acc_balance = stod(splittedLine[4]);

	return readyClient;
}

vector <stClient> StructurizeLinesFromFile(string FilePath) {
	vector <stClient> vClients;
	fstream MyFile;

	MyFile.open(FilePath, ios::in);

	if (MyFile.is_open()) {
		string line;
		stClient client1;
		while (getline(MyFile, line))
		{
			client1 = ConvertLineToStructure(line);
			vClients.push_back(client1);
		}
		MyFile.close();
	}
	return vClients;
}

void SaveDataToFile(string FilePath, vector <stClient> UpdatedStructuresFromFile) {
	fstream MyFile;
	MyFile.open(FilePath, ios::out);

	if (MyFile.is_open()) {
		for (stClient& s : UpdatedStructuresFromFile)
		{
			MyFile << ConvertStructureToLine(s) << endl;
		}
		MyFile.close();
	}
	else
	{
		cout << "\nWe Couldn't open the File" << endl;
	}
}

int IsAccountNumberExist(vector <stClient> StructuresFromFile, string AccountNum) {
	for (int i = 0; i < StructuresFromFile.size(); i++) {
		if (StructuresFromFile[i].bank_acc == AccountNum)
		{
			return i;
		}
	}
	return -1;
}

// ** _____________ ** //
// ** (New) Helpers ** //

bool ValidateLogin(vector <stClient> StructuresFromFile, string AccountNumber, string PinCode) {
	for (stClient& C : StructuresFromFile)
	{
		if (C.bank_acc == AccountNumber && C.pin_code == PinCode)
		{
			CurrentClient = C;
			return true;
		}
	}
	return false;
}

void SyncCurrentUserChanges() {
	vector <stClient> AllClients = StructurizeLinesFromFile(ClientsFilePath);
	AllClients[IsAccountNumberExist(AllClients, CurrentClient.bank_acc)] = CurrentClient;
	SaveDataToFile(ClientsFilePath, AllClients);
}

// ** _____________ ** //

/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
void WithdrawLogic(int amount) {
	char IsSure;

	if (CurrentClient.acc_balance < amount)
	{
		cout << "\nYour Balance is Less than the Withdrawal Amount.\nTry Less Amount...\n\n" << endl;
		system("pause");
	}
	else
	{
		CheckCharInput(IsSure, "\n- Are You Sure [Y / N] : ");
		if (toupper(IsSure) == 'Y')
		{
			CurrentClient.acc_balance -= amount;
			SyncCurrentUserChanges();
			cout << "Withdraw Process Succeeded.\n\n" << endl;
			system("pause");
		}
	}
}

void QuickWithdrawDecisionsFlow(QuickWithdrawOperations enteredNum) {
	switch (enteredNum)
	{
	case 1:
		//system("cls"); // Clean Terminal
		WithdrawLogic(QuickWithdrawOperations::enOne);
		break;
	case 2:
		//system("cls"); // Clean Terminal
		WithdrawLogic(QuickWithdrawOperations::enTwo);
		break;
	case 3:
		//system("cls"); // Clean Terminal
		WithdrawLogic(QuickWithdrawOperations::enThree);
		break;
	case 4:
		//system("cls"); // Clean Terminal
		WithdrawLogic(QuickWithdrawOperations::enFour);
		break;
	case 5:
		//system("cls"); // Clean Terminal
		WithdrawLogic(QuickWithdrawOperations::enFive);
		break;
	case 6:
		//system("cls"); // Clean Terminal
		WithdrawLogic(QuickWithdrawOperations::enSix);
		break;
	case 7:
		//system("cls"); // Clean Terminal
		WithdrawLogic(QuickWithdrawOperations::enSeven);
		break;
	case 8:
		//system("cls"); // Clean Terminal
		WithdrawLogic(QuickWithdrawOperations::enEight);
		break;
	}
}

void QuickWithdraw() {
	int EnteredNum;
	do
	{
		system("cls");
		Headline("Quick Withdraw");
		cout << setw(10) << left << " " << "[1] " << QuickWithdrawOperations::enOne;
		cout << "\t" << "[2] " << QuickWithdrawOperations::enTwo << endl;
		cout << setw(10) << left << " " << "[3] " << QuickWithdrawOperations::enThree;
		cout << "\t" << "[4] " << QuickWithdrawOperations::enFour << endl;
		cout << setw(10) << left << " " << "[5] " << QuickWithdrawOperations::enFive;
		cout << "\t" << "[6] " << QuickWithdrawOperations::enSix << endl;
		cout << setw(10) << left << " " << "[7] " << QuickWithdrawOperations::enSeven;
		cout << "\t" << "[8] " << QuickWithdrawOperations::enEight << endl;
		cout << setw(10) << left << " " << "[9] Exit" << endl;
		LineOfEquals();
		cout << setw(20) << left << "Enter The Service Number : ";
		cin >> EnteredNum;
		cin.ignore();

		// Main Decisions FLow
		QuickWithdrawDecisionsFlow((QuickWithdrawOperations)EnteredNum);
	} while (EnteredNum != 9);
}


/////////////////////////////////////////////////////////////////
void CheckBalance() {
	cout << "\n";
	cout << "\t" << "Your Balance is: " << CurrentClient.acc_balance;
	cout << "\n";
	cout << "\n";
	system("pause");
}
/////////////////////////////////////////////////////////////////
void MainMenuOperations();


void Login() {
	bool IsClientExist;

	system("cls"); // Clean Terminal
	Headline("Login");
	string AccountNumber = EnterString("Enter The Account Number : ");
	string PinCode = EnterString("Enter The Pin Code : ");
	vector <stClient> StructuresFromFile = StructurizeLinesFromFile(ClientsFilePath);
	IsClientExist = ValidateLogin(StructuresFromFile, AccountNumber, PinCode);

	while (!IsClientExist) {
		system("cls"); // Clean Terminal
		Headline("Login");
		cout << "Wrong Credintials, Try Again...\n\n";
		AccountNumber = EnterString("Re-Enter The Account Number : ");
		PinCode = EnterString("Re-Enter The Pin Code : ");

		IsClientExist = ValidateLogin(StructuresFromFile, AccountNumber, PinCode);
	}
	// Then
	MainMenuOperations();
}

void MainDecisionsFlow(Operations EnteredNum) {
	switch (EnteredNum)
	{
	case Operations::enQuickWithdraw:
		system("cls"); // Clean Terminal
		Headline("Quick Withdraw");
		QuickWithdraw();
		break;
	case Operations::enNormalWithdraw:
		system("cls"); // Clean Terminal
		Headline("Normal Withdraw");
		break;
	case Operations::enDeposit:
		system("cls"); // Clean Terminal
		Headline("Deposit");
		break;
	case Operations::enCheckBalance:
		system("cls"); // Clean Terminal
		Headline("Check Balance");
		CheckBalance();
		break;
	case Operations::enLogout:
		Headline("Logout");
		Login();
		break;
	}
}

void MainMenuOperations() {
	int EnteredNum;
	do
	{
		system("cls");
		Headline("ATM - Main Menu");
		cout << "Good Morning, " << CurrentClient.name << " - " << CurrentClient.bank_acc << endl;
		cout << setw(10) << left << " " << "[1] Quick Withdraw" << endl;
		cout << setw(10) << left << " " << "[2] Normal Withdraw" << endl;
		cout << setw(10) << left << " " << "[3] Deposit" << endl;
		cout << setw(10) << left << " " << "[4] Check Balance" << endl;
		cout << setw(10) << left << " " << "[5] Logout" << endl;
		LineOfEquals();
		cout << setw(20) << left << "Enter The Service Number : ";
		cin >> EnteredNum;
		cin.ignore();

		// Main Decisions FLow
		MainDecisionsFlow((Operations)EnteredNum);
	} while (EnteredNum != Operations::enLogout);
}

int main()
{
	Login();
}