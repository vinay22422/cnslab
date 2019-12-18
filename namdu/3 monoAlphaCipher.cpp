/*********************************************************************************
Perform encryption and decryption using mono-alphabetic cipher.
The program should support the following:
i.  Construct an input file named plaintext.txt (consisting of 1000 alphabets,
    without any space or special characters)
ii. Compute key space (Permutation of set of all letters appeared in plaintext.txt:
    there are n! permutations of a set of n elements)
iii.Encrypt the characters of plaintext.txt using any one key from (ii)
    and store the corresponding ciphertext characters in ciphertext.txt
iv. Compute the frequency of occurrence of each alphabet in both plaintext.txt
    and ciphertext.txt and tabulate the results as follows
***********************************************************************************/

#include<bits/stdc++.h>

using namespace std;

char uniqtext[26]; // Global variable
string plaintext;
int frequency_count[256],noofuniqc=0;

/* read plain text from plaintext.txt file */
string readPlainText()
{
	ifstream fin;
	string ptext;

	fin.open("plaintext.txt");
	fin >> ptext;
	fin.close();

	return ptext;
}

/* write cipher text to ciphertext.txt file */
void writecipherText(string ctext)
{
	ofstream fout;
	fout.open("ciphertext.txt");
	fout << ctext;
	fout.close();
}

/* function to find all possible permutation */

void permute( vector<string>& keys, string text) // keyspace is passed by reference &&&&&&&&&&&&&&&&&
{
	sort( text.begin(), text.end());
// next_permutation is a readily available function to generate permutation of the string
	while(next_permutation(text.begin(), text.end()))
	{
	// cout<<text<<endl;
		keys.push_back(text);
	}
}

vector<string> genKeySpace(string plaintext)
{
	set<char> uniqSet;
	vector<string> keyspace; // contains all possible permutation of letters in plaintext
	int count = 0;

	/* store all the unique letters of plain text in uniqSet */
	for(int i=0; i < plaintext.length(); i++)
	{
		uniqSet.insert(plaintext[i]);
	}

	/* copy uniqSet to uniqtext char array */
	for(set<char>::iterator it = uniqSet.begin(); it != uniqSet.end(); it++)
	{
		uniqtext[count++] = (*it);
		frequency_count[*it]++;
	}
	noofuniqc=uniqSet.size();
string text(uniqtext);
	permute(keyspace,text); //& maribeda
	return keyspace;
}

/* create cipher text using key */
string encrypt(string unique, string key)
{
	string plaintext = readPlainText();
	string ciphertext = "";

	for(int i=0; i < plaintext.length(); i++)
	{
		//int idx = unique.find(plaintext[i]);ciphertext += key[idx];
		ciphertext += key[unique.find(plaintext[i])];


	}
	return ciphertext;
}

/* frequency = (no of occurance of a character / length of text) */
/* show frequency of all characters of plain text and cipher text */
void showFrequency(string pt , string ct)
{
    float length = pt.length();
    cout<<"Frequency\tUnique Characters\tChoosen Key"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
	// Frequency / Length * => percentage of occurance of the character in the entire string
	for(int i=0; i<noofuniqc;i++)
		if(frequency_count[ pt[i] ] !=-1)
		{
			cout << frequency_count[ pt[i] ] / length * 100 << "\t\t\t" << pt[i] << "\t\t" << ct[i] << endl;
			frequency_count[ pt[i] ] =-1;


		}
}

/* show frequency of only unique characters of plain text and cipher text */
/*
void showFrequency(string pt , string ct){
	map<char , char> mPlain ; // frequency of each character of plain text
	map<char , char> mCipher ; // frequency of each character of plain text
	map<char , char> pc;

	for(int i =0 ;i < pt.length() ; i++){
		mPlain[pt[i]]++ ;
		mCipher[ct[i]]++ ;
		pc[pt[i]] = ct[i];
	}

	cout<<"Frequency\t\tPlaintext Character\t\tCiphertext character" <<endl;
	cout<<"=========\t\t===================\t\t====================" <<endl;
	for(int i =0 ;i < pc.size() ; i++){
		cout<< (float)mCipher[pc[uniqtext[i]]]/ct.length() << "\t\t\t" << uniqtext[i] << "\t\t\t" << pc[uniqtext[i]] << endl ;
	}
}
*/

int main()
{
	srand(time(NULL)) ;

	plaintext = readPlainText() ;
	cout<<"Plain text = \t" << plaintext << endl;


	vector<string> keys = genKeySpace(plaintext);
	//string key = keyspace[rand()%keyspace.size()]; 	vector has size() function
        //cout<<"enter key\n";
        string ut(uniqtext);
	cout<<"Unique chars = \t" << ut <<endl;

	//cout<<"enter key with unique letter for each\n";
	//cout<<"Chosen key = \t" << key <<endl;
	string key;
	//cin>>key;
	key=keys[rand()%keys.size()];
	cout<<"Choosen Key:\t"<<key<<endl;

	string ciphertext = encrypt(ut , key) ;
	writecipherText(ciphertext) ;
	showFrequency(plaintext , ciphertext) ;
}


/****************************** OUTPUT-1 ****************************************
Plain text =    HelloWorld
Unique chars =  HWdelor
Chosen key =    WHoedrl

Frequency               Plaintext Character             Ciphertext character
=========               ===================             ====================
0.1                             H                               W
0.1                             e                               e
0.3                             l                               d
0.3                             l                               d
0.2                             o                               r
0.1                             W                               H
0.2                             o                               r
0.1                             r                               l
0.3                             l                               d
0.1                             d                               o

/****************************** OUTPUT-2 ****************************************
Plain text =    workisworship
Unique chars =  hikoprsw
Chosen key =    rphskowi

Frequency               Plaintext Character             Ciphertext character
=========               ===================             ====================
0.153846                                w                               i
0.153846                                o                               s
0.153846                                r                               o
0.0769231                               k                               h
0.153846                                i                               p
0.153846                                s                               w
0.153846                                w                               i
0.153846                                o                               s
0.153846                                r                               o
0.153846                                s                               w
0.0769231                               h                               r
0.153846                                i                               p
0.0769231                               p                               s
***********************************************************************************/

