#include "ciphers.h"

unordered_map<char, int> viginere::keyMap =
{
	{ 'a', 0 }, { 'b', 1 }, { 'c', 2 },
	{ 'd', 3 }, { 'e', 4 }, { 'f', 5 },
	{ 'g', 6 }, { 'h', 7 }, { 'i', 8 },
	{ 'j', 9 }, { 'k', 10 }, { 'l', 11 },
	{ 'm', 12 }, { 'n', 13 }, { 'o', 14 },
	{ 'p', 15 }, { 'q', 16 }, { 'r', 17 },
	{ 's', 18 }, { 't', 19 }, { 'u', 20 },
	{ 'v', 21 }, { 'w', 22 }, { 'x', 23 },
	{ 'y', 24 }, { 'z', 25 }
};

unordered_map<int, char> viginere::charMap =
{
	{ 0, 'a' }, { 1, 'b' }, { 2, 'c' },
	{ 3, 'd' }, { 4, 'e' }, { 5, 'f' },
	{ 6, 'g' }, { 7, 'h' }, { 8, 'i' },
	{ 9, 'j' }, { 10, 'k' }, { 11, 'l' },
	{ 12, 'm' }, { 13, 'n' }, { 14, 'o' },
	{ 15, 'p' }, { 16, 'q' }, { 17, 'r' },
	{ 18, 's' }, { 19, 't' }, { 20, 'u' },
	{ 21, 'v' }, { 22, 'w' }, { 23, 'x' },
	{ 24, 'y' }, { 25, 'z' }
};

viginere::viginere(string key)
{
	this->key =key;
	transform(this->key.begin(),this->key.end(),this->key.begin(), tolower);
	this->key.erase(remove_if(this->key.begin(), this->key.end(), ::isspace), this->key.end());
}

repeatKeyViginere::repeatKeyViginere(string key) :viginere(key)
{}

string repeatKeyViginere::encrypt(string text)
{

	transform(text.begin(), text.end(), text.begin(), tolower);
	text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end());
	int keySize = key.size();
	int textSize = text.size();
	string encText = "";
	int keyIndex = 0;
	for (int i = 0; i < textSize; i++)
	{
		if (text[i] == ' ')
			continue;
		int index = (keyMap[key[keyIndex%keySize]] + keyMap[text[i]]) % 26;
		encText += charMap[index];
		keyIndex++;
	}
	return encText;
}

string repeatKeyViginere::decrypt(string text)
{
	transform(text.begin(), text.end(), text.begin(), tolower);
	text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end());
	int keySize = key.size();
	int textSize = text.size();
	string plText = "";
	int keyIndex = 0;
	for (int i = 0; i < textSize; i++)
	{
		int index = ((keyMap[text[i]] - keyMap[key[keyIndex%keySize]]) + 26) % 26;
		plText += charMap[index];
		keyIndex++;
	}
	return plText;
}
autoKeyViginere::autoKeyViginere(string key) :viginere(key)
{}

string autoKeyViginere::encrypt(string text)
{
	transform(text.begin(), text.end(), text.begin(), tolower);
	text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end());
	string appendedKey = key.append(text);
	int keySize = appendedKey.size();
	int textSize = text.size();
	string encText = "";
	int keyIndex = 0;
	for (int i = 0; i < textSize; i++)
	{
		int index = (keyMap[appendedKey[keyIndex%keySize]] + keyMap[text[i]]) % 26;
		encText += charMap[index];
		keyIndex++;
	}
	return encText;
}

string autoKeyViginere::decrypt(string text)
{
	transform(text.begin(), text.end(), text.begin(), tolower);
	text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end());
	string appendedKey = key.append(text);
	int keySize = appendedKey.size();
	int textSize = text.size();
	string plText = "";
	int keyIndex = 0;
	for (int i = 0; i < textSize; i++)
	{
		int index = ((keyMap[text[i]] - keyMap[appendedKey[keyIndex%keySize]]) + 26) % 26;
		plText += charMap[index];
		keyIndex++;
	}
	return plText;
}