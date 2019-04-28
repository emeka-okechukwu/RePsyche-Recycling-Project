//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************


class account
{
	int acno;
	char name[50];
	int deposit;
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
};         //class ends here

void account::create_account()
{
	cout<<"\nEnter Your Pin No. :";
	cin>>acno;
	cout<<"\n\nEnter Your Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter 0 to confirm account opening : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
{
	cout<<"\nPin No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nPin No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<setw(6)<<deposit<<endl;
}

	
int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

//***************************************************************
//    	function declaration
//****************************************************************
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void leaderboard();	//function to display the most contributor or depositor
void intro();	//introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	char ch;
	int num;
  int op;
  int pass;
	intro();
	
  menu:
   cout << "\t \t WHAT IS YOUR ROLE?" << endl;
   cout << "USER [1]" << endl;
   cout << "STAKEHOLDER [2]" << endl;
   cout << "......" << endl;
   cout << ">>>" << endl; cin >> op;
   switch(op){
        case 1:
            goto user;
            break;
       
        case 2:
            goto stakeholder;
            break;
           
        default:
            cout << "Retype your choice" << endl;
            goto menu;
   }

  user:
  do
	{
		system("cls");
		cout<<"\n\n\n\tUSER MENU";
		cout<<"\n\n\t1 CREATE ACCOUNT";
		cout<<"\n\n\t2 DEPOSIT CREDIT";
		cout<<"\n\n\t3 SPEND CREDIT";
		cout<<"\n\n\t4 BALANCE STATEMENT";
		cout<<"\n\n\t5 CLOSE MY ACCOUNT";
		cout<<"\n\n\t6 MODIFY MY ACCOUNT";
		cout<<"\n\n\t7 EXIT";
		cout<<"\n\n\tSelect Your Option From 1-7 ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter Your pin No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter Your pin No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter Your pin No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			cout<<"\n\n\tEnter Your pin No. : "; cin>>num;
			delete_account(num);
			break;
		 case '6':
			cout<<"\n\n\tEnter Your pin No. : "; cin>>num;
			modify_account(num);
			break;
		 case '7':
			cout << "\n\n\tThanks for using our recycling system" << endl;
      goto menu;
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='7');

  stakeholder:
  cout << "Password: "; cin >> pass;
  if (pass == 123){
            cout << "Success !" << endl;
            do
                {
                  system("cls");
                  cout<<"\n\n\n\tWELCOME STAKEHOLDER";
                  cout<<"\n\n\t1 ALL ACCOUNT HOLDER LIST";
                  cout<<"\n\n\t2 VIEW LEADERBOARD";
                  cout<<"\n\n\t3 EXIT";
                  cout<<"\n\n\tSelect Your Option From 1-3 ";
                  cin>>ch;
                  system("cls");
                  switch(ch)
                  {
                  case '1':
                    display_all();
                    break;
                  case '2':
                    leaderboard();
                    break;
                  case '3':
                    cout << "\n\n\tThanks for using recycling system" << endl;
                    goto menu;
                    break;
                  default :cout<<"\a";
                  }
                  cin.ignore();
                  cin.get();
                }while(ch!='2');
                      }
  else{
        cout << "Password do not match!" << endl;
        goto menu;
        return 1;
  }
  return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open!! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open!! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open!! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open!! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME            CREDITt\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open!! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSIT CREDIT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tSPEND CREDIT";
				cout<<"\n\nEnter The amount to be spent: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<amt))
					cout<<"Not enough credit";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//***************************************************************
//    	function to display the most contributor or depositor
//****************************************************************

void leaderboard()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME            Credit\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************


void intro()
{
	cout<<"\n\n\tAshesi as a Living Lab Presents";
	cout<<"\n\n\n\t     RePsyche";
	cout<<"\n\n\tA Recycling Project";
  cout << endl << endl;
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
