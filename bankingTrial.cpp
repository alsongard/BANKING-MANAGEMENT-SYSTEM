#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;
class customer
{
    public:
    char  customerName[100];
    int customerId;
    int customerAge;
    int customerAddress;
    int customerPhoneNumber;

    //methods getDetails(), updateDetails()
    void getDetails();
};

void customer::getDetails()
{
    cout<<"Enter customer Id"<<endl;
    cin>>customerId;
    cout<<"Enter customer Name"<<endl;
    cin.ignore();
    cin.getline(customerName, 100);
    cout<<"Enter the customer age"<<endl;
    cin>>customerAge;
    cout<<"enter phoneNumber"<<endl;
    cin>>customerPhoneNumber;
    cout<<"Enter customer Address"<<endl;
    cin>>customerAddress;
    cout<<"user details have been captured, kindly proceed to create account"<<endl;
}
// void customer::updateDetails()//member function of customer 
// //i will not use this for updating details of customer
// {
//     cout<<"enter account number \n";
//     cin>>customerId;
//     cout<<"Enter customer name \n";
//     cin.getline(customerName, 100);
//     cout<<"Enter the type of account "<<" Saving account or Family Account"<<endl;
//}

class accounts : public customer//main inheritance - getDetails();
{
    public:
	int accountNumber;
	int balance;
    char accountType[20];
    //function belonging to the account class
    void openAccount();
	void closeAccount(int num);
	void updateAccount(int checkNum);  
	void displayDetails();
	int returnAccountNumber() const
	{
		return accountNumber;
	}
};

