#ifndef BANK_H
#define BANK_H
#include <iostream>
using namespace std;
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
class account
{
	double acno;
	char name[50];
	double deposit;
	char type;

public:
	//Methods
	void createAccount();	
	void displayInfo() const;
	void modifyAccount();	
	void addAmount(int);	
	void withDraw(int);	
	void accountDetails() const;	
	int returnAccNum() const;	
	int returnBalance() const;	
	char returnAccType() const;	
};
#endif /* BANK_H */
/////////////////////////////////
//function to get data from user
/////////////////////////////////
void account::createAccount()
{
	cout << "\nEnter The account No. :";
	cin >> acno;
	cout << "\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter Type of The account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\nEnter The Initial amount : ";
	cin >> deposit;
	cout << "\n\n\nAccount Created!!!";
}
//////////////////////////////////
//function to show data on screen
//////////////////////////////////
void account::displayInfo() const
{
	cout << "\nAccount Number. : " << acno;
	cout << "\nAccount Holder Name : " << name;
	cout << "\nType of Account : " << type;
	cout << "\nBalance amount : " << deposit;
}
///////////////////////////
//function to add new data
///////////////////////////
void account::modifyAccount()
{
	system("Color E4");
	cout << "\nAccount Number. : " << acno;
	cout << "\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify Account Type : ";
	cin >> type;
	type = toupper(type);
	cout << "\nModify Balance amount : ";
	cin >> deposit;
}
//////////////////////////////////////////////////////
//function to accept amount and add to balance amount
//////////////////////////////////////////////////////
void account::addAmount(int x)
{
	deposit += x;
}
////////////////////////////////////////////////////////////
//function to accept amount and subtract from balance amount
////////////////////////////////////////////////////////////
void account::withDraw(int x)
{
	deposit -= x;
}
/////////////////////////////////////////
//function to show data in tabular format
/////////////////////////////////////////
void account::accountDetails() const
{
	ios_base::fmtflags flags = cout.flags();
	cout << left << setw(25) << acno << setw(25) << name << setw(20) << type << setw(20) << deposit << endl;
	cout.flags(flags);
}
////////////////////////////////////
//function to return account number
////////////////////////////////////
int account::returnAccNum() const
{
	return acno;
}
///////////////////////////////////
//function to return balance amount
///////////////////////////////////
int account::returnBalance() const
{
	return deposit;
}
////////////////////////////////////
//function to return type of account
////////////////////////////////////
char account::returnAccType() const
{
	return type;
}

