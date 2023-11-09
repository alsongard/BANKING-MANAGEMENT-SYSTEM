//BANKING MANAGEMENT SYSTEM
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
    void updateDetails();
};

void customer::getDetails()
{
    //ofstream myfile("customerDetails.txt", ios::app);
    cout<<"Enter customer Id"<<endl;
    cin>>customerId;
    //myfile<<customerId;
    cout<<"Enter customer Name"<<endl;
	cin.ignore();
    cin.getline(customerName, 100);
    //myfile<<customerName;
    cout<<"Enter the customer age"<<endl;
    cin>>customerAge;
    //myfile<<customerAge;
	cout<<"enter phoneNumber"<<endl;
	cin>>customerPhoneNumber;
    //myfile<<customerPhoneNumber;
    cout<<"Enter customer Address"<<endl;
    cin>>customerAddress;
    //myfile<<customerAddress;
    cout<<"user details have been captured, kindly proceed to create account"<<endl;
}
void customer::updateDetails()
{
    cout<<"enter account number \n";
    cin>>customerId;
    cout<<"Enter customer name \n";
    cin.getline(customerName, 100);
    cout<<"Enter the type of account "<<" Saving account or Family Account"<<endl;
}

class accounts : public customer//main inheritance - getDetails();
{
    public:
	int accountNumber;
	int balance;
    char accountType[20];

    //function belonging to the account class
    void openAccount();
	// void closeAccount();
	void updateAccount();  
	void displayDetails();
	int returnAccNum() const
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
	cin.ignore();
    cout<<"Enter the type of account for the user \n"<<"Saving account or Family Account"<<endl;
    cin.getline(accountType, 20);
	cout<<"You acccount is successfully created\n";
	cout<<endl<<endl;
}
// void accounts::closeAccount()
// {
//     cout<<"Enter the account number \n";
//     cin>>accountNumber;
// }
void accounts::updateAccount()
{
	cout<<"enter the account number : \n";
	cin>>accountNumber;
	cout<<"Enter the type of account : \n";
	cin>>accountType;

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

class transactions : public accounts//inherit attributes and methods from accounts class
{	
	//declare methods/functions
	void makeDeposit();
	void makeWithdraw();
	void updateAccount();
	void getTransactionHistory();
};
void writeAccount();
void closeAccount(int);
void displayAccountDetails(int);
int main()
{

    int choice;
    //PREVENT READ CHARACTERS
	while (choice != 8)
	{
		cout<<"WELCOME TO CRYPTO BANKING SYSTEM"<<endl;
		cout<<"TO GET STARTED, CHOOSE ONE OF THE OPTIONS BELOW"<<endl;
		cout<<"=================MAIN MENU=================="<<endl;
		cout<<"1: CREATE ACCOUNT"<<endl;
		cout<<"2: SIGN ACCOUNT"<<endl;
		cout<<"3: CLOSE ACCOUT"<<endl;
		cout<<"4: UPDATE ACCOUNT"<<endl;
		cout<<"5: WITHDRAW MONEY"<<endl;
		cout<<"6: DEPOSIT MONEY"<<endl;
		cout<<"7: DISPLAY ACCOUNTS"<<endl;
		cout<<"8: Exit"<<endl;
		cout<<endl;

		cout<<"Choose the options from the above list\n";
		cin>>choice;

			
		int accountNum;
		switch (choice)
		{
			case 1:
				system("clear");
				writeAccount();
				
				break;
			case 2:
				system("clear");
				cout<<"Enter your bamk account number\n";
				cin>>accountNum;
				//sign account func
				break;
			case 3:
				system("clear");
				cout<<"Enter account number\n";
				cin>>accountNum;
				closeAccount(accountNum);
				break;
			case 4:
				system("clear");
				cout<<"Enter your account number\n";
				cin>>accountNum;
				//update money
				break;
				
			case 5:
				system("clear");
				cout<<"Enter accout number\n";
				cin>>accountNum;
				//withdraw account
				break;
				
			case 6:
				system("clear");
				cout<<"Enter account Number\n";
				cin>>accountNum;
				//deposit money
				break;
			
			case 7:
				system("clear");
				cout<<"Enter account number\n";
				cin>>accountNum;
				displayAccountDetails(accountNum);
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
	outFile.open("accountDetails.dat", ios::out | ios::app | ios::binary);
	accountObject.getDetails();
	accountObject.openAccount();
	outFile.write(reinterpret_cast<char *>(&accountObject), sizeof(accounts));
	outFile.close();
}
void closeAccount(int num)
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
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);

	while(inFile.read(reinterpret_cast<char *>(&accountsObject), sizeof(accounts)))
	{
		if(accountsObject.returnAccNum()!= num)
		{
			outFile.write(reinterpret_cast<char *> (&accountsObject), sizeof(accounts));
		}
	}
	inFile.close();
	outFile.close();
	remove("bankAccount.dat");
	rename("Temp.dat", "bankAccount.dat");
	cout<<"Account has been succesfully removed\n";
	cout<<endl;
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
		if (accountsObject.returnAccNum() == num)
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
