#ifndef __ACCOUNT__H_
#define __ACCOUNT__H_

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

class account
{
	public:
		account();
		~account();
		bool insert(int num, string fname, string lname, double balance);
		bool remove(int num);
		void deposit(int num);
		void withdraw(int num);
		void transfer(int num1, int num2);
		bool verify(int num);
		bool printInfo(int num);
		void printAccounts();
		void print(ostream &out);


	private:
		struct node
		{
			int actNum;
			string firstName;
			string lastName;
			double balance;
			node *next;
		};
		node *headptr;
};

account::account()
{
	headptr = nullptr;
}

account::~account()
{
	node *temp = nullptr;
	temp = headptr;
	while (temp != nullptr)
	{
		headptr = headptr->next;
		delete temp;
		temp = headptr;
	}
}

bool account::insert(int num, string fname, string lname, double balance)
{
	node *temp, *prev, *curr;
	temp = new(nothrow)node;
	if (temp == nullptr)
		return false;
	temp->actNum = num;
	temp->firstName = fname;
	temp->lastName = lname;
	temp->balance = balance;
	temp->next = nullptr;
	if (headptr == nullptr)
	{
		headptr = temp;
		return true;
	}
	if (temp->lastName < headptr->lastName)
	{
		temp->next = headptr;
		headptr = temp;
		return true;
	}
	prev = headptr;
	curr = headptr;
	while (curr != nullptr && curr->lastName < temp->lastName)
	{
		prev = curr;
		curr = curr->next;
	}
	prev->next = temp;
	temp->next = curr;
	return true;
}

bool account::remove(int num)
{
	node *temp, *prev, *curr;
	if (headptr == nullptr)
		return false;
	if (headptr->actNum == num)
	{
		temp = headptr;
		headptr = headptr->next;
		delete temp;
		return true;
	}
	prev = headptr;
	curr = headptr;
	while (curr != nullptr && curr->actNum != num)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == nullptr)
		return false;
	prev->next = curr->next;
	delete curr;
	return true;
}

void account::deposit(int num)
{
	double amount = 0;
	node *temp = nullptr;
	temp = headptr;
	if (temp == nullptr)
		return;
	while (temp != nullptr && temp->actNum != num)
		temp = temp->next;
	cout << "How much would you like to deposit?" << endl;
	cin >> amount;
	if (amount > 0)
	{
		temp->balance += amount;
		cout << endl << "Transaction Successful!" << endl;
		cout << endl << "New Balance:  $ " << temp->balance << endl << endl;
	}
}

void account::withdraw(int num)
{
	double amount = 0;
	node *temp = nullptr;
	temp = headptr;
	if (temp == nullptr)
		return;
	while (temp != nullptr && temp->actNum != num)
		temp = temp->next;
	cout << "How much would you like to withdraw?" << endl;
	cin >> amount;
	if (amount > 0)
	{
		temp->balance = temp->balance - amount;
		cout << endl << "Transaction Successful!" << endl;
		cout << endl << "New Balance:  $ " << temp->balance << endl << endl;
	}
}

void account::transfer(int num1, int num2)
{
	double amount = 0;
	node *temp1 = nullptr;
	node *temp2 = nullptr;
	temp1 = headptr;
	temp2 = headptr;
	while (temp1 != nullptr && temp1->actNum != num1)
		temp1 = temp1->next;
	while (temp2 != nullptr && temp2->actNum != num2)
		temp2 = temp2->next;
	cout << "How much would you like to transfer?" << endl;
	cin >> amount;
	if (amount > 0)
	{
		temp1->balance = temp1->balance - amount;
		temp2->balance += amount;
		cout << endl << "Transaction Successful!" << endl;
		cout << endl << "New Balance:  $ " << temp1->balance << endl << endl;
	}
}

bool account::verify(int num)
{
	node *temp = nullptr;
	temp = headptr;
	while (temp != nullptr)
	{
		if (temp->actNum == num)
			return false;
		temp = temp->next;
	}
	return true;
}

bool account::printInfo(int num)
{
	node *temp;
	temp = headptr;
	while (temp != nullptr && temp->actNum != num)
		temp = temp->next;
	if (temp == nullptr)
		return false;
	cout << endl << endl;
	cout << temp->lastName << ", " << temp->firstName << endl << endl;
	cout << "Balance:    $ " << temp->balance << endl << endl;
	return true;
}

void account::printAccounts()
{
	node *temp;
	temp = headptr;
	cout << endl;
	while (temp != nullptr)
	{
		cout << temp->actNum << endl;
		cout << temp->lastName << ", " << temp->firstName << endl << endl;
		temp = temp->next;
	}
}

void account::print(ostream &out)
{
	node *temp = nullptr;
	temp = headptr;
	int i = 1;
	if (temp != nullptr)
	{
		while (temp->next != nullptr)
		{
			out << i++ << endl;
			out << temp->actNum << endl << temp->lastName << ", ";
			out << temp->firstName << endl << temp->balance << endl;
			temp = temp->next;
		}
		out << i++ << endl;
		out << temp->actNum << endl << temp->lastName << ", ";
		out << temp->firstName << endl << temp->balance << endl;
	}

}

#endif