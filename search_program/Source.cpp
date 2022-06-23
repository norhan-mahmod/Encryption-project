#include<iostream>
#include<math.h>
#include<string>
using namespace std;
char table[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
int key[2][2]; //(e which is encryption key )
int key_inverse[2][2]; //(inverse of e which is decription key)
string plaintext,ciphertext="";
int plaintext_code[2];
int det;
bool check_key_invertible()
{

	det = (key[0][0] * key[1][1]) - (key[0][1] * key[1][0]);
	if (det % 26 != 0)
	{
		while (det > 26)
			det -= 26;
		return true;
	}
	else
		return false;
}
void read_encryption_key()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> key[i][j];
		}
	}
}
int indexOf(char x, char y[])
{
	for (int i = 0; i < 26; i++)
	{
		if (x == y[i])
		{
			return i;
			break;
		}
	}
}
char char_of_index(int x, char y[])
{
	return y[x];
}
void encryption_calculation(int x[])
{
	for (int m = 0; m < 2; m++)
	{
		int enc = 0;
		for (int n = 0; n < 2; n++)
		{
			enc += (x[n] * key[n][m]);
		}
		while (enc > 26)
			enc = enc - 26;
		ciphertext += char_of_index(enc, table);
	}
}
void encryption()
{
	cout << "enter the encryption key in a form of 2*2 matrix" << endl;
	read_encryption_key();
	cout << "enter the plaintext" << endl;
	cin >> plaintext;
	if (check_key_invertible() == false)
	{
		cout << "the encryption key is not allowed to use because it hasn't an inverse";
	}
	else
	{
		key_inverse[0][0] = key[1][1];
		key_inverse[1][0] = -key[1][0];
		key_inverse[0][1] = -key[0][1];
		key_inverse[1][1] = key[0][0];

		int f = 1;
		while ((det * f) % 26 != 1)
			f++;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				key_inverse[i][j] *= f;
				while (key_inverse[i][j] < 0)
					key_inverse[i][j] = key_inverse[i][j] + 26;
				while (key_inverse[i][j] > 26)
					key_inverse[i][j] = key_inverse[i][j] - 26;
			}
		}
		cout << "the inverse of encryption key is" << endl;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				cout << key_inverse[i][j] << " ";
			}
			cout << endl;
		}
		for (int j = 0, i = 0; j < plaintext.length(); j++)
		{
			plaintext_code[i] = indexOf(plaintext[j], table);
			if (i == 0)
				i += 1;
			else
			{
				encryption_calculation(plaintext_code);
				i = 0;
			}

		}
		cout << "the ciphertext is  " << ciphertext << endl;

	}
	
}
void decryption()
{

}
void main()
{
	char a;
	cout << "if you want to encrypt plaintext please press 'e' " << endl << " but if you want to decrypt ciphertext please press 'd' " << endl;
	cin >> a;
	if (a == 'e')
		encryption();
	else if (a == 'd')
		decryption();
}