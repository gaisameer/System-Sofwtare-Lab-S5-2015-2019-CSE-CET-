#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<stack>
#include<queue>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<math.h>

using namespace std;

class Loader
{
	private:
		string input_file, output_file;
	public:
		Loader(string, string);
		void print_line(vector<string>);
		void process_line();
		string add_chars(string, char, int, int);
		vector<string> return_line(string);
		string convert_to_hexa(int);
		int convert_to_decimal(string);
};

void Loader :: print_line(vector<string> a)
{
	string l;
	ofstream fout(output_file.c_str(), std::ios_base::app);
	int locctr = convert_to_decimal(a[1]);
	for(int i = 3; i < a.size(); i++)
	{
		l = a[i];
		for(int j = 0; j < l.length(); j += 2)
		{
			cout<<add_chars(convert_to_hexa(locctr), '0', 4, 0)<<" : "<<l[j]<<l[j+1]<<endl;
			fout<<add_chars(convert_to_hexa(locctr), '0', 4, 0)<<" : "<<l[j]<<l[j+1]<<endl;
			locctr++;
		}
	}
	return;
}

void Loader :: process_line()
{
	ifstream fin(input_file.c_str());
	for(string line; getline(fin, line);)
	{
		if(line[0] == 'T')
		{
			print_line(return_line(line));
		}
	}
	fin.close();
}

string Loader :: add_chars(string line, char a, int l, int g)
{
	int p = line.length();
	if(g == 0)
		for(int i = 0; i < l - p; i++)
			line = string(1, a) + line;
	else
		for(int i = 0; i < l - p; i++)
			line += string(1, a);
	return line;
}

vector<string> Loader :: return_line(string a)
{
	string b;
	vector<string> temp;
	for(int i = 0; i < a.length(); i++)
	{
		if(a[i] == '^' && b.length() != 0)
		{
			temp.push_back(b);
			b.clear();
		}
		else if(a[i] != '^')
		{
			b += string(1, a[i]);
		}
	}
	if(b.length() != 0)
	{
		temp.push_back(b);
	}
	return temp;
}

string Loader :: convert_to_hexa(int a)
{
	stringstream ss;
	ss<<hex<<a;
	string hex_value;
	hex_value = ss.str();
	transform(hex_value.begin(), hex_value.end(), hex_value.begin(), ::toupper);
	return hex_value;
}

int Loader :: convert_to_decimal(string a)
{
	stringstream ss;
	ss<<a;
	int decimal_value;
	ss>>hex>>decimal_value;
	return decimal_value;
}

Loader :: Loader(string a, string b)
{
	input_file = a;
	output_file = b;
}

int main ()
{
	int i;
	string input, output;
	while(1)
	{
		cout<<"Enter 1 to load a new file"<<endl;
		cout<<"Enter 2 to exit"<<endl;
		cin>>i;
		cin.ignore();
		switch(i)
		{
			case 1:
			{
				cout<<"Enter the name of the input file"<<endl;
				getline(cin, input);
				cout<<"Enter the name of the output file"<<endl;
				getline(cin, output);
				Loader ld(input, output);
				ld.process_line();
				cout<<"Done loading the object code"<<endl;
				break;
			}
			case 2:
			{
				exit(0);
				break;
			}
			default:
				cout<<"Please enter a valid choice"<<endl;
		}
	}
	return 0;
}