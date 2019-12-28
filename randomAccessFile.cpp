#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
using namespace std;

class base
{
	protected:
	    string name,subject;
	    int rollno;
};

class derived: virtual public base
{
    int scode,intmarks,unimarks;
    public:
	    void create();
	    void display();
	    void search(int,int*);
};

void derived::create()
{
    cin.ignore();
    cout << "Name: ";
    getline(cin,name);
    cout << "Roll Number: ";
    cin >> rollno;
    cin.ignore();
    cout << "Subject: ";
    getline(cin,subject);
    cout << "Subject Code: ";
    cin >> scode;
    cout << "Internal Marks: ";
    cin >> intmarks;
    cout << "University Marks: ";
    cin >> unimarks;
}

void derived::display()
{
    cout << name << setw(10) <<  rollno << setw(10) << subject << setw(10) << scode << setw(16) << intmarks << setw(13) << unimarks << endl;
}

void derived::search(int key,int *c)
{
	if(key == rollno)
		*c = 1;
	else
		*c = 0;
}

int main()
{
    fstream op,tp;
    derived t;
    int resp,i,n,key,flag,flag2;
    do
    {
    	cout << "\nFILE OPERATIONS\n1. Create Master Table\n2. Display Table\n3. Insert New Entry\n4. Delete Entry\n5. Edit an Entry\n6. Search for Record\n7. Exit\nYour Choice: ";
        cin >> resp;
        switch(resp)
        {
            case 1: op.open("abc.bin",ios::out|ios::trunc|ios::binary);
            	    cout << "\nNo. of Records to create: ";
            	    cin >> n;
            	    for(i = 0;i < n;i++)
            	    {
            	    	cout << endl << "Entry #" << i+1 << endl;
            	    	t.create();
            	    	op.write((char*)&t,sizeof(t));
            	    }
            	    op.close();
	            	break;
		    case 2: op.open("abc.bin",ios::in);
					op.seekg(0);
		   	    	cout << "Name" << setw(10) <<  "Roll No." << setw(10) << "Subject" << setw(13) << "Sub. Code" << setw(15) << "Int. Marks" << setw(15) << "Uni. Marks" << endl << endl;
	    	    	while(op.read((char*)&t,sizeof(t)))
						t.display();
	        	    op.close();
		    	    break;
		    case 3: cout << endl;
		    	    op.open("abc.bin",ios::out|ios::app|ios::binary);
					t.create();
					op.write((char*)&t,sizeof(t));
		    	    op.close();
		    	    break;
		    case 4: cout << "Enter Roll No. to Delete: ";
			    cin >> key;
			    op.open("abc.bin",ios::in|ios::out|ios::binary);
			    tp.open("temp.bin",ios::in|ios::out|ios::trunc|ios::binary);
			    op.seekg(0);
    			    flag2 = 0;
			    while(op.read((char*)&t,sizeof(t)))
		 	    {
				t.search(key,&flag);
				if(flag != 1)
					tp.write((char*)&t,sizeof(t));
				else
					flag2 = 1;
			    }
			    if(flag2 == 1)
				cout << endl << "Record Deleted Successfully!" << endl;
			    else
				cout << endl << "Record Unavailable. Cannot Delete." << endl;
			    remove("abc.bin");
			    rename("temp.bin","abc.bin");
			    tp.close();
			    op.close();
		    	    break;
		    case 5: cout << "Enter Roll No. to Edit: ";
					cin >> key;
					op.open("abc.bin",ios::in|ios::out|ios::binary);
					op.seekg(0);
					while(!op.eof())
					{
						op.read((char*)&t,sizeof(t));
						t.search(key,&flag);
						if(flag == 1)
							break;
					}
					if(flag == 1)
					{
						int m = sizeof(t);
						op.seekg(-m,ios::cur);
						cout << endl << "Record Found!\nEnter Edited Data:\n";
						t.create();
						op.write((char*)&t,sizeof(t));
					}
					else
						cout << endl << "Record Not Present." << endl;
					op.close();
		    	    break;
		    case 6: cout << "Enter Roll No. to Search: ";
					cin >> key;
					op.open("abc.bin",ios::in);
					while(!op.eof())
					{
						op.read((char*)&t,sizeof(t));
						t.search(key,&flag);
						if(flag == 1)
							break;
					}
					if(flag == 1)
						cout << endl << "Record Found!" << endl;
					else
						cout << endl << "Record Not Present." << endl;
					op.close();
		    	    break;
		    case 7: return 1;
			default: cout << endl << "Please enter a valid response." << endl;
	    }
     }while(resp != 7);
     return 0;
}
