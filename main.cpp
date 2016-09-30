#include "account.h"

void inFile(account &act, fstream &accounts, string filename);
bool createAcc(account &act1, int count);
bool saveFile(account &act, fstream& fout, string filename);


int main(int argc, char**argv)
{
	int choice1 = 0, choice2 = 0, num = 0, pass = 0, count = 0;
	int num2 = 0;
	fstream accounts;
	string filename, fname, lname;
	account act;
	srand((int)time(nullptr));
	cout << setprecision(2) << fixed;
	if (argc > 2 || argc < 2)
	{
		cout << "Error Reading System!" << endl;
		exit(0);
	}
	if (argc == 2)
	{
		filename = argv[1];
		inFile(act, accounts, filename);
	}
	cout << "Bank System" << endl << endl;
	do
	{
		cout << "1) Access Account" << endl << "2) Create Account" << endl;
		cout << "3) View All Accounts On System" << endl;
		cout << "4) Delete Account" << endl;
		cout << "9) Exit System" << endl;
		cin >> choice1;
		if (choice1 == 1)
		{
			cin.ignore();
			cout << "Please Enter Account Number:    ";
			cin >> num;
			if (!act.printInfo(num))
			{
				cout << "ERROR" << endl;
				cout << "Account Not In System" << endl;
			}
			do
			{
				cout << "1) Deposit" << endl << "2) Withdraw" << endl;
				cout << "3) Transfer" << endl;
				cout << "9) Exit Account" << endl;
				cin >> choice2;
				if (choice2 == 1)
					act.deposit(num);
				if (choice2 == 2)
					act.withdraw(num);
				if (choice2 == 3)
				{
					cout << "Enter Account to Transfer to:  ";
					cin >> num2;
					act.transfer(num, num2);
				}
			} while (choice2 != 9);
		}
		if (choice1 == 2)
		{
			if (createAcc(act, count))
				count++;
		}
		if (choice1 == 3)
		{
			act.printAccounts();
		}
		if (choice1 == 4)
		{
			cout << "Enter Account Number to Delete  ";
			cin >> num;
			act.remove(num);
		}
	} while (choice1 != 9);

	saveFile(act, accounts, filename);
	return 0;
}

void inFile(account &act, fstream &accounts, string filename)
{
	string fname, lname;
	int actNum = 0;
	int num;
	double balance = 0;
	accounts.open(filename);
	if (!accounts)
	{
		cout << "Error opening file  " << filename << endl;
		return;
	}
	while (accounts >> num)
	{
		accounts >> actNum;
		accounts.ignore();
		getline(accounts, lname, ',');
		accounts.ignore();
		getline(accounts, fname, '\n');
		accounts >> balance;
		act.insert(actNum, fname, lname, balance);
	}
	accounts.close();
}

bool createAcc(account &act, int count)
{
	string fname, lname;
	int pass = 0, num = 0;
	double bal = 0;
	cin.ignore();
	cout << "Enter First Name:     ";
	getline(cin, fname);
	cout << "Enter Last Name:     ";
	getline(cin, lname);

	while (pass != 1)
	{
		if (!(count < 999))
		{
			cout << "Cannot Create Account" << endl;
			return false;
		}
		else
		{
			num = rand() % (999 - 100 + 1) + 100;
			if (act.verify(num))
				pass = 1;
		}
	}
	if (count < 999)
	{
		if (act.insert(num, fname, lname, bal))
		{
			cout << "Account Created Successfully!" << endl;
			cout << "Your account number is:   " << num << endl << endl;
			return true;
		}
	}
	return false;
}

bool saveFile(account &act, fstream& fout, string filename)
{
	fout.open(filename, ofstream::out | ofstream::trunc);
	if (!fout)
	{
		cout << "Error opening file" << filename << endl;
		return false;
	}
	act.print(fout);
	fout.close();
	return true;
}