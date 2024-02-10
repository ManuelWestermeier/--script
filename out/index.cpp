#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <random>

using namespace std;

void writeFile(string fileName, string data)
{
	ofstream MyFile(fileName);
	MyFile << data;
	MyFile.close();
}

string readFile(string fileName)
{
	ifstream f(fileName);
	string str;
	if (f)
	{
		ostringstream ss;
		ss << f.rdbuf();
		str = ss.str();
	}
	return str;
}

string log(string out)
{
	cout << out << endl;
	return out;
}

string print(string out)
{
	cout << out << endl;
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

string securifyHTML(string html)
{
	return replace(html, '<', "< ");
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

string sf(int d)
{
	return to_string(d);
}

// start
//int x = 100;
/*int x = 100;*/

/*
vector<int> x;
*/
/*@array x : int*/
//@array x : int

int requestIndex = 0;
string lastPost = "Hello World";

string returnSomeString () {
    return "\nSome String\n\n";
}

void doSomethingx(int i) {
    print("Hallo Welt " + sf(i));
    print(returnSomeString());
}

int main(int argc, char *argv[]) {
    //get the arguments
System::String * target= "http://www.microsoft.com";
System::String * target = "ftp://ftp.microsoft.com";
System::String * target = "C:\\Program Files\\Microsoft Visual Studio\\INSTALL.HTM";

System::Diagnostics::Process::Start(target);

for (int i = 0; i < argc; ++i) {
    print(argv[i]);
}
    //call a function
    doSomethingx(10);
    //---arrays---
    //test array create
//name : string
vector<string> text;
    //split a string
//split string
//split(string, splitter);
text = split("Hello World it's the first programm written in @-script?", " ");
    //loop foreach
//loop for items in array
//itemname : array-name
for (auto &word : text) {
    print(word + ",");
}
    //join array
//join array
print("\n");
//join(array:array-string, splitter:string);
print(join(text,"|"));
print("\n");
    //destruct array
//destruct 2 first items in array
//array-name # array type : variable names splitted with a space
string first = text.at(0);
string secound = text.at(1);

//print them
print("\ndestruct : " + first + " and " + secound + "\n");
    //loop
for (int index = 0; index < 10; index++) {
    //sf = stringify
	print("int " + sf(index) +"\n");
}

for (int i = 0; i < 5; i++) {
    //sf = stringify
	print("int " + sf(i) +"\n");
}
    //---maps---
    //create
//variable name : keytype and datatype
map<string, string> global;
    //get set and delete
//set
global["xyz"] = "\nHallo Welt from Map\n";
//get
print(global["xyz"]);
//delete
global.erase("xyz");
    //---filesystem---
vector<string> x;

for (int index = 0; index < 10; index++) {
    x.push_back("Hallo Welt");
}

writeFile("x.txt", join(x,"\n"));

string data = readFile("x.txt");

vector<string> y;

y = split(data, "\n");

for (auto &str : y) {
    print(str  + "\n");
}
    //---string tamplate----
//define the in the string requested variables
string header = "Hello";
string textBody = "Hello World 1234252677 <h1>x</h1>";
string HTML = "<b>Hallo Welt</b>";

//variable-name from file-name
string   txt;
txt += "<!DOCTYPE html>\n<html lang=\"en\">\n\n<head>\n    <meta charset=\"UTF-8\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <!--securifyHTML is a function that\n        convert text in no HTML-->\n    <title>";
txt += securifyHTML(header);
txt += "</title>\n</head>\n\n<body onload=\"alert('Hallo')\">\n    <h1>\n        <!--\n            use the hashtag variable-name hashtag\n            to add a variable             \n        -->\n        ";
txt += securifyHTML(header);
txt += "\n    </h1>\n    <p>\n        ";
txt += securifyHTML(textBody);
txt += "\n    </p>\n    ";
txt += HTML;
txt += "\n</body>\n\n</html>";


//output the string
writeFile("in.html", txt);
system("start in.html");
print(txt);
    //---create-http-server---
using namespace httplib;
//https://github.com/yhirose/cpp-httplib

//create the server
Server svr;
//on get the root
svr.Get("/", [](const Request& req, Response& res) {
    requestIndex++;
string   homePage;
homePage += "<!DOCTYPE html>\n<html lang=\"en\">\n\n<head>\n    <meta charset=\"UTF-8\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <title>Hello World</title>\n    <style>\n        * {\n            margin: 5px;\n            padding: 5px;\n            font-family: system-ui, -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;\n            border-radius: 3px;\n        }\n    </style>\n</head>\n\n<body>\n    <div>\n        <h1>Hello World</h1>\n        <a href=\"/\">Reload</a>\n        <p>\n            Request Index : ";
homePage += sf(requestIndex);
homePage += "\n        </p>\n        <hr>\n        <p>\n            ";
homePage += securifyHTML(lastPost);
homePage += "\n        </p>\n        <hr>\n    </div>\n    <form>\n        <input type=\"text\" placeholder=\"content...\">\n        <br>\n        <button>Post</button>\n    </form>\n    <script>\n        document.querySelector(\"form\").addEventListener(\"submit\", async e => {\n            e.preventDefault();\n            await fetch(document.location, {\n                method: \"POST\",\n                body: document.querySelector(\"input\").value\n            })\n            location.reload()\n        })\n    </script>\n</body>\n\n</html>";

    res.set_content(homePage, "text/html");
});
//on post
svr.Post("/", [](const Request& req, Response& res) {
    lastPost = req.body;
    res.set_content("<script>location = \"\"</script>", "text/html");
});
//404
svr.set_error_handler([](const auto& req, auto& res) {
  auto fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
  char buf[BUFSIZ];
  snprintf(buf, sizeof(buf), fmt, res.status);
  res.set_content(buf, "text/html");
});
//listen
svr.listen("localhost", 80);
//open
system("start http://localhost");
    //pause the system
    system("pause");
}

//---class---
class testClass {
private:
        int count = 0;
public:
void l() {
            log("count : " + sf(count));
        }
void add(int i) {
            count += i;
        }
};

//Hallo welt