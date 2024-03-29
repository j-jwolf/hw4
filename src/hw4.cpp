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
 * 	- You aren't reading the data in correctly. You need to check if is contacted:
 * 	  -- if yes, there is a date and doctor id
 * 	  -- else, no date or doctor id
 * 	  -- !!! NEED TO FIX THIS, DOCID THEN DIAGNOSIS !!!
 * Notes:
 * 	- What to code first:
 * 		- Finish adding the accessers/mutators first. Those are easy and will really shape what to do next on their own
 * 		- Create a method to read in data from the text files. Just make one method that returns a vector of strings?
 * 	- Never pass a vector in/out
 * 	Methods to be deleted before turning in (per class):
 * 	-AllCases:
 * 		-testPrint()
 * 		-testPrint(int)
 * 		-showAssociatedCases(int)
 * 	-AllPersons:
 * 		-testPrint()
 * 	-Case:
 * 		-testPrint()
 * 	-Person:
 * 		-testPrint()
 * =====================================================================================================================================================================
 */

class Date
{
private:
	int _m, _d, _y;
	// Notice, these are private functions!!
	void adjustDate()
	{
		int c1[] = {1, 3, 5, 7, 8, 10, 12}, c2[] = {4, 6, 9, 11};
		int count = 0, length = 7, val = -1;
		while(count < length && val == -1)
		{
			if(_m == c1[count])
			{
				val = c1[count];
				_d++;
				if(_d > 31)
				{
					_m++;
					_d = 1;
					if(_m > 12) {_m = 1; _y++;}
				}
			}
			else if(count < 4 && _m == c2[count])
			{
				val = c2[count];
				_d++;
				if(_d > 30) {_m++; _d = 1;}
			}
			count++;
		}
		if(val == -1)
		{
			val = 2;
			_d++;
			if((_d > 28 && _y%4 == 0) || (_d > 27 && _y%4 != 0)) {_m++; _d = 1;}
		}
	}
	void convert(string s)
	{
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
		cout << "Date n-arg constructor" << endl;
		cout << "string arg: " << s << endl;
		convert(s);
		cout << "date: " << getDate() << endl;
	}
	string getDate() {return convert2();}
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
	Person(int p, string fn, string ln, string em)
	{
		_pid = p;
		_fname = fn;
		_lname = ln;
		_email = em;
	}
	void setPid(int p) {_pid = p;}
	void setFname(string fn) {_fname = fn;}
	void setLname(string ln) {_lname = ln;}
	void setEmail(string em) {_email = em;}
	int getPid() {return _pid;}
	const string getFname() {return _fname;}
	const string getLname() {return _lname;}
	const string getEmail() {return _email;}
	void testPrint()
	{
		cout << "=================================================" << endl;
		cout << "PID: " << _pid << endl;
		cout << "First name: " << _fname << ", Last name: " << _lname << endl;
		cout << "Email: " << _email << endl;
	}
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
	Case(int cid, int pid, string date, int diag, int whoconf, int contacted)
	{
		_cid = cid;
		_pid = pid;
		if(date != "") {Date d(date); _diagDate = d;}
		_diagnosis = diag;
		_whoConf = whoconf;
		_contacted = contacted;
		_caseStatus = 0;
	}
	Case(int cid, int pid, int diag, int whoconf, int contacted, int status)
	{
		_cid = cid;
		_pid = pid;
		_diagnosis = diag;
		_whoConf = whoconf;
		_contacted = contacted;
		_caseStatus = status;
	}
	Case(int cid, int pid)
	{
		_cid = cid;
		_pid = pid;
		_contacted = 0;
		_whoConf = -1;
		_diagnosis = -1;
		_caseStatus = 0;
	}
	void closeCase() {_caseStatus = !_caseStatus;}
	void setContacted(int contacted) {_contacted = contacted;}
	void setCid(int cid) {_cid = cid;}
	void setPid(int pid) {_pid = pid;}
	void setDiag(int diagnosis) {_diagnosis = diagnosis;}
	void setWhoConfirmed(int docId) {_whoConf = docId;}
	void setCaseStatus(int caseStatus) {_caseStatus = caseStatus;}
	void setDiagDate(string date) {Date d(date); _diagDate = d;}
	int getContacted() {return _contacted;}
	int getCid() {return _cid;}
	int getPid() {return _pid;}
	int getDiag() {return _diagnosis;}
	int getWhoConfirmed() {return _whoConf;}
	int getCaseStatus() {return _caseStatus;}
	string getDiagDate() {return _diagDate.getDate();}
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
	int getSeverity(int index) {return _severity[index];}
	int getOrigCid(int index) {return _original[index];}
	void addOrigCid(int cid) {_original.push_back(cid);}
	void removeOrigCid(int index)
	{
		if(index < 0 || index > _original.size()) {return;}
		std::vector<int>::iterator vit = _original.begin()+index;
		_severity.erase(vit);
	}
	int getAssociatedCid(int index) {return _associated[index];}
	void addAssociatedCid(int cid) {_associated.push_back(cid);}
	void removeAssociatedCid(int index)
	{
		if(index < 0 || index > _associated.size()) {return;}
		std::vector<int>::iterator vit = _associated.begin()+index;
		_associated.erase(vit);
	}
	int originalCount() {return _original.size();}
	int associatedCount() {return _associated.size();}
	void testPrint()
	{
		cout << "=================================================" << endl;
		cout << "Case ID: " << _cid << endl;
		cout << "Person ID: " << _pid << endl;
		cout << "Diagnosis: ";
		if(_diagnosis == 1) {cout << "Positive";}
		else if(_diagnosis == 0) {cout << "Negative";}
		else {cout << "No diagnosis information";}
		cout << endl << "Doctor ID: ";
		if(_whoConf != -1) {cout << _whoConf << endl;}
		else {cout << "no doctor confirmation" << endl;}
		cout << "Contacted?: ";
		if(_contacted) {cout << "Yes";}
		else {cout << "No";}
		cout << endl << "Patient symptoms" << endl;
		int length = _symptoms.size();
		for(int i = 0; i < length; i++)
		{
			cout << "Symptom: " << _symptoms[i] << ", is confirmed?: ";
			if(_confirmed[i]) {cout << "Yes";}
			else {cout << "No";}
			cout << ", severity: " << _severity[i] << endl;
		}
		int oLen = _original.size(), aLen = _associated.size();
		if(oLen > 0)
		{
			cout << "Original case IDs: " << _original[0];
			for(int i = 1; i < oLen; i++) {cout << ", " << _original[i];}
			cout << endl;
		}
		if(aLen > 0)
		{
			cout << "Associated case IDs: " << _associated[0];
			for(int i = 1; i < aLen; i++) {cout << ", " << _associated[i];}
			cout << endl;
		}
		cout << "Is case closed?: ";
		if(_caseStatus) {cout << "Yes";}
		else {cout << "No";}
		cout << endl;
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
		if(_persons.size() == 0)
		{
			_persons.push_back(new Person(pid, fname, lname, email));
		}
		else
		{
			std::vector<Person*>::iterator vit = _persons.begin();
			while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
			if(vit == _persons.end()) {_persons.push_back(new Person(pid, fname, lname, email));}
		}
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
	void testPrint()
	{
		int length = _persons.size();
		cout << "person cnt: " << length << endl;
		cout << "=================================================" << endl;
		for(int i = 0; i < length; i++)
		{
			_persons[i]->testPrint();
		}
	}
};

class AllCases
{
private:
	vector<Case*> _cases;
	Case* getCaseByCid(int cid)
	{
		Case* caseptr = nullptr;
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if((*vit)->getCid() == cid) {caseptr = (*vit);}
		return caseptr;
	}
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
	int getCaseCount() {return _cases.size();}
	int getCid(int index) {return _cases[index]->getCid();}
	void addCase(int cid, int pid, string date, int diag, int whoconf, int contacted)
	{
		if(_cases.size() == 0)
		{
			_cases.push_back(new Case(cid, pid, date, diag, whoconf, contacted));
		}
		else
		{
			std::vector<Case*>::iterator vit = _cases.begin();
			while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
			if(vit == _cases.end()) {_cases.push_back(new Case(cid, pid, date, diag, whoconf, contacted));}
		}
	}
	void addCase(int cid, int pid, int diag, int whoconf, int contacted, int status)
	{
		if(_cases.size() == 0)
		{
			_cases.push_back(new Case(cid, pid, diag, whoconf, contacted, status));
		}
		else
		{
			std::vector<Case*>::iterator vit = _cases.begin();
			while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
			if(vit == _cases.end()) {_cases.push_back(new Case(cid, pid, diag, whoconf, contacted, status));}
		}
	}
	void addCase(int cid, int pid)
	{
		if(_cases.size() == 0)
		{
			_cases.push_back(new Case(cid, pid));
		}
		else
		{
			std::vector<Case*>::iterator vit = _cases.begin();
			while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
			if(vit == _cases.end()) {_cases.push_back(new Case(cid, pid));}
		}
	}
	void addToCaseContacted(int cid, int contacted)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if(vit != _cases.end()) {(*vit)->setContacted(contacted);}
	}
	void addDiagnosisInfo(int cid, int diagnosis, int whoDiagnosed, string date)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if(vit != _cases.end())
		{
			(*vit)->setWhoConfirmed(whoDiagnosed);
			(*vit)->setDiag(diagnosis);
			(*vit)->setDiagDate(date);
		}
	}
	void addToCaseSymptom(int cid, string symptom, int confirmed, int severity)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if(vit != _cases.end()) {(*vit)->addSymptom(symptom); (*vit)->addConfirmed(confirmed); (*vit)->addSeverity(severity);}
	}
	void setCaseStatus(int cid, int status)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && cid != (*vit)->getCaseStatus()) {vit++;}
		if(vit != _cases.end()) {(*vit)->setCaseStatus(status);}
	}
	/*
	 * More methods to write
	 * think about EVERYTHING you'll need to modify or even MIGHT need to modify
	 */
	// !!! FOR TESTING, DELETE ME !!!
	void testPrint()
	{
		int length = _cases.size();
		cout << "Length: " << length << endl;
		cout << "=================================================" << endl;
		for(int i = 0; i < length; i++)
		{
			_cases[i]->testPrint();
		}
	}
	void testPrint(int cid)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if((*vit)->getCid() == cid)
		{
			(*vit)->testPrint();
		}
	}
	void addToCaseOriginal(int cid, int assocCid)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if((*vit)->getCid() == cid) {(*vit)->addOrigCid(assocCid);}
	}
	void addToCaseAssociated(int cid, int assocCid)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if((*vit)->getCid() == cid) {(*vit)->addAssociatedCid(assocCid);}
	}
	bool isClosed(int cid)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if((*vit)->getCid() == cid) {return (*vit)->getCaseStatus();}
		return false;
	}
	void closeCase(int cid)
	{
		Case* t;
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++; t = (*vit);}
		if((*vit)->getCid() == cid)
		{
			vector<int> assocCases;
			int acnt = (*vit)->associatedCount(), count = 0;
			while(count < acnt && isClosed((*vit)->getAssociatedCid(count))) {count++;}
			if(count == acnt) {(*vit)->closeCase();}
		}
	}
	void showAssociatedCases(int cid)
	{
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if((*vit)->getCid() == cid)
		{
			int count = 0, lim = (*vit)->associatedCount();
			cout << endl << "Associated PIDs" << endl << "===========================================" << endl;
			while(count < lim) {cout << "CID: " << (*vit)->getAssociatedCid(count) << endl; count++;}
			if(lim == 0) {cout << "No associated cases" << endl;}
			cout << "===========================================" << endl << endl;
		}
	}
	string showUncontacted()
	{
		string pids = "";
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end())
		{
			if(!(*vit)->getContacted()) {pids += (*vit)->getPid()+";";}
			vit++;
		}
		return pids;
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
	int getSymptomCount() {return _symptoms.size();}
};
class Exceptions
{
private:
	vector<string*> _exceptions;
	char* _error;
public:
	Exceptions()
	{
		_error = nullptr;
		_exceptions.push_back(new string("Cannot convert to integer exception"));
	}
	Exceptions(int e)
	{
		_exceptions.push_back(new string("Cannot convert to integer exception"));
		_error = new char[_exceptions[e]->length()+1];
		strcpy(_error, _exceptions[e]->c_str());
	}
	void setException(int e)
	{
		_error = new char[_exceptions[e]->length()+1];
		strcpy(_error, _exceptions[e]->c_str());
	}
	char* throwException(int e)
	{
		_error = new char[_exceptions[e]->length()+1];
		strcpy(_error, _exceptions[e]->c_str());
		return _error;
	}
	char* getException() {return _error;}
	bool isNumber(string data)
	{
		char* c = new char[data.length()+1];
		int count = 0, length = data.length();
		while(count < length && isdigit(c[count])) {count++;}
		if(count == length) {return true;}
		return false;
	}
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
ostream& operator<<(ostream& out, Exceptions e)
{
	out << e.getException() << endl;
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
		cout << "Debug" << endl << "line: " << line << endl;
		lines.push_back(line);
		getline(infile, line);
	}
	cout << "Debug" << endl << "line: " << line << endl;
	return lines;
}
vector<string> splitLine(const string& line)
{
	vector<string> splitLines;
	stringstream ss(line);
	string s;
	cout << "In splitLine: ";
	while(getline(ss, s, ','))
	{
		cout << "s: " << s << " ";
		splitLines.push_back(s);
	}
	cout << endl;
	return splitLines;
}
string dequote(string& s)
{
	string temp;
	stringstream ss(s);
	vector<string> vec;
	char lim = 34;
	while(getline(ss, temp, lim))
	{
		cout << "in dequote, temp: " << temp << endl;
		if(temp != " " && temp != "") {vec.push_back(temp);}
	}
	if(vec.size() > 0) {temp = vec[0];}
	else {temp = "";}
	return temp;
}
string removeSpaces(string& s)
{
	string temp;
	stringstream ss(s);
	vector<string> vec;
	char lim = ' ';
	while(getline(ss, temp, lim))
	{
		cout << "temp in remove spaces: " << temp << endl;
		if(temp != " " && temp != "") {vec.push_back(temp);}
	}
	if(vec.size() > 0) {temp = vec[0];}
	else {temp = "";}
	cout << "temp to return: " << temp << endl;
	return temp;
}
void addCase(AllCases& cases, AllPersons& persons, string data)
{
	// needs to split the line and then find out how you need to read the data in each line
	// !!! DELETE ALL OF THE TEST PRINTS FROM HERE FOR FINAL VERSION !!!
	vector<string> split = splitLine(data);
	int length = split.size();
	cout << "split length: " << length << endl;
	cout << "test print data in addCase: " << data << endl;
	cout << "test print split data in addCase" << endl << "split[0], split[1], split[2]: " << split[0] << ", " << split[1] << ", " << split[2] << endl;
	for(int i = 0; i < length; i++)
	{
		cout << "split " << i << ": " << split[i] << endl;
	}
	int cid = stoi(split[0]);
	cout << "cid made: " << cid << endl;
	int pid = stoi(split[1]);
	cout << "pid made: " << pid << endl;
	string fname = split[2];
	cout << "fname made: " << fname << endl;
	string lname = split[3];
	cout << "lname made: " << lname << endl;
	string email = split[4];
	cout << "email made: " << email << endl;
	int contacted = stoi(split[5]);
	cout << "contacted made: " << contacted << endl;
	int symCnt = stoi(split[6]);
	cout << "symCnt made: " << symCnt << endl;
	vector<string> symList;
	vector<int> confList, sevList;
	int index = 7, lim = index+symCnt;
	//index++;
	cout << "index: " << index << ", lim: " << lim << endl;
	while(index < lim)
	{
		string t1 = split[index];
		int t2 = stoi(split[index+symCnt]), t3 = stoi(split[index+(symCnt*2)]);
		symList.push_back(t1);
		confList.push_back(t2);
		sevList.push_back(t3);
		index++;
	}
	index = index+(symCnt*2);
	cout << "index after adding symptoms: " << index << endl;
	// test here
	cout << "cid: " << cid << endl << "pid: " << pid << endl << "fname: " << fname << endl << "lname: " << lname << endl << "email: " << email << endl;
	cout << "contacted: " << contacted << endl << "symCnt: " << symCnt << endl;
	for(int i = 0; i < symCnt; i++)
	{
		cout << "sym: " << symList[i] << ", confirmed: " << confList[i] << ", severity: " << sevList[i] << endl;
	}
	cout << "ending index: " << index << endl;
	string diagDate = removeSpaces(split[index++]);
	cout << "date: " << diagDate << endl << "index: " << index << endl;
	string deqDate = "";
	if(diagDate != "") {deqDate = dequote(diagDate);}
	cout << "dequoted date: " << deqDate << endl;
	int diagnosis = stoi(split[index++]);
	int docid;
	if(diagnosis != -1) {docid = stoi(split[index++]);}
	else {docid = -1;}
	cout << "diagnosis: " << diagnosis << endl << "docid: " << docid << endl;
	int origCaseCnt = stoi(split[index++]);
	lim = index+origCaseCnt;
	cout << "origCaseCnt: " << origCaseCnt << endl << "index: " << index << endl << "lim: " << lim << endl;
	vector<int> origCases, assocCases;
	if(index < lim)
	{
		while(index < lim)
		{
			int origCid = stoi(split[index]);
			origCases.push_back(origCid);
			cout << "ocid " << index << ": " << origCid << endl;
			index++;
		}
	}
	int assocCaseCnt = stoi(split[index++]);
	lim = index+assocCaseCnt;
	cout << "assocCaseCnt: " << assocCaseCnt << endl << "index: " << index << endl << "lim: " << lim << endl;
	if(index < lim)
	{
		while(index < lim)
		{
			int assocCid = stoi(split[index]);
			assocCases.push_back(assocCid);
			cout << "acid: " << index << ": " << assocCid << endl;
			cout << assocCases[0] << endl;
			index++;
		}
	}
	int status = stoi(split[index++]);
	cout << "status (closed?): " << status << endl;
	if(contacted == 0)
	{
		cases.addCase(cid, pid);
	}
	else
	{
		cases.addCase(cid, pid, deqDate, diagnosis, docid, contacted);
		cases.addToCaseContacted(cid, contacted);
		cases.addDiagnosisInfo(cid, diagnosis, docid, deqDate);
	}
	/*cases.addCase(cid, pid, deqDate, diagnosis, docid, contacted);
	cases.addToCaseContacted(cid, contacted);
	cases.addDiagnosisInfo(cid, diagnosis, docid, deqDate);*/
	if(symCnt > 0)
	{
		for(int i = 0; i < symCnt; i++)
		{
			string sym = symList[i];
			int conf = confList[i];
			int sev = sevList[i];
			cases.addToCaseSymptom(cid, sym, conf, sev);
		}
	}
	if(origCaseCnt > 0)
	{
		for(int i = 0; i < origCaseCnt; i++)
		{
			int origPid = origCases[i];
			cout << "origPid" << origPid << endl;
			cases.addToCaseOriginal(cid, origPid);
		}
	}
	if(assocCaseCnt > 0)
	{
		for(int i = 0; i < assocCaseCnt; i++)
		{
			int assocPid = assocCases[i];
			cout << "assocPid: " << assocPid << endl;
			cases.addToCaseAssociated(cid, assocPid);
		}
	}
	persons.addPerson(pid, fname, lname, email);
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
	int symCount = symptomList.size();
	for(int i = 0; i < symCount; i++)
	{
		symptoms.addPossibleSymptom(symptomList[i]);
	}
	cout << "compiled" << endl;
	int caseCnt = caseInfo.size();
	for(int i = 0; i < caseCnt; i++)
	{
		addCase(cases, persons, caseInfo[i]);
		cout << "case " << i+1 << " was added" << endl;
	}
	string input = "5";
	string options[] = {"View a case file", "View uncontacted persons for a case", "Modify a case file", "View all open cases", "Exit"};
	int optionCount = *(&options + 1) - options;
	cout << "Covid-19 Case Tracker" << endl;
	for(int i = 0; i < optionCount; i++) {cout << to_string(i+1) << ": " << options[i] << endl;}
	cout << "==================================================" << endl << "Enter number of option to select: ";
	getline(cin, input);
	cout << endl;
	while(input != "5")
	{
		//
	}
	// saves here
	/*caseInfo.clear(); symptomList.clear();
	for(int i = 0; i < symptoms.getSymptomCount(); i++) {symptomList.push_back(symptoms.getSymptom(i));}
	for(int i = 0; i < cases.getCaseCount(); i++)
	{
		//
	}*/
	return 0;
}









































