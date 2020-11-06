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
#include <ctime>
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
 * 		- Finish adding the accessors/mutators first. Those are easy and will really shape what to do next on their own
 * 		- Create a method to read in data from the text files. Just make one method that returns a vector of strings?
 * 	- Never pass a vector in/out
 * 	- !!! Checks in the menu options are not working properly, nor are the loop structures !!! !!! URGENT !!!
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
			if((_d > 29 && _y%4 == 0) || (_d > 28 && _y%4 != 0)) {_m++; _d = 1;}
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
		if(s != "") {convert(s);}
		else {_m = 0; _d = 0; _y = 0;}
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
	Date* _diagDate;
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
		if(date != "") {_diagDate = new Date(date);}
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
		_diagDate = nullptr;
	}
	Case(int cid, int pid)
	{
		_cid = cid;
		_pid = pid;
		_contacted = 0;
		_whoConf = -1;
		_diagnosis = -1;
		_caseStatus = 0;
		_diagDate = nullptr;
	}
	Case(int cid, int pid, int contacted)
	{
		_cid = cid;
		_pid = pid;
		_contacted = contacted;
		_whoConf = -1;
		_diagnosis = -1;
		_caseStatus = 0;
		_diagDate = nullptr;
	}
	void closeCase() {_caseStatus = !_caseStatus;}
	void setContacted(int contacted) {_contacted = contacted;}
	void contacted() {_contacted = !_contacted;}
	void setCid(int cid) {_cid = cid;}
	void setPid(int pid) {_pid = pid;}
	void setDiag(int diagnosis) {_diagnosis = diagnosis;}
	void setWhoConfirmed(int docId) {_whoConf = docId;}
	void setCaseStatus(int caseStatus) {_caseStatus = caseStatus;}
	void setDiagDate(string date) {_diagDate = new Date(date);}
	int getContacted() {return _contacted;}
	int getCid() {return _cid;}
	int getPid() {return _pid;}
	int getDiag() {return _diagnosis;}
	int getWhoConfirmed() {return _whoConf;}
	int getCaseStatus() {return _caseStatus;}
	string getDiagDate() {return _diagDate->getDate();}
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
		int size = _confirmed.size();
		if(index < 0 || index > size-1) {return;}
		std::vector<int>::iterator vit = _confirmed.begin() + index;
		_confirmed.erase(vit);
	}
	void addSeverity(int severity) {_severity.push_back(severity);}
	void modifiySeverity(int index, int severity) {_severity[index] = severity;}
	void removeSeverity(int index)
	{
		int size = _severity.size();
		if(index < 0 || index > size) {return;}
		std::vector<int>::iterator vit = _severity.begin()+index;
		_severity.erase(vit);
	}
	int getSeverity(int index) {return _severity[index];}
	int getOrigCid(int index) {return _original[index];}
	void addOrigCid(int cid) {_original.push_back(cid);}
	void removeOrigCid(int index)
	{
		int size = _original.size();
		if(index < 0 || index > size) {return;}
		std::vector<int>::iterator vit = _original.begin()+index;
		_severity.erase(vit);
	}
	int getAssociatedCid(int index) {return _associated[index];}
	void addAssociatedCid(int cid) {_associated.push_back(cid);}
	void removeAssociatedCid(int index)
	{
		int size = _associated.size();
		if(index < 0 || index > size) {return;}
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
		cout << "Case status: " << _caseStatus << endl;
	}
};
class AllPersons
{
private:
	vector<Person*> _persons; // or vector<*Person>
	Person* getPersonByPid(int pid)
	{
		Person* personptr = nullptr;
		std::vector<Person*>::iterator vit = _persons.begin();
		while(vit != _persons.end() && (*vit)->getPid() != pid) {vit++;}
		if((*vit)->getPid() == pid) {personptr = (*vit);}
		return personptr;
	}
	string noCaseFound(int pid) {return "No person with ID "+to_string(pid)+" was found";}
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
		Person* personptr = getPersonByPid(pid);
		if(personptr) {personptr->setFname(fname);}
	}
	void setLname(int pid, string lname)
	{
		Person* personptr = getPersonByPid(pid);
		if(personptr) {personptr->setLname(lname);}
	}
	void setEmail(int pid, string email)
	{
		Person* personptr = getPersonByPid(pid);
		if(personptr) {personptr->setEmail(email);}
	}
	const int getPid(int i) {return _persons[i]->getPid();}
	const string getFname(int pid)
	{
		string fname = "";
		Person* personptr = getPersonByPid(pid);
		if(personptr) {fname = personptr->getFname();}
		return fname;
	}
	const string getLname(int pid)
	{
		string lname = "";
		Person* personptr = getPersonByPid(pid);
		if(personptr) {lname = personptr->getLname();}
		return lname;
	}
	const string getEmail(int pid)
	{
		string email = "";
		Person* personptr = getPersonByPid(pid);
		if(personptr) {email = personptr->getEmail();}
		return email;
	}
	void addPerson(int pid, string fname, string lname, string email)
	{
		if(_persons.size() == 0) {_persons.push_back(new Person(pid, fname, lname, email));}
		else
		{
			Person* personptr = getPersonByPid(pid);
			if(!personptr) {_persons.push_back(new Person(pid, fname, lname, email));}
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
		Person* personptr = getPersonByPid(pid);
		if(personptr) {personptr->setEmail(email);}
	}
	void modifyPersonFname(int pid, string fname)
	{
		Person* personptr = getPersonByPid(pid);
		if(personptr) {personptr->setFname(fname);}
	}
	void modifyPersonLname(int pid, string lname)
	{
		Person* personptr = getPersonByPid(pid);
		if(personptr) {personptr->setLname(lname);}
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
	string noCaseFound(int cid) {return "No case with ID "+to_string(cid)+" was found";}
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
	string operator[](int cid)
	{
		string t = "";
		Case* caseptr = getCaseByCid(cid);
		if(caseptr)
		{
			t = "Case ID: "+to_string(caseptr->getCid())+" | Person ID: "+to_string(caseptr->getPid())+"\nNumber of original cases: ";
			t += to_string(caseptr->originalCount())+" | Number of associated cases: "+to_string(caseptr->associatedCount());
		}
		else {t = "No case with ID "+to_string(cid)+" was found";}
		return t;
	}
	// can make a case here and modify everything else
	int getCaseCount() {return _cases.size();}
	void setCid(int index, int cid) {_cases[index]->setCid(cid);}
	void setCasePid(int cid, int pid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {caseptr->setPid(pid);}
	}
	void setCaseDiagnosis(int cid, int diagnosis)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {caseptr->setDiag(diagnosis);}
	}
	void setDoctorId(int cid, int docid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {caseptr->setWhoConfirmed(docid);}
	}
	void setContacted(int cid, int contacted)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {caseptr->setContacted(contacted);}
	}
	void setContacted(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {caseptr->contacted();}
	}
	void addSymptom(int cid, string symptom, int confirmed, int severity)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr)
		{
			caseptr->addSymptom(symptom);
			caseptr->addConfirmed(confirmed);
			caseptr->addSeverity(severity);
		}
	}
	int getCid(int index) {return _cases[index]->getCid();}
	int getPid(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getPid();}
		else {return -1;}
	}
	string getDate(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getDiagDate();}
		return "";
	}
	int getCaseDiagnosis(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getDiag();}
		return -1;
	}
	int getDoctorId(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getWhoConfirmed();}
		return -1;
	}
	bool isClosed(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getCaseStatus();}
		return false;
	}
	int caseStatus(int index) {return !_cases[index]->getCaseStatus();}
	int caseExists(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return 1;}
		else {return 0;}
	}
	int getContacted(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getContacted();}
		return -1;
	}
	int getCaseSymptomCount(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->symptomCount();}
		return -1;
	}
	string getSymptom(int cid, int index)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getSymptom(index);}
		return "";
	}
	int getConfirmed(int cid, int index)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getConfirmed(index);}
		return -1;
	}
	int getSeverity(int cid, int index)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getSeverity(index);}
		return -1;
	}
	int getCaseOriginalCount(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->originalCount();}
		return -1;
	}
	int getOriginalCase(int cid, int index)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getOrigCid(index);}
		return -1;
	}
	int getCaseAssociatedCount(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->associatedCount();}
		return -1;
	}
	int getAssociatedCase(int cid, int index)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {return caseptr->getAssociatedCid(index);}
		return -1;
	}
	void addCase(int cid, int pid, string date, int diag, int whoconf, int contacted)
	{
		if(_cases.size() == 0) {_cases.push_back(new Case(cid, pid, date, diag, whoconf, contacted));}
		else
		{
			if(getCaseByCid(cid) == nullptr) {_cases.push_back(new Case(cid, pid, date, diag, whoconf, contacted));}
		}
	}
	void addCase(int cid, int pid, int diag, int whoconf, int contacted, int status)
	{
		if(_cases.size() == 0) {_cases.push_back(new Case(cid, pid, diag, whoconf, contacted, status));}
		else
		{

			if(getCaseByCid(cid) == nullptr) {_cases.push_back(new Case(cid, pid, diag, whoconf, contacted, status));}
		}
	}
	void addCase(int cid, int pid)
	{
		if(_cases.size() == 0) {_cases.push_back(new Case(cid, pid));}
		else
		{
			if(getCaseByCid(cid) == nullptr) {_cases.push_back(new Case(cid, pid));}
		}
	}
	void addCase(int cid, int pid, int contacted)
	{
		cout << "in addCase(cid, pid, contacted)" << endl << "cid: " << cid << endl << "pid: " << pid << endl << "contacted: " << contacted << endl;
		if(_cases.size() == 0) {_cases.push_back(new Case(cid, pid, contacted));}
		else
		{
			cout << "case count: " << _cases.size() << endl;
			if(!getCaseByCid(cid)) {cout << "cid " << cid << " does not exist" << endl; _cases.push_back(new Case(cid, pid, contacted)); cout << "case pushed" << endl;}
			else {cout << "cid " << cid << " already exists" << endl;}
		}
	}
	void addToCaseContacted(int cid, int contacted)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {caseptr->setContacted(contacted);}
	}
	void addDiagnosisInfo(int cid, int diagnosis, int whoDiagnosed, string date)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr)
		{
			caseptr->setWhoConfirmed(whoDiagnosed);
			caseptr->setDiag(diagnosis);
			caseptr->setDiagDate(date);
		}
	}
	void addDiagnosisInfo(int cid, int diagnosis, int whoDiagnosed)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr)
		{
			caseptr->setWhoConfirmed(whoDiagnosed);
			caseptr->setDiag(diagnosis);
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
		while(vit != _cases.end() && (*vit)->getCid() != cid) {vit++;}
		if((*vit)->getCid() == cid) {(*vit)->setCaseStatus(status);}
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
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {caseptr->testPrint();}
	}
	void addToCaseOriginal(int cid, int assocCid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {caseptr->addOrigCid(assocCid);}
	}
	void addToCaseAssociated(int cid, int assocCid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr) {caseptr->addAssociatedCid(assocCid);}
	}
	void closeCase(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr)
		{
			vector<int> assocCases;
			int acnt = caseptr->associatedCount(), count = 0;
			while(count < acnt && isClosed(caseptr->getAssociatedCid(count))) {count++;}
			if(count == acnt) {caseptr->closeCase();}
		}
	}
	void showAssociatedCases(int cid)
	{
		Case* caseptr = getCaseByCid(cid);
		if(caseptr)
		{
			int count = 0, lim = caseptr->associatedCount();
			cout << endl << "Associated PIDs" << endl << "===========================================" << endl;
			while(count < lim) {cout << "CID: " << caseptr->getAssociatedCid(count) << endl; count++;}
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
	string viewCase(int cid)
	{
		string caseInfo = "";
		Case* caseptr = getCaseByCid(cid);
		if(caseptr)
		{
			string ids = "Case ID: "+to_string(caseptr->getCid())+" | Person ID: "+to_string(caseptr->getPid());
			string orig, assoc;
			if(caseptr->originalCount() > 0)
			{
				orig = "Original case IDs: "+to_string(caseptr->getOrigCid(0));
				int count = 1, length = caseptr->originalCount();
				while(count < length)
				{
					orig += " | "+to_string(caseptr->getOrigCid(count));
					count++;
				}
			}
			else {orig = "No original cases";}
			if(caseptr->associatedCount() > 0)
			{
				assoc = "Associated case IDs: "+to_string(caseptr->getAssociatedCid(0));
				int count = 1, length = caseptr->associatedCount();
				while(count < length)
				{
					assoc += " | "+to_string(caseptr->getAssociatedCid(count));
					count++;
				}
			}
			else {assoc = "No Associated Cases";}
			caseInfo = ids+"\n"+orig+"\n"+assoc;
		}
		else {caseInfo = noCaseFound(cid);}
		return caseInfo;
	}
	string getUncontactedPids(int cid)
	{
		string assocCids;
		Case* caseptr = getCaseByCid(cid);
		if(!caseptr) {return noCaseFound(cid);}
		int acnt = caseptr->associatedCount();
		if(acnt > 0)
		{
			assocCids = "";
			for(int i = 0; i < acnt; i++)
			{
				Case* temp = getCaseByCid(caseptr->getAssociatedCid(i));
				if(!temp->getContacted()) {assocCids += to_string(temp->getCid())+" ";}
			}
			if(assocCids.length() == 0) {assocCids = "No uncontacted persons in associated cases in case "+to_string(cid);}
		}
		else {assocCids = "No uncontacted persons in associated cases in case "+to_string(cid);}
		return assocCids;
	}
	int countOpenCases()
	{
		int openCnt = 0, length = _cases.size();
		for(int i = 0; i < length; i++) {if(caseStatus(i)) {openCnt++; cout << "open case id: " << _cases[i]->getCid();}}
		if(openCnt > 0) {cout << endl;}
		return openCnt;
	}
	string getOpenCases()
	{
		string cids;
		std::vector<Case*>::iterator vit = _cases.begin();
		while(vit != _cases.end())
		{
			if(!(*vit)->getCaseStatus()) {cids += to_string((*vit)->getCid())+" ";}
			vit++;
		}
		return cids;
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
int isDigit(const string& input)
{
	int length = input.length();
	char* c = new char[length+1];
	strcpy(c, input.c_str());
	int count = 0;
	while(count < length && isdigit(c[count])) {count++;}
	if(count == length) {return 1;}
	return 0;
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
void addCaseRew(AllCases& cases, AllPersons& persons, string data)
{
	vector<string> split = splitLine(data);
	int length = split.size();
	cout << "split info for case" << endl;
	for(int i = 0; i < length; i++) {cout << "Split[" << i << "]: " << split[i] << endl;}
	int cid = stoi(split[0]);
	int pid = stoi(split[1]);
	string fname = split[2];
	string lname = split[3];
	string email = split[4];
	int contacted = stoi(split[5]);
	cout << "cid: " << cid << ", pid: " << pid << ", fname: " << fname << ", lname: " << lname << ", email: " << email << ", contacted: " << contacted << endl;
	cases.addCase(cid, pid, contacted);
	cout << "case created" << endl;
	persons.addPerson(pid, fname, lname, email);
	cout << "person added" << endl;
	int index = 6;
	string date;
	int diagnosis, doctor;
	cout << "Before adding contacted" << endl;
	if(contacted)
	{
		cout << contacted << endl;
		int symCount = stoi(split[6]), count = 0;
		index++;
		while(count < symCount && symCount != 0)
		{
			string symptom = split[index];
			int confirmed = stoi(split[index+symCount]);
			int severity = stoi(split[index+(symCount*2)]);
			cout << "Symptom: " << symptom << endl << "Confirmed: " << confirmed << endl << "Severity: " << severity << endl;
			cases.addToCaseSymptom(cid, symptom, confirmed, severity);
			index++;
			count++;
		}
		cout << "Index: " << index << endl;
		cout << "split[" << index << "]: " << split[index];
		index += (symCount*2);
		cout << "split[" << index << "]: " << split[index];
		date = dequote(split[index++]);
		diagnosis = stoi(split[index++]);
		cout << "diagnosis: " << diagnosis << endl;
		doctor = stoi(split[index++]);
		cases.addDiagnosisInfo(cid, diagnosis, doctor, date);
	}
	else
	{
		cout << "not contacted" << endl;
		index++;
		date = split[index++];
		cout << "date: " << date << endl;
		diagnosis = stoi(split[index++]);
		cout << "diagnosis: " << diagnosis << endl;
		doctor = -1; index++;
		cases.addDiagnosisInfo(cid, diagnosis, doctor);
	}
	int origCaseCount = stoi(split[index++]);
	if(origCaseCount > 0)
	{
		int count = 0;
		while(count < origCaseCount)
		{
			cases.addToCaseOriginal(cid, stoi(split[index++]));
			count++;
		}
	}
	int assocCaseCount = stoi(split[index++]);
	if(assocCaseCount > 0)
	{
		int count = 0;
		while(count < assocCaseCount)
		{
			cases.addToCaseAssociated(cid, stoi(split[index++]));
			count++;
		}
	}
	int status = stoi(split[index]);
	cout << "Case Status: " << status << endl;
	cout << "Original case count: " << origCaseCount << endl << "Associated case count: " << assocCaseCount << endl;
	cases.setCaseStatus(cid, status);
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
	try
	{
		if(contacted != 0 && contacted != 1) {throw "No contact information for CID "+cid;}
	}catch (char* e) {cout << e << endl; exit(-1);}
	if(contacted == 0)
	{
		cases.addCase(cid, pid);
		cout << "In addCase(), case " << cid << ", uncontacted person " << pid << " was added" << endl;
	}
	else
	{
		cases.addCase(cid, pid, deqDate, diagnosis, docid, contacted);
		cases.addToCaseContacted(cid, contacted);
		cases.addDiagnosisInfo(cid, diagnosis, docid, deqDate);
		cout << "In addCase(), case " << cid << ", contacted person " << pid << " was added" << endl;
	}
	/*cases.addCase(cid, pid, deqDate, diagnosis, docid, contacted);
	cases.addToCaseContacted(cid, contacted);
	cases.addDiagnosisInfo(cid, diagnosis, docid, deqDate);*/
	cout << "adding symptoms to case" << endl;
	if(symCnt > 0)
	{
		for(int i = 0; i < symCnt; i++)
		{
			string sym = symList[i];
			int conf = confList[i];
			int sev = sevList[i];
			cases.addToCaseSymptom(cid, sym, conf, sev);
			cout << "symptom " << sym << " with severity " << sev << " with confirmation " << conf << " was added" << endl;
		}
	}
	if(origCaseCnt > 0)
	{
		cout << "Original cases to add" << endl;
		for(int i = 0; i < origCaseCnt; i++)
		{
			int origPid = origCases[i];
			cout << "origPid" << origPid << endl;
			cases.addToCaseOriginal(cid, origPid);
			cout << "original pid " << origPid << " was added to " << cid << endl;
		}
	}
	else {cout << "No original cases to add" << endl;} // delete me
	if(assocCaseCnt > 0)
	{
		cout << "Associated cases to add" << endl;
		for(int i = 0; i < assocCaseCnt; i++)
		{
			int assocPid = assocCases[i];
			cout << "assocPid: " << assocPid << endl;
			cases.addToCaseAssociated(cid, assocPid);
			cout << "associated case " << assocPid << " was added to " << cid << endl;
		}
	}
	else {cout << "no associated cases to add" << endl;}
	persons.addPerson(pid, fname, lname, email);
	cout << "Person " << pid << ", name: " << lname << ", " << fname << " with email " << email << " was added to case" << endl;
}
void clearMenu() // this is a function psuedo-clears the console. It just ends lines in the console so that the previous text is no longer visible
{
	/*
	 * This is the reason I implemented the option to save the session data in main. This way, the user won't have to scroll up to view information again. It's
	 * stored in a text file for viewing longer than the program runs/console is open
	 */
	for(int i = 0; i < 15; i++) {cout << endl;}
}
string viewCase(AllCases& cases)
{
	string input, output = "";
	clearMenu();
	while(input != "0" && output == "")
	{
		cout << "Enter case ID you would like to view or 0 to return: ";
		getline(cin, input);
		clearMenu();
		if(input != "0")
		{
			int length = input.length(), count = 0;
			char* c = new char[length+1];
			strcpy(c, input.c_str());
			while(count < length && isdigit(c[count])) {count++;}
			if(count == length)
			{
				int cid = stoi(input);
				output = cases.viewCase(cid);
				//cout << output << endl << endl;
				string data = "View of case ID "+input+": "+output;
				return data;
			}
			else {cout << input << " is not a valid integer" << endl;}
		}
		cin.clear();
	}
	return output;
}
string viewUncontactedInCase(AllCases& cases) // this doesn't work correctly. FIX IT
{
	string input, output = "";
	clearMenu();
	while(input != "0" && output == "")
	{
		cout << "Enter case ID of case to view uncontacted persons: ";
		getline(cin, input);
		clearMenu();
		if(input != "0")
		{
			int length = input.length(), count = 0;
			char* c = new char[length+1];
			strcpy(c, input.c_str());
			while(count < length && isdigit(c[count])) {count++;}
			if(count == length)
			{
				int cid = stoi(input);
				output = cases.getUncontactedPids(cid);
				//cout << "Uncontacted IDs: " << output << endl << endl;
				string data = "Uncontacted Person IDs for case "+input+": "+output;
				return data;
			}
			else {cout << input << " is not a valid integer" << endl;}
		}
		cin.clear();
	}
	return output;
}
string modifyCase(AllCases& cases, int cid)
{
	string result;
	//
	return result;
}
string modify(AllCases& cases, vector<string>& sessionData)
{
	string input, output;
	clearMenu();
	while(input != "0" && output == "")
	{
		cout << "Enter the case ID to modify: ";
		getline(cin, input);
		clearMenu();
		int valid = isDigit(input);
		if(valid)
		{
			int cid = stoi(input);
			if(cases.caseExists(cid))
			{
				string caseVars[] = {"Case ID", "Person ID", "Diagnosis Date", "Diagnosis", "Doctor ID", "Symptoms", "Original Cases", "Associated Cases", "Case Status"};
				int origCount = cases.getCaseOriginalCount(cid), assocCount = cases.getCaseAssociatedCount(cid);
				cout << "1: this case" << endl << "2: original cases" << endl << "3: associated cases" << endl;
				cout << "What would you like to modify?: ";
				getline(cin, input);
				cout << endl;
			}
			else {cout << "Case with ID " << cid << " does not exist" << endl;}
		}
		else {cout << input << " is not a valid integer" << endl;}
	}
	return output;
}
int splitCids(const string& t, int& index)
{
	cout << "test -- t: " << t << endl;
	int cid = -1, length = t.length();
	stringstream ss(t);
	string buff = "";
	char* c = new char[length+1];
	strcpy(c, t.c_str());
	while(index < length && cid == -1)
	{
		cout << "c[" << index << "]: " << c[index] << endl;
		if(c[index] != ' ') {buff += c[index];}
		else
		{
			if(buff != " " && buff != "") {cid = stoi(buff);}
		}
		index++;
	}
	return cid;
}
string showOpenCases(AllCases& cases, AllPersons& persons)
{
	string data;
	int length = cases.countOpenCases();
	if(length > 0)
	{
		data = "There are "+to_string(length)+" open cases\n----------------------------------------------\n";
		string cids = cases.getOpenCases();
		int count = 0, index = 0;
		while(count < length)
		{
			int cid = splitCids(cids, index);
			if(cid != -1)
			{
				int pid = cases.getPid(cid), contacted = cases.getContacted(cid);
				string fname = persons.getFname(pid), lname = persons.getLname(pid);
				data += "Case ID: "+to_string(cid)+", Person ID: "+to_string(pid)+"\nName: "+lname+", "+fname+"\nContacted?: ";
				if(contacted) {data += "Yes";}
				else {data += "No";}
				data += "\n----------------------------------------------";
				count++;
				if(count < length) {data += "\n";}
			}
		}
	}
	/*if(length > 0)
	{
		data = "There are "+to_string(length)+" open cases\n----------------------------------------------\n";
		for(int i = 0; i < length; i++)
		{
			int status = cases.caseStatus(i);
			if(status)
			{
				int cid = cases.getCid(i), pid = cases.getPid(cid), contacted = cases.getContacted(cid);
				string fname = persons.getFname(pid), lname = persons.getLname(pid);
				data += "Case ID: "+to_string(cid)+", Person ID: "+to_string(pid)+"\nName: "+lname+", "+fname+"\nContacted?: ";
				if(contacted) {data += "Yes";}
				else {data += "No";}
				data += "\n----------------------------------------------\n";
			}
		}
	}*/
	else {data = "There are no open cases";}
	return data;
}
void writeSessionData(vector<string*>& sessionData)
{
	fstream file;
	string fn = "session_data.txt";
	file.open(fn, ios::out);
	int length = sessionData.size();
	for(int i = 0; i < length; i++) {file << *sessionData[i] << endl; delete(sessionData[i]); sessionData[i] = nullptr;}
	file << endl;
	file.close();
}
void writeSymptoms(AllSymptoms& symptoms, ostream& outfile)
{
	int count = 0, symptomCount = symptoms.getSymptomCount();
	while(count < symptomCount)
	{
		string line = symptoms.getSymptom(count);
		outfile << line << endl;
		count++;
	}
	outfile << endl;
}
void writeCaseData(AllCases& cases, AllPersons& persons, ostream& outfile)
{
	int count = 0, caseCount = cases.getCaseCount();
	while(count < caseCount)
	{
		string line = "";
		int cid = cases.getCid(count), pid = cases.getPid(cid);
		line += to_string(cid)+", "+to_string(pid)+", ";
		line += persons.getFname(pid)+", "+persons.getLname(pid)+", "+persons.getEmail(pid)+", ";
		int symptomCount = cases.getCaseSymptomCount(cid);
		for(int i = 0; i < symptomCount; i++) {line += cases.getSymptom(cid, i)+", ";}
		for(int i = 0; i < symptomCount; i++) {line += to_string(cases.getConfirmed(cid, i))+", ";}
		for(int i = 0; i < symptomCount; i++) {line += to_string(cases.getSeverity(cid, i))+", ";} // find a better way to do this
		line += cases.getDate(cid)+", ";
		line += cases.getCaseDiagnosis(cid)+", ";
		line += cases.getDoctorId(cid)+", ";
		int originalCnt = cases.getCaseOriginalCount(cid), assocCount = cases.getCaseAssociatedCount(cid);
		line += to_string(originalCnt);
		for(int i = 0; i < originalCnt; i++) {line += to_string(cases.getOriginalCase(cid, i));}
		line += to_string(assocCount);
		for(int i = 0; i < assocCount; i++) {line += to_string(cases.getAssociatedCase(cid, i));}
		line += to_string(cases.isClosed(cid));
		outfile << line << endl;
		count++;
	}
	outfile << endl;
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
		addCaseRew(cases, persons, caseInfo[i]);
		cout << "case " << i+1 << " was added" << endl;
	}

	//======================== This is used for storing/writing out the current session's data, since the clear menu function is being used ===========================

	/*
	 * This was something I implemented in because the menu got crowded with data and I didn't think it looked too much like a menu in that state. It is disabled by
	 * default in case you are doing large tests. I figured that would just increase runtime and would take up more memory for no reason. If you wanted to run the
	 * program with it enabled, it can be turned on below
	 */
	//                          !!! MAKE SURE THAT BOOL IS SET TO FALSE AND THIS COMMENT IS DELETED BEFORE TURNING IN !!!
	/*
	 *-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	 * 								>>> Data log >>> */ bool sessionStorage = false; /* <<< enabled here <<<
	 *-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	 * */
	//
	vector<string*> sessionData;
	if(sessionStorage)
	{
		tm* localTime;
		time_t ctime = time(0);
		localTime = localtime(&ctime);
		int d = localTime->tm_mday, m = 1+localTime->tm_mon, y = 1900+localTime->tm_year;
		Date date(m, d, y);
		int hr = localTime->tm_hour, min = localTime->tm_min, s = localTime->tm_sec;
		string minstr, secstr;
		if(to_string(s).length() == 1) {secstr = "0"+to_string(s);}
		else {secstr = to_string(s);}
		if(to_string(min).length() == 1) {minstr = "0"+to_string(min);}
		else {minstr = to_string(min);}
		string after;
		if(hr > 12) {hr -= 12; after = "PM";}
		else {after = "AM";}
		string time = to_string(hr)+":"+minstr+":"+secstr+" "+after;
		string sessionStart = "Session start time: "+date.getDate()+" "+time+"\n";
		sessionData.push_back(new string(sessionStart));
	}
	//=================================================================================================================================================================

	string input = "5";
	string options[] = {"View a case file", "View uncontacted persons for a case", "Modify a case file", "View all open cases", "Exit"};
	int optionCount = *(&options + 1) - options;
	cout << endl << "Debug test print" << endl << "////////////////////////////////" << endl;
	for(int i = 0; i < cases.getCaseCount(); i++) {cases.testPrint(i);}
	cout << "End of test print" << endl << "/////////////////////////////" << endl << endl;
	cout << "Covid-19 Case Tracker" << endl;
	for(int i = 0; i < optionCount; i++) {cout << to_string(i+1) << ": " << options[i] << endl;}
	cout << "==================================================" << endl << endl << "Enter number of option to select: ";
	getline(cin, input);
	cout << endl;
	while(input != "5")
	{
		int option;
		string result;
		if(input == "1") {result = viewCase(cases); option = 0;}
		else if(input == "2") {result = viewUncontactedInCase(cases); option = 1;}
		else if(input == "4") {result = showOpenCases(cases, persons); option = 3;}
		else {input = "5"; option = 4;} // this is for testing to stop accidental infinite loops
		cin.clear();
		clearMenu();
		cout << result << endl << "Press enter when done viewing results";
		while(input != "") {cin.clear(); getline(cin, input);}
		cout << endl;
		clearMenu();
		for(int i = 0; i < optionCount; i++) {cout << to_string(i+1) << ": " << options[i] << endl;}
		cout << endl;
		cout << "==================================================" << endl << endl << "Enter number of option to select: ";
		getline(cin, input);
		cout << endl;


		//============================================================== For data log =================================================================================
		if(sessionStorage)
		{
			if(result != "" && option != 4)
			{
				string action = "Action: "+options[option];
				sessionData.push_back(new string(action));
				sessionData.push_back(new string("=============================================="));
				sessionData.push_back(new string(result));
				sessionData.push_back(new string("==============================================\n"));
			}
		}
		//=============================================================================================================================================================
	}
	// saves here
	clearMenu();
	cout << "Exiting" << endl;


	//================================================================== For data log =================================================================================
	if(sessionStorage && sessionData.size() > 1) {cout << "Writing session data" << endl; writeSessionData(sessionData); cout << "Session data written" << endl;}
	//=================================================================================================================================================================


	/*caseInfo.clear(); symptomList.clear();
	for(int i = 0; i < symptoms.getSymptomCount(); i++) {symptomList.push_back(symptoms.getSymptom(i));}
	for(int i = 0; i < cases.getCaseCount(); i++)
	{
		//
	}*/
	ofstream outfile;
	outfile.open("symptom_test.txt");
	writeSymptoms(symptoms, outfile);
	outfile.close();
	outfile.open("case_test.txt");
	writeCaseData(cases, persons, outfile);
	outfile.close();
	cout << "Data written to files" << endl;
	return 0;
}









































