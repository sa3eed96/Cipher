#include"ciphers.h"
#include<algorithm>

polybius::polybius(string key)
{
	transform(key.begin(), key.end(), key.begin(), tolower);
	this->key = key;
	for (int i = 0; i < key.length(); i++)
	if (this->key[i] == 'j')
		this->key[i] = 'i';
	createKeySquare();
}

void polybius::createKeySquare()
{
	int keyIt = 0;
	char letter = 'a';
	for (char i = '1'; i < '6'; i++)
	{
		for (char j = '1'; j < '6'; j++)
		{
			if (keyIt < key.length())
			{
				while (keyIt < key.length() && letterNum.find(key[keyIt]) != letterNum.end())
					keyIt++;
				if (keyIt < key.length())
				{
					pair<string, string> c;
					c.first = i; c.second = j;
					letterNum[key[keyIt]] = c;
					numLetter[c.second + c.first] = key[keyIt];
					keyIt++;
					continue;
				}
			}
			while (letterNum.find(letter) != letterNum.end() || letter == 'j'){
				letter++;
			}
			pair<string, string> c;
			c.first = i; c.second = j;
			letterNum[letter] = c;
			numLetter[c.second + c.first] = letter;
		}
	}
}

string polybius::encrypt(string text)
{
	transform(text.begin(), text.end(), text.begin(), tolower);
	text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end());
	modifiedText = "";
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == 'j')
			text[i] = 'i';
		modifiedText += text[i];
	}

	string encText = "";
	for (int i = 0; i < modifiedText.length(); i++)
		encText += letterNum[modifiedText[i]].second + letterNum[modifiedText[i]].first;
	return encText;
}

string polybius::decrypt(string text){
	string plText = "";
	for (int i = 0; i < text.length(); i += 2){
		string s = "";
		s += text[i];
		s += text[i + 1];
		plText += numLetter[s];
	}
	return plText;
}