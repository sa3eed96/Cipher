#include<unordered_map>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;

class ceaser
{
	char key;
	static  unordered_map<char, int> keyMap;
	static  unordered_map<int, char> charMap;
public:
	ceaser(char);
	string encrypt(string);
	string decrypt(string);
};

class viginere
{
protected:
	string key;
	static  unordered_map<char, int> keyMap;
	static  unordered_map<int, char> charMap;
public:
	viginere(string);
	virtual string encrypt(string) = 0;
	virtual string decrypt(string) = 0;
};

class repeatKeyViginere : public viginere
{
public:
	repeatKeyViginere(string);
	string encrypt(string);
	string decrypt(string);
};

class autoKeyViginere : public viginere
{
public:
	autoKeyViginere(string);
	string encrypt(string);
	string decrypt(string);
};

class hill
{
	string key,text,eText;
	static  unordered_map<char, int> keyMap;
	static unordered_map<int, char> charMap;
	vector<vector<int>> keyMatrix;
	vector<vector<int>> inverseKeyMatrix;
	bool isInvertible;
	vector<int> textVector;

	void createKeyMatrix();
	void createTextVector(string);

	void encryptTextVector(vector<int>&);
	void decryptTextVector(vector<int>&);
	string getVecText(const vector<int>&);

	void getInverseMatrix();
	void getAdjointMatrix(const vector<vector<int>>&, vector<vector<int>>&);
	void getCofactorMat(const vector<vector<int>>&, vector<vector<int>>&, int, int, int);
	void getMatrixTrans(vector<vector<int>>&, int);
	int getMatDet(vector<vector<int>>, int);
	int getMatDetInv(int);
public:
	hill(string);
	string encrypt(string);
	string decrypt(string);
};

class polybius
{
	string key;
	unordered_map<string, char> numLetter;
	unordered_map<char, pair<string, string>> letterNum;
	string modifiedText;
	void createKeySquare();
public:
	polybius(string);
	string encrypt(string);
	string decrypt(string);

};

class railFence
{
	int key;
public:
	railFence(int);
	string encrypt(string);
	string decrypt(string);
};