//============================================================================
// Name        : hw4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string.h>
using namespace std;

/*
 * Text file format:
 * cid,
 * pid,
 * fname,
 * lname,
 * email,
 * contacted (int used as bool),
 * # of symptoms,
 * list of symptoms,
 * parallel list of confirmed (int used as bool),
 * parallel list of severity (int 1-5)
 * string of diagnosis date (to be converted to date at some point)
 * diagnosis - (0 - !covid, 1 - covid)
 * diagnosing doctor's id
 * # of original cases
 * list of original case ids
 * # of associated cases
 * list of associated case ids
 * case status (is closed: 0 - open, 1 closed)
 */

/*
 * =====================================================================================================================================================================
 * Questions:
 * 	- How are we implementing a menu system here?
 * 	- Are we able to use getline(cin, var) to read input or should we use while(!sentinel) {cin >> var;} instead?
 * To do:
 * 	- Finish adding methods to date from your laptop. Just manually add them, there's only a few short methods
 * 	-
 * Notes:
 * 	- What to code first:
 * 		- Finish adding the accessers/mutators first. Those are easy and will really shape what to do next on their own
 * 		- Create a method to read in data from the text files. Just make one method that returns a vector of strings?
 * =====================================================================================================================================================================
 */

class Date
{
private:
	int _m, _d, _y;
	// Notice, these are private functions!!
	void convert(string s){
		char x[5]; // atoi stands for ascii to integer
		// like stoi, string to integer
		x[0] = s[0];   x[1] = s[1];  x[2] = '\0';
		_m = atoi(x);
		x[0] = s[3];   x[1] = s[4];  x[2] = '\0';
		_d = atoi(x);
		x[0] = s[6];   x[1] = s[7];  x[2] = s[8];
		x[3] = s[9];   x[4] = '\0';
		_y = atoi(x);
	}
	string convert2()
	{
		string tm = "", td = "", ty = "";
		/*char t[10];*/
		if (_m <= 9)
			tm = tm + "0" + to_string(_m);
		else
			tm = to_string(_m);
		if (_d <= 9)
			td = td + "0" + to_string(_d);
		else
			td = to_string(_d);
		ty = to_string(_y);
		return tm + "/" + td + "/" + ty;
	}
	char* convert3()
	{
		string t = convert2();
		char* c = new char[t.length()+1];
		strcpy(c, t.c_str());
		return c;
	}
public:
	Date():_m(1), _d(1), _y(2020){cout << "in default constructor" << endl;}
	Date(int m, int d, int y){
		cout << "in 3-arg constructor" << endl;
		_m = m;
		_d = d;
		_y = y;
	}
	Date(string s)
	{
		cout << "in string type conversion function" << endl;
		convert(s);
	}
	const Date& operator++()
	{
		cout << "in prefix operator++" << endl;
		_d++;
		return *this;
	}
	const Date operator++(int)
	{
		cout << "in postfix operator++" << endl;
		Date t = *this;
		_d++;
		return t;
	}
	int operator[](int x)
	{
		// pre: parameter must be a 0, 1, or 2
		// post: corresponding day, month, or year returned, -1 returned if error
		cout << "In operator []" << endl;
		if(x == 0) {return _d;}
		else if(x == 1) {return _m;}
		else if(x == 2) {return _y;}
		else {return -1;}
	}
	int operator()(int x)
	{
		// should just make another PRIVATE method for this and [] to call
		// instead of just repeating code
		cout << "In operator() : index" << endl;
		if(x == 0) {return _d;}
		else if(x == 1) {return _m;}
		else if(x == 2) {return _y;}
		else {return -1;}
	}
	void operator()(string s)
	{
		//pre: string passed in with month, date, and year
		cout << "In operator()" << endl;
		convert(s);
	}
	Date operator+(int a)
	{
		cout << "in operator+(int)" << endl;
		Date t = *this;
		t._d = t._d + a;
		return t;
	}
	operator string()
	{
		// something
		cout << "in string type conversion operator" << endl;
		return convert2();
	}
	operator char*()
	{
		cout << "in c-string type conversion operator" << endl;
		return convert3();
	}
	int getM()const {return _m;}
	int getD()const {return _d;}
	int getY()const {return _y;}
	void setD(int x) {_d = x;}
	void setM(int x) {_m = x;}
	void setY(int x) {_y = x;}
	void print()
	{
		cout << _m << " " << _d << " " << _y << endl;
	}
};
class Person
{
private:
	int _pid;
	string _fname;
	string _lname;
	string _email;
public:
	Person();
	Person(int p, string fn, string ln, string em);
	void setPid(int p) {_pid = p;}
	void setFname(string fn) {_fname = fn;}
	void setLname(string ln) {_lname = ln;}
	void setEmail(string em) {_email = em;}
	int getPid() {return _pid;}
	const string getFname() {return _fname;}
	const string getLname() {return _lname;}
	const string getEmail() {return _email;}
};
class Case
{
private:
	int _pid, _cid;
	Date _diagDate;
	int _diagnosis;
	int _whoConf;
	int _contacted;
	vector<string> _symptoms; // <- {fatigue, cough, sore throat}
	vector<int> _confirmed; // <- {1, 0, 0}
	vector<int> _severity; // <- {2, 2, 4}
	vector<int> _original;
	vector<int> _associated;
	int _caseStatus;
public:
	// need set/get cid, pid, diag, whoconf, casestatus
	Case(){}
	Case(int cid, int pid, Date date, int diag, int whoconf, int contacted)
	{
		_cid = cid;
		_pid = pid;
		_diagDate = date;
		_diagnosis = diag;
		_whoConf = whoconf;
		_contacted = contacted;
		_caseStatus = 0;
	}
	void setContacted(int contacted) {_contacted = contacted;}
	void setCid(int cid) {_cid = cid;}
	void setPid(int pid) {_pid = pid;}
	void setDiag(int diagnosis) {_diagnosis = diagnosis;}
	void setWhoConfirmed(int docId) {_whoConf = docId;}
	void setCaseStatus(int caseStatus) {_caseStatus = caseStatus;}
	int getContacted() {return _contacted;}
	int getCid() {return _cid;}
	int getPid() {return _pid;}
	int getDiag() {return _diagnosis;}
	int getWhoConfirmed() {return _whoConf;}
	int getCaseStatus() {return _caseStatus;}
	/*
	 * pre: parameter must be 0 to length-1 of vector of symptoms
	 * post: symptom returned or empty string if parameter out of bounds
	 */
	string getSymptom(int index) {return _symptoms[index];} // location is index in vector
	int symptomCount() {return _symptoms.size();}
	void addSymptom(string s) {_symptoms.push_back(s);} // actual symptom val
	void removeSymptom(string s) // actual symptom value
	{
		std::vector<string>::iterator vitr = _symptoms.begin();
		while(vitr != _symptoms.end() && *vitr != s) {vitr++;}
		if(*vitr == s) {_symptoms.erase(vitr);}
	}
	int getConfirmed(int index) {return _confirmed[index];}
	int confirmedCount() {return _confirmed.size();}
	void addConfirmed(int confirm) {_confirmed.push_back(confirm);}
	void modifyConfirmed(int index) {_confirmed[index] = !(_confirmed[index]);}
	/*
	 * pre: parameter is the index in vector to remove
	 * post:
	 */
	void removeConfirmed(int index) // x is the location of value to remove in vector
	{
		if(index < 0 || index > _confirmed.size()-1) {return;}
		std::vector<int>::iterator vit = _confirmed.begin() + index;
		_confirmed.erase(vit);
	}
	void addSeverity(int severity) {_severity.push_back(severity);}
	void modifiySeverity(int index, int severity) {_severity[index] = severity;}
	void removeSeverity(int index)
	{
		if(index < 0 || index > _severity.size()) {return;}
		std::vector<int>::iterator vit = _severity.begin()+index;
		_severity.erase(vit);
	}
};
class AllPersons
{
private:
	vector<Person*> _persons; // or vector<*Person>
public:
	AllPersons() {}
	~AllPersons()
	{
		int size = _persons.size();
		for(int i = 0; i < size; i++)
		{
			delete(_persons[i]);
		}
	}
	void setPid(int i, int pid) {_persons[i]->setPid(pid);}
	void setFname(int pid, string fname)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if((*vit)->getPid() == pid) {(*vit)->setFname(fname);}
	}
	void setLname(int pid, string lname)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if((*vit)->getPid() == pid) {(*vit)->setLname(lname);}
	}
	void setEmail(int pid, string email)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if((*vit)->getPid() == pid) {(*vit)->setEmail(email);}
	}
	const int getPid(int i) {return _persons[i]->getPid();}
	const string getFname(int pid)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if((*vit)->getPid() == pid) {return (*vit)->getFname();}
		return "";
	}
	const string getLname(int pid)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if((*vit)->getPid() == pid) {return (*vit)->getLname();}
		return "";
	}
	const string getEmail(int pid)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if((*vit)->getPid() == pid) {return (*vit)->getEmail();}
		return "";
	}
	void addPerson(int pid, string fname, string lname, string email)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if(vit != _persons.end()) {_persons.push_back(new Person(pid, fname, lname, email));}
	}
	void removePerson(int pid)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if((*vit)->getPid() == pid) {_persons.erase(vit);}
	}
	void modifyPersonEmail(int pid, string email)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if(vit != _persons.end()) {(*vit)->setEmail(email);}
	}
	void modifyPersonFname(int pid, string fname)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if(vit != _persons.end()) {(*vit)->setFname(fname);}
	}
	void modifyPersonLname(int pid, string lname)
	{
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if(vit != _persons.end()) {(*vit)->setLname(lname);}
	}
};

