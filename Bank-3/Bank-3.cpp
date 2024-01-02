#include <iostream>
#include <string>
#include <vector> 
#include <fstream> 
#include <iomanip>
using namespace std;

//const string ClientsFilePath = "C:\\Users\\Abdullah\\Desktop\\Clients-Table.txt";
//const string UsersFilePath = "C:\\Users\\Abdullah\\Desktop\\Users-Table.txt";

const string ClientsFilePath = "Clients-Table.txt";
const string UsersFilePath = "Users-Table.txt";

enum Operations
{
	//None = 0,
	ShowAll = 1,
	Add = 2,
	Delete = 3,
	Update = 4,
	Find = 5,
	Transactions = 6,
	ManageUsers = 7,
	Logout = 8,
};

enum TransactionsOperation
{
	Deposit = 1,
	Withdrawal = 2,
	ShowAllBalance = 3,
	MainMenu = 4,
};

enum enManageUsersOperation
{
	ListUsers = 1,
	AddUsers = 2,
	DeleteUsers = 3,
	UpdateUsers = 4,
	FindUsers = 5,
	//MainMenu = 6,
};

struct stClient
{
	string bank_acc;
	string pin_code;
	string name;
	string phone;
	double acc_balance = 0;

	stClient() = default;
};

struct stUserPermissions {
	//short IsShowAll = 0;
	//short IsAdd = 0;
	//short IsDelete = 0;
	//short IsUpdate = 0;
	//short IsFind = 0;
	//short IsTransaction = 0;
	//short IsManageUsers = 0;
	int PermissionID = 0;
};

struct stUser
{
	string Username;
	string Password;
	stUserPermissions Permissions;
};

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

int isAccountExist(vector <stClient> StructuresFromFile, string AccountNum);
vector <stClient> LoadAndStructurizeDataFromFile(string FilePath);

// Adding Client
stClient ReadNewClient() {
	stClient client;
	vector <stClient> AllClients = LoadAndStructurizeDataFromFile(ClientsFilePath);

	cout << "Enter your bank account : ";
	getline(cin, client.bank_acc);

	if (isAccountExist(AllClients, client.bank_acc) >= 0)
	{
		do
		{
			cout << "\nThe Entered Bank Acc. Already Exist!";
			cout << "\nRe-Enter your bank account : ";
			getline(cin, client.bank_acc);
		} while (isAccountExist(AllClients, client.bank_acc) >= 0);
	}

	cout << "Enter your pin code : ";
	getline(cin, client.pin_code);

	cout << "Enter your full name : ";
	getline(cin, client.name);

	cout << "Enter your phone number : ";
	getline(cin, client.phone);

	cout << "Enter Your Account Balance : ";
	cin >> client.acc_balance;

	return client;
}

string ConvertRecordToLine(stClient client, string seperator = "#//#") {

	string tempRecord = "";

	tempRecord += client.bank_acc + seperator;
	tempRecord += client.pin_code + seperator;
	tempRecord += client.name + seperator;
	tempRecord += client.phone + seperator;
	tempRecord += to_string(client.acc_balance);

	return tempRecord;
}

