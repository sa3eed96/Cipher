#include "ciphers.h"

railFence::railFence(int key) :key(key)
{}

string railFence::encrypt(string text)
{
	transform(text.begin(), text.end(), text.begin(), tolower);
	text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end());
	char**textMatrix = new char*[key];
	for (int i = 0; i < key; i++)
		textMatrix[i] = new char[text.length()];
	int index = 1;
	bool toggle = true;
	for (int i = 0; i < text.length(); i++)
	{
		if (toggle)
			index--;
		else
			index++;
		if (index == key-1 || index == 0)
			toggle = !toggle;
		textMatrix[index][i] = text[i];
	}

	string encText="";
	for (int i = 0; i < key;i++)
	    for (int j = 0; j < text.length();j++)
		  if (textMatrix[i][j] >= 97 && textMatrix[i][j]<=122)
		    	encText += textMatrix[i][j];

	for (int i = 0; i < key; i++)
		delete textMatrix[i];
	delete[] textMatrix;

	return encText;
}

string railFence::decrypt(string text)
{
	transform(text.begin(), text.end(), text.begin(), tolower);
	char**textMatrix = new char*[key];
	for (int i = 0; i < key; i++)
		textMatrix[i] = new char[text.length()];
	int textIndex = 0;
	int index;
	bool toggle;
	for (int i = 0; i < key; i++)
	{
		index = 1;
		toggle = true;
		for (int j = 0; j < text.length(); j++)
		{
			if (toggle)
				index--;
			else
				index++;
			if (index == key - 1 || index == 0)
				toggle = !toggle;
			if (index == i&&textIndex<text.length())
			{
				textMatrix[index][j] = text[textIndex];
				textIndex++;
			}
		}
		if (textIndex >= text.length())
			break;
	}
	index = 1;
	toggle = true;
	string plText="";
	for (int i = 0; i < text.length(); i++)
	{
		if (toggle)
			index--;
		else
			index++;
		if (index == key - 1 || index == 0)
			toggle = !toggle;
		plText+=textMatrix[index][i];
	}
	for (int i = 0; i < key; i++)
		delete textMatrix[i];
	delete[] textMatrix;
	return plText;
}
