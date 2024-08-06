#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<string>
#define MIN_BAL 500
using namespace std;
class Accounts
{
    private:
    float balance;
    string fname,lname;
    long accountnumber;
    static long count;
    public:
    Accounts(){}
    Accounts(string firstname,string lastname,float balance)
    {
        fname=firstname;
        lname=lastname;
        accountnumber=++count;
        this->balance=balance;
    }
    string getfirstname(){return fname;}
    string getlastname(){return lname;}
    float getbalance(){return balance;}
    long getaccountnumber(){return accountnumber;}
    static void setcount(long a);
    static long getcount();
    void initial();
    void Deposite(float deposite);
    void Withdrawl(float deposite);
  friend ostream &operator<<(ostream &out,Accounts &acc);
  friend ofstream &operator<<(ofstream &out,Accounts &acc);
  friend ifstream &operator>>(ifstream &ifs,Accounts &acc);
  };
  class Bank
  {
    private:
    map<long,Accounts>m;
    public:
    Bank();
    Accounts Openaccount(string firstname,string lastname,float balance);
    Accounts Balanceenquiry(long accountnumber);
    Accounts Deposite(long accountnumber,float deposite);
    Accounts Withdrawl(long accountnumber,float deposite);
    void CloseAccount(long accountnumber);
    void ShowAllAccounts();
    ~Bank();
  };
  class InsufficientFunds:exception{};
