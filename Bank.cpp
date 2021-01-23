#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<cctype>
#include<iomanip>
#include"bank.h"
using namespace std;
////////////////////////////
//function to write in file
////////////////////////////
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("bank.txt", ios::binary | ios::app);
	ac.createAccount();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}
/////////////////////////////////////////////
//function to read specific record from file
/////////////////////////////////////////////
void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("bank.txt", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\nBALANCE DETAILS\n";

	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.returnAccNum() == n)
		{
			ac.displayInfo();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nAccount number does not exist";
}
////////////////////////////////////
//function to modify record of file
////////////////////////////////////
void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("bank.txt", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.returnAccNum() == n)
		{
			ac.displayInfo();
			cout << "\n\nEnter The New Details of account" << endl;
			ac.modifyAccount();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}

///////////////////////////////////
//function to delete record of file
///////////////////////////////////
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("bank.txt", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.txt", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.returnAccNum() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.txt", "bank.txt");
	cout << "\n\n\tRecord Deleted ..";
}
////////////////////////////////////////////////
//function to display all accounts deposit list
////////////////////////////////////////////////
void display_all()
{
	system("Color F9");
	/*const int LINELENGTH = 60;
	string header(LINELENGTH, '*');*/
	
	account ac;
	ifstream inFile;
	inFile.open("bank.txt", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << '\n';
	ios_base::fmtflags flags = cout.flags();
	cout << left << setw(25) << "A/c no." <<setw(25) << "NAME" <<setw(20) << "Type"  << setw(20) << "Balance\n";
	cout.flags(flags);
	cout << '\n';
	

	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.accountDetails();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************
void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("bank.txt", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.returnAccNum() == n)
		{
			ac.displayInfo();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter The amount to be deposited";
				cin >> amt;
				ac.addAmount(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdraw";
				cin >> amt;
				int bal = ac.returnBalance() - amt;
				if ((bal < 500 && ac.returnAccType() == 'S') || (bal < 1000 && ac.returnAccType() == 'C'))
					cout << "Insufficience balance";
				else
					ac.withDraw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}
////////////////////////
//INTRODUCTION FUNCTION
////////////////////////
void intro()
{
	system("Color 30");
	cout << "\n\n\n\tBARJONA BANK";
	cout << "\n\n\t MANAGEMENT";
	cout << "\n\n\t  SYSTEM";
	cout << "\n\n\n\nMADE BY : JERRY SIMON";
	cout << "\n\nSCHOOL : BRIGHAM YOUNG UNIVERSITY IDAHO";
	cin.get();
}
//***********************************
//   THE MAIN FUNCTION OF PROGRAM
//***********************************
int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		system("Color 0F");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t01. NEW ACCOUNT";
		cout << "\n\n\t02. DEPOSIT AMOUNT";
		cout << "\n\n\t03. WITHDRAW AMOUNT";
		cout << "\n\n\t04. BALANCE ENQUIRY";
		cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout << "\n\n\t06. CLOSE AN ACCOUNT";
		cout << "\n\n\t07. MODIFY AN ACCOUNT";
		cout << "\n\n\t08. EXIT";
		cout << "\n\n\tSelect Your Option (1-8) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			delete_account(num);
			break;
		case '7':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			modify_account(num);
			break;
		case '8':
			cout << "\n\n\tThanks for using BARJONA bank managemnt system";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch >= 1 || ch <= 8);
	return 0;
}
//***********************
//    END OF PROJECT
//***********************