#include "ciphers.h"
#include<math.h>
#include<algorithm>
#include<limits>
unordered_map<char, int> hill::keyMap =
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

unordered_map<int, char> hill::charMap =
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




hill::hill(string key)
{
	this->key = key;
	createKeyMatrix();
	isInvertible = false;
	getInverseMatrix();
}

string hill::encrypt(string text)
{
	int textLen = text.length();
	int keyLen = key.length();
	this->text = text;
	if (textLen != sqrt(keyLen))
	{
		cout << "Invalid text.this key can only encrypt a text of length " << sqrt(keyLen) << ", Encryption failed";
		return "";
	}
	transform(this->text.begin(), this->text.end(), this->text.begin(), tolower);
	createTextVector(this->text);
	vector<int> encryptedTextVector;
	encryptTextVector(encryptedTextVector);
	this->eText = getVecText(encryptedTextVector);
	return eText;
}


void hill::createKeyMatrix()
{
	int rows, cols;
	rows = cols = sqrt(key.length());
	transform(key.begin(), key.end(), key.begin(), tolower);

	keyMatrix.resize(rows, vector<int>(cols, 0));
	int g = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			keyMatrix[i][j] = keyMap[key[g]];
			g++;
		}
	}
}

void hill::createTextVector(string txt)
{
	int rows = txt.length();
	textVector.clear();
	for (int i = 0; i < rows; i++)
	{
		textVector.push_back(keyMap[txt[i]]);
	}
}

void hill::encryptTextVector(vector<int>& encryptedTextVector)
{
	int rows, cols;
	rows = cols = text.length();

	for (int i = 0; i < rows; i++)
	{
		int x = 0;
		for (int j = 0; j < cols; j++)
		{
			x += (textVector[j] * keyMatrix[i][j]);
		}
		x %= 26;
		encryptedTextVector.push_back(x);
	}
}

string hill::getVecText(const vector<int>& TextVector)
{
	string Text = "";
	int textLen = sqrt(key.length());
	for (int i = 0; i < textLen; i++)
	{
		int x = TextVector[i];
		char c = charMap[x];
		Text += c;
	}
	return Text;
}

string hill::decrypt(string etext)
{
	if (!isInvertible)
	{
		cout << "this key is not invertible,Text cannot be decrypted" << endl;
		return "";
	}
	int textLen = etext.length();
	int keyLen = key.length();
	if (textLen != sqrt(keyLen))
	{
		cout << "Invalid text.this key can only decrypt a text of length " << sqrt(keyLen) << ", Decryption failed";
		return "";
	}
	this->eText = etext;
	transform(this->eText.begin(), this->eText.end(), this->eText.begin(), tolower);
	createTextVector(eText);
	vector<int> decryptedTextVector;
	decryptTextVector(decryptedTextVector);
	this->text = getVecText(decryptedTextVector);
	return text;
}

void hill::getInverseMatrix()
{
	inverseKeyMatrix.resize(sqrt(key.length()), vector<int>(sqrt(key.length()), 0));
	int len = sqrt(key.length());
	int det = getMatDet(keyMatrix, len);
	if (det == 0)
	{
		cout << "Note: this key is not invertible, decryption is not possible." << endl;
		return;
	}

	int invDet = getMatDetInv(det);
	if (!isInvertible)
	{
		cout << "Note: this key is not invertible, decryption is not possible." << endl;
		return;
	}

	vector<vector<int>> adjointMat;
	adjointMat.resize(len, vector<int>(len, 0));
	getAdjointMatrix(keyMatrix, adjointMat);

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			inverseKeyMatrix[i][j] = adjointMat[i][j] * invDet;
			inverseKeyMatrix[i][j] %= 26;
		}
	}
}

int hill::getMatDet(vector<vector<int>>matrix, int Size)
{
	int det = 0;
	if (Size == 1)
		return matrix[0][0];

	vector<vector<int>> coMat;
	coMat.resize(Size, vector<int>(Size));

	int posNeg = 1;
	for (int i = 0; i < Size; i++)
	{
		getCofactorMat(matrix, coMat, 0, i, Size);
		det += posNeg*matrix[0][i] * getMatDet(coMat, Size - 1);
		posNeg *= -1;
	}
	return det;
}

int hill::getMatDetInv(int det)
{
	while (det < 0){
		det += 26;
	}
	det %= 26;
	int detInv = -1;
	for (int i = 1; i < 26; i++)
	{
		if ((det*i - 1) % 26 == 0)
		{
			detInv = i;
			isInvertible = true;
			break;
		}
	}
	return detInv;
}

void hill::getAdjointMatrix(const vector<vector<int>>& keyMatrix, vector<vector<int>>& adjointMatrix)
{
	int Size = sqrt(key.length());
	vector<vector<int>> coMatrix;
	coMatrix.resize(Size, vector<int>(Size, 0));
	int posNeg = 1;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if ((i + j) % 2 == 0)
				posNeg = 1;
			else
				posNeg = -1;
			getCofactorMat(keyMatrix, coMatrix, i, j, Size);
			adjointMatrix[i][j] = getMatDet(coMatrix, Size - 1)*posNeg;
		}
	}
	getMatrixTrans(adjointMatrix, Size);

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			while (adjointMatrix[i][j] < 0)
			{
				adjointMatrix[i][j] += 26;
			}
			adjointMatrix[i][j] %= 26;
		}
	}
}

void hill::getCofactorMat(const vector<vector<int>>&matrix, vector<vector<int>>& coMatrix, int row, int col, int Size)
{
	int i = 0, j = 0;
	for (int k = 0; k < Size; k++)
	{
		for (int e = 0; e < Size; e++)
		{
			if (k != row && e != col)
			{
				coMatrix[i][j] = matrix[k][e];
				j++;
				if (j == (Size - 1))
				{
					i++;
					j = 0;
				}
			}
		}
	}
}

void hill::getMatrixTrans(vector<vector<int>>&adjointMatrix, int Size)
{
	int index = Size - 1;
	for (int i = 0; i < Size; i++){
		for (int j = i; j < Size; j++)
		{
			int temp = adjointMatrix[i][j];
			adjointMatrix[i][j] = adjointMatrix[j][i];
			adjointMatrix[j][i] = temp;
		}
	}
}

void hill::decryptTextVector(vector<int>& decryptedTextVector)
{
	int rows, cols;
	rows = cols = eText.length();
	for (int i = 0; i < rows; i++)
	{
		int x = 0;
		for (int j = 0; j < cols; j++)
		{
			x += (textVector[j] * inverseKeyMatrix[i][j]);
		}
		x %= 26;
		decryptedTextVector.push_back(x);
	}
}