void accounts::openAccount()
{   
    cout<<"Enter the Account Number\n";
    cin>>accountNumber;
    //myfile<<accountNumber;
    cout<<"Enter the amount you wish to deposit\n";
    cin>>balance;
    cout<<"Enter the type of account for the user \n"<<"Saving account or Family Account"<<endl;
	cin.ignore();
    cin.getline(accountType, 20);
	cout<<"You acccount is successfully created\n";
	cout<<endl<<endl;
}
void accounts::updateAccount(int checkNum)
{
	accounts accountObject;
	//the account number is provided when updateAccount is called
	//check if account exists
	fstream inFile;
	inFile.open("accountDetails.dat", ios::in | ios::out | ios::binary);
	if (!inFile)
	{
		cout<<"An error occured while accessing the file\n";
	}
	//read data from file
	while(inFile.read(reinterpret_cast<char *>(&accountObject), sizeof(accounts)))
	{
		if (accountObject.returnAccountNumber() == checkNum)
	{
		cout<<"Account user has been found \n";
		cout<<"the user details for the account number are : \n";
		cout<<"Account Number : "<<accountObject.accountNumber<<endl;
		cout<<"Customer Id : "<<accountObject.customerId<<endl;
		cout<<"Account User Name : "<<accountObject.customerName<<endl;
		cout<<"Account customerAddress : "<<accountObject.customerAddress<<endl;
		cout<<"Account user phone number "<<accountObject.customerPhoneNumber<<endl;
		//PROCEED TO CHANGE USER ACCOUNT DETAILS
		cout<<"PROCEED TO CHANGE USER ACCOUNT DETAILS \n";
		cout<<"Enter the new user name \n";
		cin.ignore();
		cin.getline(accountObject.customerName, 100);
		cout<<"Enter new user home address \n";
		cin>>accountObject.customerAddress;
		cout<<"Enter new user phone number \n";
		cin>>accountObject.customerPhoneNumber;
		cout<<"Enter the type of account you wish to change to \n Savings Account \n Family Account"<<endl;
		cin>>accountObject.accountType;

		//how to change data from file
		inFile.seekp(-static_cast<streamoff>(sizeof(accountObject)), ios::cur);
		inFile.write(reinterpret_cast<char *>(&accountObject), sizeof(accountObject));
	}
	}
	
		cout<<"User Account Details have been changed successfully\n";

}
void accounts::displayDetails()
{
	cout<<"Account Number : "<<accountNumber<<endl;
	cout<<"Account User Name : "<<customerName<<endl;
	cout<<"Account type : "<<accountType<<endl;
	cout<<"Account Balance : "<<balance<<endl;
	cout<<endl;
	cout<<endl;
}
void accounts::closeAccount(int num)
{
	// 	int accountNumber; int balance char accountType[20];
	accounts accountsObject;
	
	fstream inFile;
	fstream outFile;
	inFile.open("accountDetails.dat", ios::in | ios::binary);
	if(!inFile)
	{
		cout<<"the file does not exist !!! Check another time\n";
	}
	
	//create a temp file for storing data without the user specified
	outFile.open("temp.dat",ios::out | ios::binary);

	while(inFile.read(reinterpret_cast<char *>(&accountsObject), sizeof(accounts)))
	{
		if(accountsObject.returnAccountNumber()!= num)
		{
			outFile.write((char *)(&accountsObject), sizeof(accounts));
		}
	}
	inFile.close();
	outFile.close();
	remove("accountDetails.dat");
	rename("temp.dat", "accountDetails.dat");
	cout<<"Account has been succesfully removed\n";
	cout<<endl;
}
class transaction : public accounts//inherit attributes and methods from accounts class
{	
    public:
	//declare methods functions
	void makeDeposit(int checkNumber);
	void makeWithdraw(int checkNumber);
	void getTransaction(int checkNumber);
};
void transaction::getTransaction(int checkNumber)
{	
	transaction transactionObject;
	bool condition = false;
	fstream inFile;
	inFile.open("accountDetails.dat", ios::in | ios::binary);//read data from original
	fstream outFile;
	outFile.open("transaction.dat", ios::out | ios::binary);//get details and compare specific changes
	while(inFile.read(reinterpret_cast<char *>(&transactionObject), sizeof(transaction)))
	{
		if (transactionObject.returnAccountNumber() == checkNumber)
		{
			condition = true;
			cout<<"Account has been found\n";
			cout<<"ACCOUNT TRANSACTION HISTORY\n";
		}
	}
}
void transaction::makeDeposit(int checkNumber)
{
    transaction transactionObject;
    int amount;
	bool condition = false;
    //check if account number exitst - read file and compare
    fstream inFile;
    inFile.open("accountDetails.dat", ios::in | ios::out | ios::binary);
    //check existance of file
    if (!inFile)
    {
        cout<<"Error !! No file was currently found, try again later\n";
    }
    while(inFile.read(reinterpret_cast<char *>(&transactionObject), sizeof(transaction)));
    {
		//multi-leve inheritance of returnAccountNumber()
        if (transactionObject.returnAccountNumber() == checkNumber)
        {
			bool condition = true;
            cout<<"accountFound and proceed to deposit \n";
			cout<<"Current balance : "<<transactionObject.balance<<endl;
            cout<<"Enter the amount you wish to deposit \n";
            cin>>amount;
            transactionObject.balance = transactionObject.balance + amount;
            cout<<"New user balance :"<<transactionObject.balance<<endl;
			inFile.seekp(-static_cast<streamoff>(sizeof(transactionObject)), ios::cur);
			inFile.write(reinterpret_cast<char *>(&transactionObject), sizeof(transaction));
			cout<<"Records updated successfully \n";
        }
 
    }
	if (!condition)
	{
		cout<<"Account number could not be found.\n";
	}
	
	
}
void transaction::makeWithdraw(int checkNumber)
{
    transaction transactionObject;
	bool condition = false;
    int amount, realNumber;
    //check whether account exist
    //read data from file for comparisons
    fstream inFile;
    inFile.open("accountDetails.dat", ios::in | ios::out | ios::binary);
    //check for file existance 
    if (!inFile)
    {
        cout<<"Error!! the file does not exist\n";
    }
	while(inFile.read(reinterpret_cast<char *>(&transactionObject), sizeof(transaction)))
	{
		if (transactionObject.returnAccountNumber() == checkNumber)
		{
			condition = true;
			cout<<"Account has been found\n";
			cout<<"Current user account balance is : "<<transactionObject.balance<<endl;
			cout<<"Enter amount to withdraw  : \n";
			cin>>amount;
			
			if (amount < transactionObject.balance)
			{
				cout<<"You can proceed to withdraw \n";
				transactionObject.balance = transactionObject.balance - amount;
				cout<<"You have successfully withdrawn : "<<amount<<endl;
				cout<<"Current balance : "<<transactionObject.balance<<endl;
				inFile.seekp(-static_cast<streamoff>(sizeof(transactionObject)), ios::cur);
				inFile.write(reinterpret_cast<char *>(&transactionObject), sizeof(transaction));
				// realNumber = transactionObject.balance;
				// cout<<"Test for real Number : "<<realNumber<<endl;

			}
			else
			{
				cout<<"You  do not have the required funds to proceed with these transaction\n";
			}
			
		}

	}
	if(!condition)
	{
		cout<<"The account has not been found\n";
	}    
}
void writeAccount();
void closeAccount(int);
void displayAccountDetails(int);
int main()
{

    transaction transactionObject;
	accounts accountObject;
    int choice;
    //PREVENT READ CHARACTERS
	while (choice != 7)
	{
		cout<<"WELCOME TO CRYPTO BANKING SYSTEM"<<endl;
		cout<<"TO GET STARTED, CHOOSE ONE OF THE OPTIONS BELOW"<<endl;
		cout<<"=================MAIN MENU=================="<<endl;
		cout<<"1: CREATE ACCOUNT"<<endl;
		cout<<"2: UPDATE ACCOUNT"<<endl;
		cout<<"3: DISPLAY ACCOUNT"<<endl;
		cout<<"4: WITHDRAW MONEY"<<endl;
		cout<<"5: DEPOSIT MONEY"<<endl;
		cout<<"6: CLOSE ACCOUNT"<<endl;
		cout<<"7: Exit"<<endl;
		cout<<endl;

		cout<<"Choose the options from the above list\n";
		cin>>choice;

			
		int accountNum;
		switch (choice)
		{
			case 1:
				system("clear");
				writeAccount();//create account
				break;
			case 2:
				system("clear");
				cout<<"Enter account number\n";
				cin>>accountNum;
				accountObject.updateAccount(accountNum);//update account details
				break;
			case 3:
				system("clear");
				cout<<"Enter your account number\n";
				cin>>accountNum;
				displayAccountDetails(accountNum);//display user details
				break;
				
			case 4:
				system("clear");
				cout<<"Enter accout number\n";
				cin>>accountNum;
				transactionObject.makeWithdraw(accountNum);//withdraw function
				break;
				
			case 5:
				system("clear");
				cout<<"Enter account Number\n";
				cin>>accountNum;
				transactionObject.makeDeposit(accountNum);//deposit function
				break;
			
			case 6:
				system("clear");
				cout<<"Enter account number\n";
				cin>>accountNum;
				accountObject.closeAccount(accountNum);//close account
				break;
		}
	}
	cout<<"Thank you for using Crypto Bank. We hope to see you soon\n";
	return (0);
}

void writeAccount()
{
	accounts accountObject;
	fstream outFile;
	outFile.open("accountDetails.dat", ios::app | ios::binary);
	accountObject.getDetails();
	accountObject.openAccount();
	outFile.write(reinterpret_cast<char *>(&accountObject), sizeof(accounts));
	outFile.close();
}
void displayAccountDetails(int num)
{
	accounts accountsObject;
	bool condition = false;

	fstream inFile;
	inFile.open("accountDetails.dat", ios::in | ios::binary);
	
	if(!inFile)
	{
		cout<<"Error :: the file does not exist!! \n";
	}
	cout<<"BANK ACCOUNT DETAILS FOR : \n";	
	while(inFile.read(reinterpret_cast<char *>(&accountsObject), sizeof(accounts)))
	{
		if (accountsObject.returnAccountNumber() == num)
		{
			accountsObject.displayDetails();
			condition = true;
		}
	}
	inFile.close();
	if (condition = false)
	{
		cout<<"The account number does not exist\n";
	}
}
