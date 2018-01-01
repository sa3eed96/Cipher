#include "ciphers.h"

unordered_map<char,int> ceaser::keyMap = 
{
	{ 'a', 0 }, { 'b', 1 }, { 'c', 2 },
	{ 'd', 3 }, { 'e', 4 }, { 'f', 5 },
	{ 'g', 6 }, { 'h', 7 }, { 'i', 8 },
	{ 'j', 9 }, { 'k',10 }, { 'l',11 },
	{ 'm',12 }, { 'n',13 }, { 'o',14 },
	{ 'p',15 }, { 'q',16 }, { 'r',17 },
	{ 's',18 }, { 't',19 }, { 'u',20 },
	{ 'v',21 }, { 'w',22 }, { 'x',23 },
	{ 'y',24 }, { 'z',25 }
};

unordered_map<int, char> ceaser::charMap =
{
	{ 0,'a' }, { 1,'b' }, { 2,'c' },
	{ 3,'d' }, { 4,'e' }, { 5,'f'},
	{ 6,'g'}, { 7,'h'}, { 8,'i' },
	{ 9,'j'}, { 10,'k'}, { 11,'l' },
	{ 12,'m'}, { 13,'n' }, { 14,'o'},
	{ 15,'p'}, { 16,'q' }, { 17,'r' },
	{ 18,'s'}, { 19,'t' }, { 20,'u' },
	{ 21,'v' }, { 22,'w'}, { 23,'x' },
	{ 24,'y' }, { 25,'z'}
};

ceaser::ceaser(char key = 'a') :key(tolower(key))
{}

string ceaser::encrypt(string text)
{
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	int keyValue = keyMap[key];
	int textSize = text.size();
	string decText = "";
	for (int i = 0; i < textSize; i++)
	{	
		if (text[i] == ' ')
			continue;
		int index = (keyMap[text[i]] + keyMap[key])%26;
		decText += charMap[index];
	}
	return decText;
}

string ceaser::decrypt(string text)
{
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	int keyValue = keyMap[key];
	int textSize = text.size();
	string plText = "";
	for (int i = 0; i < textSize; i++)
	{
		int index = (keyMap[text[i]] - keyMap[key]+26)%26;
		plText += charMap[index];
	}
	return plText;
}