#include<iostream>
#include<string>
#include"ciphers.h"
void fun(string s,bool mode)
{
	int c;
BEGIN:;
	cout << "choose cipher:" << endl;
	cout << "(1)ceaser" << endl;
	cout << "(2)polybius" << endl;
	cout << "(3)railfence" << endl;
	cout << "(4)viginere with autoKey" << endl;
	cout << "(5)viginere with repeated key" << endl;
	cout << "(6)hill" << endl;
	cin >> c;
	if (c == 1)
	{
		cout << "enter Key (the key is one letter): " << endl;
		char ck;
		cin >> ck;
		ceaser c(ck);
		if (mode)
		{
			cout << c.encrypt(s) << endl;;
		}
		else
		{
			cout << c.decrypt(s) << endl;
		}
	}
	else if (c == 2)
	{
		cout << "enter Key (the key is a string): " << endl;
		string pk;
		cin >> pk;
		polybius p(pk);
		if (mode)
		{
			cout << p.encrypt(s) << endl;;
		}
		else
		{
			cout << p.decrypt(s) << endl;
		}
	}
	else if (c == 3)
	{
		cout << "enter Key (the key is an integer): " << endl;
		int rk;
		cin >> rk;
		railFence r(rk);
		if (mode)
		{
			cout << r.encrypt(s) << endl;;
		}
		else
		{
			cout << r.decrypt(s) << endl;
		}
	}
	else if (c == 4)
	{
		cout << "enter Key (the key is a string): " << endl;
		string ak;
		cin >> ak;
		autoKeyViginere av(ak);
		if (mode)
		{
			cout << av.encrypt(s) << endl;;
		}
		else
		{
			cout << av.decrypt(s) << endl;
		}
	}
	else if (c == 5){
		cout << "enter Key (the key is a string): " << endl;
		string rvk;
		cin >> rvk;
		repeatKeyViginere rv(rvk);
		if (mode)
		{
			cout << rv.encrypt(s) << endl;;
		}
		else
		{
			cout << rv.decrypt(s) << endl;
		}
	}
	else if (c == 6)
	{
		cout << "enter Key (the key is a string): " << endl;
		string hk;
		cin >> hk;
		hill h(hk);
		if (mode)
		{
			cout << h.encrypt(s) << endl;;
		}
		else
		{
			cout << h.decrypt(s) << endl;
		}
	}
	else 
	{
		goto BEGIN;
	}
}
int main()
{
	int c;
BEGIN:;
	cout << "1-encrypt" << endl;
	cout << "2-decrypt" << endl;
	cin >> c;
	if (c == 1){
		cout << "enter something to encrypt: ";
		string s;
		cin >> s;
		fun(s, 1);
	}
	else if (c == 2)
	{
		cout << "enter something to decrypt: ";
		string s;
		cin >> s;
		fun(s, 0);
	}
	else{
		cout << "invalid command." << endl;
		goto BEGIN;
	}
}