string ConvertRecordToLine(stUser user, string seperator = "#//#") {

	string tempRecord = "";

	tempRecord += user.Username + seperator;
	tempRecord += user.Password + seperator;
	tempRecord += to_string(user.Permissions.PermissionID);

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

void AddNewClient() {
	stClient client = ReadNewClient();
	SaveDataToFile(ClientsFilePath, ConvertRecordToLine(client));
}

void AddClients() {
	char addMore = 'Y';

	while (toupper(addMore) == 'Y')
	{
		AddNewClient();


		cout << "\nClient Saved Successfully, Add more ? [Y / N] : ";
		cin >> addMore;
		cin.ignore();
	};
}

void LineOfEquals() {
	cout << setw(50) << "==================================================" << endl;
}

void Headline(string headline) {
	LineOfEquals();
	cout << "\t\t" << headline << endl;
	LineOfEquals();
}

// Read Client
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

stClient LineToClientStructure(string line) {
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

vector <stClient> LoadAndStructurizeDataFromFile(string FilePath) {
	vector <stClient> vClients;
	fstream MyFile;

	MyFile.open(FilePath, ios::in);

	if (MyFile.is_open()) {
		string line;
		stClient client1;
		while (getline(MyFile, line))
		{
			client1 = LineToClientStructure(line);
			vClients.push_back(client1);
		}
		MyFile.close();
	}
	return vClients;
}

void HugeLine() {
	cout << "____________________________________________________________________________________________________" << endl;
}

void PrintHeaders(int vectorSize, bool IsUser = false) {
	if (IsUser)
	{
		cout << "\n\t\t\t\tUsers List (" << vectorSize << ") User(s)." << endl;
		HugeLine();
		cout << "\n| " << left << setw(20) << "Username";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(20) << "Permissions" << endl;
		HugeLine();
	}
	else
	{
		cout << "\n\t\t\t\tClient List (" << vectorSize << ") Client(s)." << endl;
		HugeLine();
		cout << "\n| " << left << setw(20) << "Account Number";
		cout << "| " << left << setw(20) << "Pin Code";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(20) << "Phone";
		cout << "| " << left << setw(20) << "Balance" << endl;
		HugeLine();
	}
}

void PrintRows(stClient client) {
	cout << "| " << left << setw(20) << client.bank_acc;
	cout << "| " << left << setw(20) << client.pin_code;
	cout << "| " << left << setw(20) << client.name;
	cout << "| " << left << setw(20) << client.phone;
	cout << "| " << left << setw(20) << client.acc_balance << endl;
}

void PrintRows(stUser user) {
	cout << "| " << left << setw(20) << user.Username;
	cout << "| " << left << setw(20) << user.Password;
	cout << "| " << left << setw(20) << user.Permissions.PermissionID << endl;
}

void PrintImportedLines(vector <stClient> StructuresFromFile) {
	HugeLine();
	PrintHeaders(StructuresFromFile.size(), false);
	for (stClient& structure : StructuresFromFile)
	{
		PrintRows(structure);
	}
	HugeLine();
}

void PrintImportedLines(vector <stUser> StructuresFromFile) {
	HugeLine();
	PrintHeaders(StructuresFromFile.size(), true);
	for (stUser& structure : StructuresFromFile)
	{
		PrintRows(structure);
	}
	HugeLine();
}


void ReadClients() {
	vector <stClient> StructuresFromFile = LoadAndStructurizeDataFromFile(ClientsFilePath);
	PrintImportedLines(StructuresFromFile);
}

// Find Client

stClient NotFoundClient() {
	stClient temp;

	temp.bank_acc = "NOT FOUND";
	temp.pin_code = "NOT FOUND";
	temp.name = "NOT FOUND";
	temp.phone = "NOT FOUND";
	temp.acc_balance = 0;

	return temp;
}

stUser NotFoundUser() {
	stUser temp;

	temp.Username = "NOT FOUND";
	temp.Password = "NOT FOUND";
	temp.Permissions.PermissionID = 0;

	return temp;
}

void PrintHeaders(bool isUser = false) {
	if (!isUser) {
		HugeLine();
		cout << "\n| " << left << setw(20) << "Account Number";
		cout << "| " << left << setw(20) << "Pin Code";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(20) << "Phone";
		cout << "| " << left << setw(20) << "Balance" << endl;
		HugeLine();
	}
	else
	{
		HugeLine();
		cout << "\n| " << left << setw(20) << "Username";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(20) << "Permissions" << endl;
		HugeLine();
	}
}

void PrintImportedLines(stClient StructuresFromFile) {
	PrintHeaders();
	PrintRows(StructuresFromFile);
}

void PrintImportedLines(stUser StructuresFromFile) {
	PrintHeaders(true);
	PrintRows(StructuresFromFile);
}

stClient SearchInClients(vector <stClient> StructuresFromFile, string AccountNum) {
	for (stClient& structure : StructuresFromFile)
	{
		if (structure.bank_acc == AccountNum)
		{
			return structure;
		}
	}
	return NotFoundClient();
}

void FindClient() {
	string AccountNum = EnterString("Enter The Account Number : ");
	vector <stClient> StructuresFromFile = LoadAndStructurizeDataFromFile(ClientsFilePath);
	stClient TheClient = SearchInClients(StructuresFromFile, AccountNum);
	PrintImportedLines(TheClient);
}

// Delete Client

string JoinClientDataToLine(stClient stClient, string seperator = "#//#") {
	string wordsJoined = "";

	wordsJoined += stClient.bank_acc + seperator;
	wordsJoined += stClient.pin_code + seperator;
	wordsJoined += stClient.name + seperator;
	wordsJoined += stClient.phone + seperator;
	wordsJoined += to_string(stClient.acc_balance);

	return wordsJoined;
}

void SaveDataToFile(string FilePath, vector <stClient> UpdatedStructuresFromFile) {
	fstream MyFile;
	MyFile.open(FilePath, ios::out);

	if (MyFile.is_open()) {
		for (stClient& s : UpdatedStructuresFromFile)
		{
			MyFile << JoinClientDataToLine(s) << endl;
		}
		MyFile.close();
	}
	else
	{
		cout << "\nWe Couldn't open the File" << endl;
	}
}

int isAccountExist(vector <stClient> StructuresFromFile, string AccountNum) {
	for (int i = 0; i < StructuresFromFile.size(); i++) {
		if (StructuresFromFile[i].bank_acc == AccountNum)
		{
			return i;
		}
	}
	return -1;
}

int isAccountExist(vector <stUser> StructuresFromFile, string Username) {
	for (int i = 0; i < StructuresFromFile.size(); i++) {
		if (StructuresFromFile[i].Username == Username)
		{
			return i;
		}
	}
	return -1;
}

void DeleteFromVectorByIndex(vector <stClient>& StructuresFromFile, string AccountNum) {
	StructuresFromFile.erase(StructuresFromFile.begin() + isAccountExist(StructuresFromFile, AccountNum));
}

void DeleteFromVectorByIndex(vector <stUser>& StructuresFromFile, string Username) {
	StructuresFromFile.erase(StructuresFromFile.begin() + isAccountExist(StructuresFromFile, Username));
}

void DeleteAndPrintTheCLient(vector <stClient>& StructuresFromFile, string AccountNum) {
	char Sure;
	int TargetVectorIndex = isAccountExist(StructuresFromFile, AccountNum);

	if (isAccountExist(StructuresFromFile, AccountNum) != -1)
	{
		PrintImportedLines(StructuresFromFile[TargetVectorIndex]);

		CheckCharInput(Sure, "\n- Are You Sure [Y / N] : ");
		if (toupper(Sure) == 'Y')
		{
			DeleteFromVectorByIndex(StructuresFromFile, AccountNum);
			cout << "\nCLient Data Deleted Successfully.\n";

		}
	}
	else
	{
		PrintImportedLines(NotFoundClient());
	}
}

void DeleteClient() {
	char isContinued;
	vector <stClient> StructuresFromFile = LoadAndStructurizeDataFromFile(ClientsFilePath);
	do
	{
		system("cls"); // Clean Terminal

		string AccountNum = EnterString("Enter The Account Number : ");

		DeleteAndPrintTheCLient(StructuresFromFile, AccountNum); // Deletion Process
		SaveDataToFile(ClientsFilePath, StructuresFromFile); // Sync Changes

		CheckCharInput(isContinued, "\n- Do you want to continue [Y / N] : ");
	} while (toupper(isContinued) == 'Y');

	cout << "\nThank you, See you soon!\n\n";
}

// Update Client

stClient UpdateFromVectorByIndex(stClient TheClient) {
	TheClient.pin_code = EnterString("Enter Pin Code : ");
	TheClient.name = EnterString("Enter Name : ");
	TheClient.phone = EnterString("Enter Phone Number : ");
	TheClient.acc_balance = stod(EnterString("Enter Balance : "));

	return TheClient;
}

void UpdateAndPrintTheClient(vector <stClient>& StructuresFromFile, string AccountNum) {
	char Sure;
	int TargetVectorIndex = isAccountExist(StructuresFromFile, AccountNum);

	if (isAccountExist(StructuresFromFile, AccountNum) != -1)
	{
		PrintImportedLines(StructuresFromFile[TargetVectorIndex]);

		CheckCharInput(Sure, "\n- Proceed with this client [Y / N] : ");
		if (toupper(Sure) == 'Y')
		{
			StructuresFromFile[TargetVectorIndex] = UpdateFromVectorByIndex(StructuresFromFile[TargetVectorIndex]);
			cout << "\nClient Data Updated Successfully.\n";
		}
	}
	else
	{
		PrintImportedLines(NotFoundClient());
	}
}

void UpdateClient() {
	char isContinued;
	do
	{
		system("cls"); // Clear Terminal
		Headline("Update Client");
		string AccountNum = EnterString("Enter The Account Number : ");
		vector <stClient> StructuresFromFile = LoadAndStructurizeDataFromFile(ClientsFilePath);

		UpdateAndPrintTheClient(StructuresFromFile, AccountNum);
		SaveDataToFile(ClientsFilePath, StructuresFromFile); // Sync Changes

		CheckCharInput(isContinued, "\n- Continue Updating [Y / N] : ");
	} while (toupper(isContinued) == 'Y');

	cout << "\nThank you, See you soon!\n\n";
}

// Transactions

void QuickClinetPrint(stClient client) {
	cout << "Account Number = " << client.bank_acc << endl;
	cout << "Pin Code = " << client.pin_code << endl;
	cout << "Name = " << client.name << endl;
	cout << "Phone = " << client.phone << endl;
	cout << "Balance = " << client.acc_balance << endl;
}

void DepositOperation() {
	double depositValue;
	vector <stClient> StructuresFromFile = LoadAndStructurizeDataFromFile(ClientsFilePath);
	int Index = isAccountExist(StructuresFromFile, EnterString("Enter The Account Number : "));

	if (Index >= 0)
	{
		// Printing Quick Info
		HugeLine();
		QuickClinetPrint(StructuresFromFile[Index]);
		HugeLine();

		cout << "Deposit Value : ";
		cin >> depositValue;

		StructuresFromFile[Index].acc_balance += depositValue;
		SaveDataToFile(ClientsFilePath, StructuresFromFile);
		cout << "Data Saved Successfully." << endl;
	}
	else
	{
		cout << "Account Number Not Exist!" << endl;
	}
}

void WithdrawalOperation() {
	double withdrawalValue;
	vector <stClient> StructuresFromFile = LoadAndStructurizeDataFromFile(ClientsFilePath);
	int Index = isAccountExist(StructuresFromFile, EnterString("Enter The Account Number : "));

	if (Index >= 0)
	{
		// Printing Quick Info
		HugeLine();
		QuickClinetPrint(StructuresFromFile[Index]);
		HugeLine();

		cout << "Withdrawal Value : ";
		cin >> withdrawalValue;

		if (withdrawalValue <= StructuresFromFile[Index].acc_balance)
		{

			StructuresFromFile[Index].acc_balance -= withdrawalValue;
			SaveDataToFile(ClientsFilePath, StructuresFromFile);
			cout << "Data Saved Successfully." << endl;
		}
		else {
			cout << "More than current balance!" << endl;
		}
	}
	else
	{
		cout << "Account Number Not Exist!" << endl;
	}
	system("pause");
}

void ShowAllBalanceOperation() {
	vector <stClient> StructuresFromFile = LoadAndStructurizeDataFromFile(ClientsFilePath);

	HugeLine();
	cout << "\n| " << left << setw(20) << "Account Number";
	cout << "| " << left << setw(20) << "Client Name";
	cout << "| " << left << setw(20) << "Balance" << endl;
	HugeLine();
	for (stClient& C : StructuresFromFile) {
		cout << "| " << left << setw(20) << C.bank_acc;
		cout << "| " << left << setw(20) << C.name;
		cout << "| " << left << setw(20) << C.acc_balance << endl;
	}
	HugeLine();

	system("pause");
}

void TransactionsDecisionsFlow(TransactionsOperation EnteredNum) {
	switch (EnteredNum)
	{
	case TransactionsOperation::Deposit:
		system("cls"); // Clean Terminal
		Headline("Deposit");
		DepositOperation();
		system("pause");
		break;
	case TransactionsOperation::Withdrawal:
		system("cls"); // Clean Terminal
		Headline("Withdrawal");
		WithdrawalOperation();
		break;
	case TransactionsOperation::ShowAllBalance:
		system("cls"); // Clean Terminal
		Headline("Show Clients Balance");
		ShowAllBalanceOperation();
		break;
	}

}

void ClientTransactions() {
	int EnteredNum;
	do
	{
		system("cls");
		Headline("Transactions");
		cout << setw(50) << left << "[1] Deposit" << endl;
		cout << setw(50) << left << "[2] Withdrawal" << endl;
		cout << setw(50) << left << "[3] Show Clients Balance" << endl;
		cout << setw(50) << left << "[4] Main Menu" << endl;
		LineOfEquals();
		cout << setw(20) << left << "Enter The Service Number : ";
		cin >> EnteredNum;
		cin.ignore();

		// Decisions
		TransactionsDecisionsFlow((TransactionsOperation)EnteredNum);
	} while (EnteredNum != 4);
}
/////////////////////////////////////////////////////////////////
// Read User

bool ValidateLogin(vector <stUser> StructuresFromFile, string Username, string Password) {
	for (stUser& user : StructuresFromFile)
	{
		if (user.Username == Username && user.Password == Password)
		{
			return true;
		}
	}
	return false;
}

stUser LineToUserStructure(string line) {
	vector <string> splittedLine;
	stUser readyClient;
	splittedLine = splitToVector(line);

	readyClient.Username = splittedLine[0];
	readyClient.Password = splittedLine[1];
	readyClient.Permissions.PermissionID = stoi(splittedLine[2]);

	return readyClient;
}

vector <stUser> LoadAndStructurizeDataFromUsersFile(string FilePath) {
	vector <stUser> vUsers;
	fstream MyFile;

	MyFile.open(FilePath, ios::in);

	if (MyFile.is_open()) {
		string line;
		stUser user1;
		while (getline(MyFile, line))
		{
			user1 = LineToUserStructure(line);
			vUsers.push_back(user1);
		}
		MyFile.close();
	}
	return vUsers;
}

// Reading Permissions

stUserPermissions ReadUserPermissions() {
	stUserPermissions per;
	char Letter;

	cout << "\nDo you want to give Full Access [Y/N] : ";
	cin >> Letter;
	cin.ignore();


	if (toupper(Letter) == 'Y') {
		per.PermissionID = -1;
		return per;
	}
	else
	{
		cout << "\n\n- Show Client List [Y/N] : ";
		cin >> Letter;
		cin.ignore();
		if (Letter == 'Y' || Letter == 'y') {
			per.PermissionID += 1;
		}

		cout << "\n\n- Add Client[Y/N] : ";
		cin >> Letter;
		cin.ignore();

		if (Letter == 'Y' || Letter == 'y') {
			per.PermissionID += 2;
		}

		cout << "\n\n- Delete Client[Y/N] : ";
		cin >> Letter;
		cin.ignore();
		if (Letter == 'Y' || Letter == 'y') {
			per.PermissionID += 4;
		}

		cout << "\n\n- Update Client[Y/N] : ";
		cin >> Letter;
		cin.ignore();
		if (Letter == 'Y' || Letter == 'y') {
			per.PermissionID += 8;
		}

		cout << "\n\n- Find Client[Y/N] : ";
		cin >> Letter;
		cin.ignore();
		if (Letter == 'Y' || Letter == 'y') {
			per.PermissionID += 16;
		}

		cout << "\n\n- Transaction [Y/N] : ";
		cin >> Letter;
		cin.ignore();
		if (Letter == 'Y' || Letter == 'y') {
			per.PermissionID += 32;
		}

		cout << "\n\n- Manage Users [Y/N] : ";
		cin >> Letter;
		cin.ignore();
		if (Letter == 'Y' || Letter == 'y') {
			per.PermissionID += 64;
		}

	}

	if (per.PermissionID == 127)
	{
		per.PermissionID = -1;
	}

	return per;
}

//  List Users

void ListUsersFunc() {
	vector <stUser> StructuresFromFile = LoadAndStructurizeDataFromUsersFile(UsersFilePath);
	PrintImportedLines(StructuresFromFile);
}

// Add Users

stUser ReadNewUser() {
	stUser user;
	vector <stUser> AllUsers = LoadAndStructurizeDataFromUsersFile(UsersFilePath);

	cout << "Enter Username : ";
	getline(cin, user.Username);

	if (isAccountExist(AllUsers, user.Username) >= 0)
	{
		do
		{
			cout << "\nThe Entered Username. Already Exist!";
			cout << "\nRe-Enter your Username : ";
			getline(cin, user.Username);
		} while (isAccountExist(AllUsers, user.Username) >= 0);
	}

	cout << "Enter your Password : ";
	getline(cin, user.Password);

	user.Permissions = ReadUserPermissions();

	return user;
}

void AddNewUserFunc() {
	stUser user = ReadNewUser();
	SaveDataToFile(UsersFilePath, ConvertRecordToLine(user));
}

// Delete Users

void SaveDataToFile(string FilePath, vector <stUser> UpdatedStructuresFromFile) {
	fstream MyFile;
	MyFile.open(FilePath, ios::out);

	if (MyFile.is_open()) {
		for (stUser& s : UpdatedStructuresFromFile)
		{
			MyFile << ConvertRecordToLine(s) << endl;
		}
		MyFile.close();
	}
	else
	{
		cout << "\nWe Couldn't open the File" << endl;
	}
}

void DeleteAndPrintTheUser(vector <stUser>& StructuresFromFile, string Username) {
	char Sure;
	int TargetVectorIndex = isAccountExist(StructuresFromFile, Username);

	if (isAccountExist(StructuresFromFile, Username) != -1)
	{
		PrintImportedLines(StructuresFromFile[TargetVectorIndex]);

		CheckCharInput(Sure, "\n- Are You Sure [Y / N] : ");
		if (toupper(Sure) == 'Y')
		{
			DeleteFromVectorByIndex(StructuresFromFile, Username);
			cout << "\nUser Data Deleted Successfully.\n";

		}
	}
	else
	{
		PrintImportedLines(NotFoundUser());
	}
}

void DeleteUserFunc() {
	char isContinued;
	vector <stUser> StructuresFromFile = LoadAndStructurizeDataFromUsersFile(UsersFilePath);
	do
	{
		system("cls"); // Clean Terminal
		Headline("Delete Client");

		string Username = EnterString("Enter The Username : ");

		if (Username == "Admin")
		{
			cout << "\n\n" << "You Cannot Delete The (Admin)." << "\n\n";
		}
		else
		{
			DeleteAndPrintTheUser(StructuresFromFile, Username); // Deletion Process
			SaveDataToFile(UsersFilePath, StructuresFromFile); // Sync Changes
		}

		CheckCharInput(isContinued, "\n- Do you want to continue [Y / N] : ");
	} while (toupper(isContinued) == 'Y');

	cout << "\nThank you, See you soon!\n\n";
}

// Update Users

stUser UpdateFromVectorByIndex(stUser TheUser) {
	/*TheUser.Username = EnterString("Enter Username : ");
	TheUser.Password = EnterString("Enter Password : ");*/

	TheUser = ReadNewUser();

	return TheUser;
}

void UpdateAndPrintTheUser(vector <stUser>& StructuresFromFile, string Username) {
	char Sure;
	int TargetVectorIndex = isAccountExist(StructuresFromFile, Username);

	if (isAccountExist(StructuresFromFile, Username) != -1)
	{
		PrintImportedLines(StructuresFromFile[TargetVectorIndex]);

		CheckCharInput(Sure, "\n- Proceed with this User [Y / N] : ");
		if (toupper(Sure) == 'Y')
		{
			StructuresFromFile[TargetVectorIndex] = UpdateFromVectorByIndex(StructuresFromFile[TargetVectorIndex]);
			cout << "\nUser Data Updated Successfully.\n";
		}
	}
	else
	{
		PrintImportedLines(NotFoundUser());
	}
}

void UpdateUserFunc() {
	char isContinued;
	do
	{
		system("cls"); // Clear Terminal
		Headline("Update Client");
		string Username = EnterString("Enter The Username : ");
		vector <stUser> StructuresFromFile = LoadAndStructurizeDataFromUsersFile(UsersFilePath);

		UpdateAndPrintTheUser(StructuresFromFile, Username);
		SaveDataToFile(UsersFilePath, StructuresFromFile); // Sync Changes

		CheckCharInput(isContinued, "\n- Continue Updating [Y / N] : ");
	} while (toupper(isContinued) == 'Y');

	cout << "\nThank you, See you soon!\n\n";
}

// Find Users

stUser SearchInUsers(vector <stUser> StructuresFromFile, string Username) {
	for (stUser& structure : StructuresFromFile)
	{
		if (structure.Username == Username)
		{
			return structure;
		}
	}
	return NotFoundUser();
}

void FindUserFunc() {
	string Username = EnterString("Enter The Username : ");
	vector <stUser> StructuresFromFile = LoadAndStructurizeDataFromUsersFile(UsersFilePath);
	stUser TheUser = SearchInUsers(StructuresFromFile, Username);
	PrintImportedLines(TheUser);
}

/////////////////////////////////////////////////////////////////

// Manage Users

void ManageUsersDecisionsFlow(enManageUsersOperation EnteredNum) {
	switch (EnteredNum)
	{
	case enManageUsersOperation::ListUsers:
		system("cls"); // Clean Terminal
		Headline("List Users");
		ListUsersFunc();
		system("pause");
		break;
	case enManageUsersOperation::AddUsers:
		system("cls"); // Clean Terminal
		Headline("Add Users");
		AddNewUserFunc();
		system("pause");
		break;
	case enManageUsersOperation::DeleteUsers:
		system("cls"); // Clean Terminal
		Headline("Delete Users");
		DeleteUserFunc();
		system("pause");
		break;
	case enManageUsersOperation::UpdateUsers:
		system("cls"); // Clean Terminal
		Headline("Update Users");
		UpdateUserFunc();
		system("pause");
		break;
	case enManageUsersOperation::FindUsers:
		system("cls"); // Clean Terminal
		Headline("Find Users");
		FindUserFunc();
		system("pause");
		break;
	}
}

void ManageUsersOperation() {
	int EnteredNum;
	do
	{
		system("cls");
		Headline("Manage Users");
		cout << setw(50) << left << "[1] List Users" << endl;
		cout << setw(50) << left << "[2] Add New User" << endl;
		cout << setw(50) << left << "[3] Delete User" << endl;
		cout << setw(50) << left << "[4] Update User" << endl;
		cout << setw(50) << left << "[5] Find User" << endl;
		cout << setw(50) << left << "[6] Main Menu" << endl;
		LineOfEquals();
		cout << setw(20) << left << "Enter The Service Number : ";
		cin >> EnteredNum;
		cin.ignore();

		// Decisions
		ManageUsersDecisionsFlow((enManageUsersOperation)EnteredNum);
	} while (EnteredNum != 6);
}

/////////////////////////////////////////////////////////////////
void ClientOperations(stUser user);


void Login() {
	bool IsUserExist;

	system("cls"); // Clean Terminal
	Headline("Login");
	string Username = EnterString("Enter The Username : ");
	string Password = EnterString("Enter The Password : ");
	vector <stUser> StructuresFromFile = LoadAndStructurizeDataFromUsersFile(UsersFilePath);
	IsUserExist = ValidateLogin(StructuresFromFile, Username, Password);

	while (!IsUserExist) {
		system("cls"); // Clean Terminal
		Headline("Login");
		cout << "Wrong Credintials, Try Again...\n\n";
		Username = EnterString("Re-Enter The Username : ");
		Password = EnterString("Re-Enter The Password : ");
		//vector <stUser> StructuresFromFile = LoadAndStructurizeDataFromUsersFile(UsersFilePath);
		IsUserExist = ValidateLogin(StructuresFromFile, Username, Password);
	}
	// Then
	ClientOperations(StructuresFromFile[isAccountExist(StructuresFromFile, Username)]);
}

void AcceessDeniedMessage() {
	system("cls"); // Clean Terminal
	Headline("Access Denied!!!");
	Headline("Access Denied!!!");
	Headline("Access Denied!!!");
	system("pause");
}

void DecisionsFlow(Operations EnteredNum, stUserPermissions userPer) {
	switch (EnteredNum)
	{
	case Operations::ShowAll:
		if ((userPer.PermissionID & 1) == 0)
		{
			AcceessDeniedMessage();
		}
		else
		{
			system("cls"); // Clean Terminal
			Headline("Show Client List");
			ReadClients();
			system("pause");
		}
		break;
	case Operations::Add:
		if ((userPer.PermissionID & 2) == 0)
		{
			AcceessDeniedMessage();
		}
		else
		{
			system("cls"); // Clean Terminal
			Headline("Add Client");
			AddClients();
		}
		break;
	case Operations::Delete:
		if ((userPer.PermissionID & 4) == 0)
		{
			AcceessDeniedMessage();
		}
		else
		{
			system("cls"); // Clean Terminal
			Headline("Delete Client");
			DeleteClient();
		}
		break;
	case Operations::Update:
		if ((userPer.PermissionID & 8) == 0) {
			AcceessDeniedMessage();
		}
		else
		{
			system("cls"); // Clean Terminal
			Headline("Update Client");
			UpdateClient();
		}
		break;
	case Operations::Find:
		if ((userPer.PermissionID & 16) == 0)
		{
			AcceessDeniedMessage();
		}
		else
		{
			system("cls"); // Clean Terminal
			Headline("Find Client");
			FindClient();
			system("pause");
		}
		break;
	case Operations::Transactions:
		if ((userPer.PermissionID & 32) == 0)
		{
			AcceessDeniedMessage();
		}
		else
		{
			system("cls"); // Clean Terminal
			Headline("Transactions");
			ClientTransactions();
		}
		break;
	case Operations::ManageUsers:
		if ((userPer.PermissionID & 64) == 0)
		{
			AcceessDeniedMessage();
		}
		else
		{
			system("cls"); // Clean Terminal
			Headline("Manage Users");
			ManageUsersOperation();
		}
		break;
	case Operations::Logout:
		system("cls"); // Clean Terminal
		Headline("Login");
		Login();
		break;
	}

}

void ClientOperations(stUser user) {
	int EnteredNum;
	do
	{
		system("cls");
		Headline("Main Menu");
		cout << setw(50) << left << "[1] Show Client List" << endl;
		cout << setw(50) << left << "[2] Add Client" << endl;
		cout << setw(50) << left << "[3] Delete Client" << endl;
		cout << setw(50) << left << "[4] Update Client" << endl;
		cout << setw(50) << left << "[5] Find Client" << endl;
		cout << setw(50) << left << "[6] Transactions" << endl;
		cout << setw(50) << left << "[7] Manage Users" << endl;
		cout << setw(50) << left << "[8] Logout" << endl;
		LineOfEquals();
		cout << setw(20) << left << "Enter The Service Number : ";
		cin >> EnteredNum;
		cin.ignore();

		// Decisions
		DecisionsFlow((Operations)EnteredNum, user.Permissions);
	} while (EnteredNum != 8);
}

int main()
{
	Login();
}