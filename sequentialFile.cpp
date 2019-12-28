#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

class Student
{
	int id,age;
	string name;
	public:
		void input();

};

void Student::input()
{
	ofstream op;
	op.open("abc.txt",ios::in|ios::app);
	cout << "Student ID: ";
	cin >> id;
	op << id << "\t";
	cout << "Name: ";
	cin.ignore();
	getline(cin,name);
	op << name << "\t";
	cout << "Age: ";
	cin >> age;
	op << age << endl;
	op.close();
}

void display()
{
	ifstream ip;
	int id,age;
	string name;
	ip.open("abc.txt",ios::out);
	while((ip >> id)&&(ip >> name)&&(ip >> age))
		cout << setw(5) << id << setw(10) << name << setw(15) << age << endl;
	ip.close();
}

void search(int key,int *flag)
{
	int id,age;
	string name;
	ifstream ip;
	ip.open("abc.txt",ios::in);
	while(!ip.eof())
	{
		ip >> id >> name >> age;
		if(id == key)
		{
			*flag = 1;
			break;
		}
	}
	ip.close();
}

void edit(int key)
{
	int id,age,flag = 0,n;
	string name;
	fstream fp;
	fp.open("abc.txt",ios::in|ios::out);
	while(!fp.eof())
	{
		n = fp.tellg();
		fp >> id >> name >> age;
		if(id == key)
		{
			flag = 1;
			break;
		}
	}
	if(flag == 1)
	{
		fp.seekg(n + 1,ios::beg);
		cout << "Student ID: ";
		cin >> id;
		fp << id << "\t";
		cout << "Name: ";
		cin.ignore();
		getline(cin,name);
		fp << name << "\t";
		cout << "Age: ";
		cin >> age;
		fp << age << endl;
		cout << endl << "Record Edited Successfully!" << endl;
	}
	else
		cout << endl << "Record Unavailable." << endl;
	fp.close();
}

void remove(int key)
{
	int id,age,flag = 0;
	string name;
	fstream fp,ft;
	fp.open("abc.txt",ios::in|ios::out);
	ft.open("temp.txt",ios::out);
	while(!fp.eof())
	{
		fp >> id >> name >> age;
		if(id == key)
		{
			flag = 1;
			break;
		}
		else
			ft << id << "\t" << name << "\t" << age << "\t" << endl;
	}
	if(flag == 1)
	{
		while(fp >> id >> name >> age)
			ft << id << "\t" << name << "\t" << age << "\t" << endl;
		cout << endl << "Record Deleted Successfully!" << endl;
	}
	else
		cout << endl << "Record Unavailable." << endl;
	remove("abc.txt");
	rename("temp.txt","abc.txt");
	fp.close();
	ft.close();
}

int main()
{
	int resp,n,key,flag;
	ofstream op;
	Student s;
	do
	{
		cout << "\nSEQUENTIAL FILE OPERATIONS\n\n1. Create Table\n2. Display Table\n3. Add Entry\n4. Delete Entry\n5. Edit Entry\n6. Search Entry\n7. Exit\nYour Choice: ";
		cin >> resp;
		switch(resp)
		{
			case 1: op.open("abc.txt",ios::out|ios::trunc);
				op.close();
				cout << "No. of Records to Create: ";
				cin >> n;
				for(int i = 0;i < n;i++)
				{
					cout << endl << "Entry #" << i + 1 << endl;
					s.input();
				}
				break;
			case 2: cout << setw(5) << "Student ID" << setw(6) << "Name" << setw(15) << "Age" << endl;
				display();
				break;
			case 3: s.input();
				break;
			case 4: cout << "Enter Roll No. to Edit: ";
					cin >> key;
					remove(key);
					break;
			case 5: cout << "Enter Roll No. to Edit: ";
					cin >> key;
					edit(key);
				break;
			case 6: flag = 0;
				cout << "Enter Roll No. to Search: ";
				cin >> key;
				search(key,&flag);
				if(flag == 1)
					cout << endl <<"Record Found!" << endl;
				else
					cout << endl << "Record Unavailable." << endl;
				flag = 0;
				break;
			case 7: return 1;
		}
	}while(resp != 7);
	return 0;
}
