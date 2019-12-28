#include<iostream>
using namespace std;

template<class T>
class Matrix
{
	T A[10][10],B[10][10],C[10][10];
	public:
		void input(int,int,int);
		void display(int,int);
		void add(int,int);
		void multiply(int,int,int);	
};

template<class T>
void Matrix<T>::input(int r,int c,int dummy)
{
	int i,j;
	if(dummy == 1)
	{
		for(i = 0;i < r;i++)
		{
			cout << "Row #" << i+1 << endl;
			for(j = 0;j < c;j++)
				cin >> A[i][j];
		}
	}
	else
	{
		for(i = 0;i < r;i++)
		{
			cout << "Row #" << i+1 << endl;
			for(j = 0;j < c;j++)
				cin >> B[i][j];
		}
	}
}

template<class T>
void Matrix<T>::display(int r,int c)
{
	int i,j;
	cout << endl << "Resultant Matrix: \n";
	for(i = 0;i < r;i++)
	{
		cout << "|";
		for(j = 0;j < c;j++)
			cout << "\t" << C[i][j] << "\t";
		cout << "|" << endl;
	}
}

template<class T>
void Matrix<T>::add(int r,int c)
{
	int i,j;
	for(i = 0;i < r;i++)
	{
		for(j = 0;j < c;j++)
			C[i][j] = A[i][j] + B[i][j];
	}
	display(r,c);	
}

template<class T>
void Matrix<T>::multiply(int r,int c, int d)
{
	int i,j,k,temp;
	for(i = 0;i < r;i++)
	{
		for(k = 0;k < c;k++)
		{
			temp = 0;
			for(j = 0;j < d;j++)
			{
				temp += A[i][j] * B[j][k];
			}
			C[i][k] = temp;
		}
	}
	display(r,c);
}	

int main()
{
	int resp,r1,c1,r2,c2,resp2;
	Matrix <int> X;
	Matrix <float> Y;
	do
	{
		cout << "\nTEMPLATES\n\n1. Add Two Matrices\n2. Multiply Two Matrices\n3. Exit\nYour Choice: ";
		cin >> resp;
		switch(resp)
		{
			case 1: cout << "Matrix 1:\n";
				cout << "No. of Rows: ";
				cin >> r1;
				cout << "No. of Columns: ";
				cin >> c1;
			x:	cout << "Type of Matrix: 1 for int / 2 for float: ";
				cin >> resp2;
				if(resp2 == 1)
					X.input(r1,c1,1);
				else if(resp2 == 2)
					Y.input(r1,c1,1);
				else
				{
					cout << "Enter a valid response.";
					goto x;
				}
				cout << "Matrix 2:\n";
				cout << "No. of Rows: ";
				cin >> r2;
				cout << "No. of Columns: ";
				cin >> c2;
				if(resp2 == 1)
					X.input(r2,c2,2);
				else
					Y.input(r2,c2,2);
				if((r1 == r2)&&(c1 == c2))
				{
					if(resp2 == 1)
						X.add(r1,c1);
					else
						Y.add(r1,c1);
				}
				else
					cout << "\nAddition not possible.\n";
				break;
			case 2: cout << "Matrix 1:\n";
				cout << "No. of Rows: ";
				cin >> r1;
				cout << "No. of Columns: ";
				cin >> c1;
			z:	cout << "Type of Matrix: 1 for int / 2 for float: ";
				cin >> resp2;
				if(resp2 == 1)
					X.input(r1,c1,1);
				else if(resp2 == 2)
					Y.input(r1,c1,1);
				else
				{
					cout << "Enter a valid response.";
					goto z;
				}
				cout << "Matrix 2:\n";
				cout << "No. of Rows: ";
				cin >> r2;
				cout << "No. of Columns: ";
				cin >> c2;
				if(resp2 == 1)
					X.input(r2,c2,2);
				else
					Y.input(r2,c2,2);
				if(c1 == r2)
				{
					if(resp2 == 1)
						X.multiply(r1,c2,r2);
					else
						Y.multiply(r1,c2,r2);
				}
				else
					cout << "\nMultiplication not possible.\n";
				break;
			case 3: return 1;
			default: cout <<"\nPlease enter a valid response.\n";	
		}
	}while(resp != 3);
	return 0;
}