int main(){
    cout<<"***Banking System***"<<endl<<endl;
    int choice;
    string fname,lname;
    float balance,deposite;
    long accountnumber;
    Accounts acc;
    Bank b;
    do{
        acc.initial();
        cin>>choice;
        switch(choice)
        {
            case 1: cout<<"Enter First Name:";
            cin>>fname;
            cout<<"Enter Last Name:";
            cin>>lname;
            cout<<"Enter initial Balance:";
            cin>>balance;
            if(balance<MIN_BAL)
            {
            throw InsufficientFunds();
        }
            acc=b.Openaccount(fname,lname,balance);
            cout<<endl;
            cout<<"Congratulation Account is Created"<<endl;
            cout<<acc;
            break;
            case 2: cout<<"Enter Account Number:";
            cin>>accountnumber;
            acc=b.Balanceenquiry(accountnumber);
            cout<<endl;
            cout<<"Your Account Details"<<endl;
            cout<<acc;
            break;
            case 3: cout<<"Enter Account Number:";
            cin>>accountnumber;
            cout<<"Enter Amount:";
            cin>>deposite;
            acc=b.Deposite(accountnumber,deposite);
            cout<<endl;
            cout<<"Amount is Deposited"<<endl;
            cout<<acc;
            break;
            case 4: cout<<"Enter Account Number:";
            cin>>accountnumber;
            cout<<"Enter Amount:";
            cin>>deposite;
            cout<<endl;
            acc=b.Withdrawl(accountnumber,deposite);
            cout<<"Amount is Withdrawled"<<endl;
            cout<<acc;
            break;
            case 5: cout<<"Enter Account Number:";
            cin>>accountnumber;
            cout<<endl;
            b.CloseAccount(accountnumber);
            break;
            case 6: cout<<endl;
            b.ShowAllAccounts();
            break;
            case 7: break;
            default:cout<<"\nEnter correct choice";
            exit(0);
        }
    }while(choice!=7);
    return 0;
}
void Accounts::initial()
{
    cout<<"\tSelect one option below"<<endl;
    map<int,string>m;
    m.insert(pair<int,string>(1,"Open An Account"));
    m.insert(pair<int,string>(2,"Balance Enquiry"));
    m.insert(pair<int,string>(3,"Deposit"));
    m.insert(pair<int,string>(4,"Withdrawl"));
    m.insert(pair<int,string>(5,"Close an Account"));
    m.insert(pair<int,string>(6,"Show All Accounts"));
    m.insert(pair<int,string>(7,"Quit"));
    map<int,string>::iterator itr;
    for(itr=m.begin();itr!=m.end();itr++)
    {
        cout<<"\t"<<itr->first<<" "<<itr->second<<endl;
    }
    cout<<"Enter your choice:";
}
ostream &operator<<(ostream &out,Accounts &acc)
{
    out<<"First Name:"<<acc.getfirstname()<<endl;
    out<<"Last Name:"<<acc.getlastname()<<endl;
    out<<"Account Number:"<<acc.getaccountnumber()<<endl;
    out<<"Balance:"<<acc.getbalance()<<endl<<endl;
    return out;
}
ofstream &operator<<(ofstream &out,Accounts &acc)
{
    out<<acc.getfirstname()<<endl;
    out<<acc.getlastname()<<endl;
    out<<acc.getaccountnumber()<<endl;
    out<<acc.getbalance()<<endl<<endl;
    return out;
}
long Accounts::count=0;
Accounts Bank::Openaccount(string firstname,string lastname,float balance)
{
    Accounts acc(firstname,lastname,balance);
    m.insert(pair<long,Accounts>(acc.getaccountnumber(),acc));
    ofstream outfile("my.txt",ios::trunc);
    map<long,Accounts>::iterator itr;
    for(itr=m.begin();itr!=m.end();itr++)
    {
        outfile<<itr->second;
    }
    outfile.close();
    return acc;
}
 Accounts Bank::Balanceenquiry(long accountnumber)
 {
     map<long,Accounts>::iterator itr;
     itr=m.find(accountnumber);
     return itr->second;
 }
 Accounts Bank::Deposite(long accountnumber,float deposite)
 {
      map<long,Accounts>::iterator itr;
     itr=m.find(accountnumber);
     itr->second.Deposite(deposite);
     return itr->second;
 }
 void Accounts::Deposite(float deposite)
 {
     balance+=deposite;
 }
 void Accounts::Withdrawl(float deposite)
 {
     if(balance-deposite<MIN_BAL)
     throw InsufficientFunds();
          balance-=deposite;
 }
  Accounts Bank::Withdrawl(long accountnumber,float deposite)
 {
      map<long,Accounts>::iterator itr;
     itr=m.find(accountnumber);
     itr->second.Withdrawl(deposite);
     return itr->second;
 }
 void Bank::ShowAllAccounts()
 {
     map<long,Accounts>::iterator itr;
     for(itr=m.begin();itr!=m.end();itr++)
     {
         cout<<"Account"<<" "<<itr->first<<endl<<itr->second;
     }   
     
 }
 void Bank::CloseAccount(long accountnumber)
 {
     map<long,Accounts>::iterator itr;
     itr=m.find(accountnumber);
     cout<<"Account is Closed"<<endl;
            cout<<itr->second<<endl;
            m.erase(accountnumber);
 }
 Bank::Bank()
 {
    Accounts acc;
    ifstream infile;
    infile.open("my.txt");
    if(!infile)
    {
        return;
    }
    while(!infile.eof())
    {
        infile>>acc;
        m.insert(pair<long,Accounts>(acc.getaccountnumber(),acc));
    }
    acc.setcount(acc.getaccountnumber());
    infile.close();
 }
 void Accounts::setcount(long a)
 {
    count=a; 
 }
 long Accounts::getcount()
 {
     return count;
 }
 Bank::~Bank()
 {
    ofstream outfile("my.txt",ios::trunc);
    map<long,Accounts>::iterator itr;
    for(itr=m.begin();itr!=m.end();itr++)
    {
        outfile<<itr->second;
    }
    outfile.close();
 }
 ifstream &operator>>(ifstream &ifs,Accounts &acc)
 {
     ifs>>acc.fname;
     ifs>>acc.lname;
     ifs>>acc.accountnumber;
     ifs>>acc.balance;
     return ifs;
 }