class AllCases
{
private:
	vector<Case*> _cases;
public:
	AllCases() {}
	~AllCases()
	{
		int size = _cases.size();
		for(int i = 0; i < size; i++)
		{
			delete(_cases[i]);
		}
	}
	// can make a case here and modify everything else
	void addCase(int cid, int pid, string fname, string lname, string email)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if(vit != _cases.end()) {_cases.push_back(new Case());}
	}
	void addToCaseContacted(int cid, int contacted)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if(vit != _cases.end()) {(*vit)->setContacted(contacted);}
	}
	void addDiagnosisInfo(int cid, int diagnosis, int whoDiagnosed)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if(vit != _cases.end()) {(*vit)->setWhoConfirmed(whoDiagnosed); (*vit)->setDiag(diagnosis);}
	}
	void addToCaseSymptom(int cid, string symptom, int confirmed, int severity)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if(vit != _cases.end()) {(*vit)->addSymptom(symptom); (*vit)->addConfirmed(confirmed); (*vit)->addSeverity(severity);}
	}
	/*
	 * More methods to write
	 * think about EVERYTHING you'll need to modify or even MIGHT need to modify
	 */
	// !!! FOR TESTING, DELETE ME !!!
	void testPrint()
	{
		for(int i = 0; i < _cases.size(); i++)
		{
			int cid = _cases[i]->getCid(), pid = _cases[i]->getPid(), contacted = _cases[i]->getContacted();
		}
	}
};
class AllSymptoms
{
private:
	vector<string> _symptoms;
public:
	AllSymptoms() {}
	AllSymptoms(vector<string> symptoms) {_symptoms = symptoms;}
	void setSymptoms(vector<string> symptoms) {_symptoms = symptoms;}
	void addPossibleSymptom(string symptom) {_symptoms.push_back(symptom);}
	string getSymptom(int index) {return _symptoms[index];}
};
Date operator+(int x, const Date& b)
{
	cout << "in operator+ (int, date)" << endl;
	Date t = b;
	t.setD(b.getD() + x);
	return t;
}
Date operator+(const Date& a, const Date& b)
{
	cout << "in operator+ (date, date)" << endl;
	Date t = a;
	t.setD(a.getD() + b.getD());
	return t;
}
ostream& operator<<(ostream& out, const Date& b)
{
	out << "In operator <<" << endl;
	out << b.getM() << " " << b.getD() << " " << b.getY() << endl;
	//
	return out;
}
vector<string> readFile(istream& infile)
{
	vector<string> lines;
	string line;
	getline(infile, line);
	cout << "line: " << line << endl;
	while(!infile.eof())
	{
		//cout << "Debug" << endl << "line: " << line << endl;
		lines.push_back(line);
		getline(infile, line);
	}
	return lines;
}
vector<string> splitLine(string line)
{
	vector<string> splitLines;
	int count = 0, length = line.length();
	stringstream ss;
	while(count < length)
	{
		char c = line[count];
		if(c != ',') {ss << c;}
		else
		{
			string t;
			ss >> t;
			splitLines.push_back(t);
		}
		count++;
	}
	return splitLines;
}
void createCases(AllCases& cases, vector<string> data)
{
	int length = data.size();
	for(int i = 0; i < length; i++)
	{
		//
	}
}
int main()
{
	AllPersons persons;
	AllCases cases;
	AllSymptoms symptoms;
	//this is for the final version where the user chooses their file name
	//DO NOT FORGET TO UNCOMMENT THIS
	/*string casefn, symptomfn;
	cout << "Enter case file name: ";
	getline(cin, casefn);
	cout << endl << "Enter symptom file name: ";
	getline(cin, symptomfn);
	cout << endl;*/
	string casefn = "cases.txt", symptomfn = "symptoms.txt"; // !!! DELETE ME, FOR TESTING !!!
	ifstream infile(casefn);
	cout << endl;
	vector<string> caseInfo = readFile(infile);
	infile.close(); infile.open(symptomfn);
	vector<string> symptomList = readFile(infile);
	infile.close();
	symptoms.setSymptoms(symptomList);
	/*int caseCnt = caseInfo.size(), symptomCount = symptomList.size();
	cout << "Case info vector test" << endl;
	for(int i = 0; i < caseCnt; i++) {cout << caseInfo[i] << endl;}
	cout << "Symptom list vector test" << endl;
	for(int i = 0; i < symptomCount; i++) {cout << symptomList[i] << endl;}*/ //!!! DELETE ME, THIS IS FOR TESTING !!!
	cout << "compiled" << endl;
	return 0;
}
