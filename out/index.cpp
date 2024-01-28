#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void writeFile(string fileName, string data)
{
	ofstream MyFile(fileName);
	MyFile << data;
	MyFile.close();
}

string readFile(string fileName)
{
	ifstream file;
	string data;
	file.open(fileName.c_str());
	while (!file.eof())
	{
		string chunk;
		file >> chunk;
		data += chunk;
	}
	file.close();
	return data;
}

string print(string out)
{
	cout << out;
	return out;
}

string readLine(string header)
{
	cout << "\n"
		 << header;
	string line;
	getline(cin, line);
	return line;
}

string replace(string original, char find, string replacer)
{

	string new_str;

	for (int i = 0; i < original.length(); i++)
	{
		if (original.at(i) == find)
			new_str += replacer;
		else
			new_str += original[i];
	}

	return new_str;
}

string join(vector<string> &_array, string split)
{
	string out;

	for (string &_item : _array)
	{
		out += _item + split;
	}

	for (int i = 0; i < split.length(); i++)
		out.pop_back();

	return out;
}

vector<string> split(string s, string delimiter)
{
	vector<string> out;
	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != string::npos)
	{
		token = s.substr(0, pos);
		out.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	out.push_back(s);
	return out;
}

int str2int(const string &str)
{
	stringstream ss(str);
	int num;
	if ((ss >> num).fail())
	{
		return 0;
	}
	return num;
}
void ArrayTest()
{

	vector<string> arr;
	print("\n");

	for (int i = 0; i < 5; i++)
	{

		arr.push_back("Hello World " + to_string(i + 4));
	}

	for (auto &it : arr)
	{

		it.append("\n");
	}

	print(join(arr, ""));

	print("\n");

	vector<string> words = split("@-script is cool", " ");
	for (auto &it : words)
	{
		print(it + "\t");
	}

	print("\n");
}
#define HelloWorl "Hello World 2\n"

string hw()
{
	system("title test");
	return "Hello World 1\n";
}

void start(int startNum)
{

	print(hw());
	print(HelloWorl);
	ArrayTest();
}

int main()
{
	start(10);
	system("pause");
	return 0;
}