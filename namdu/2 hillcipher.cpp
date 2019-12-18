
#include<bits/stdc++.h>
using namespace std;
int keyMatrix[100][100], inverseMatrix[100][100];
int order;

string FormatMessage(string& message)
{
    for(int i=0;i<message.length();i++)
        if(message[i] == ' ')   // add conditions here for any other special characters
            message.erase(i, 1);




    if(message.length()%order)
        message += "x";
    if(message.length()%order)
        message += "x";
    return message;
}

int GetInverseDeterminant(int R , int D = 26){ //R is the remainder or determinant
	int i=1,a=1;
	for(i=1;i<(R*1000);i++)
    {
        cout<<"dv";
        if((R*i)%D == 1){
            cout<<"\n\n"<<R<<i;
            return i;}
    }
}

int GetDeterminant()
{
    int determinant = 0;
    if(order==2)
        determinant = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
    else
        for(int i = 0; i < 3; i++)
            determinant = keyMatrix[0][0]*(keyMatrix[1][1]*keyMatrix[2][2] - keyMatrix[1][2]*keyMatrix[2][1])  - keyMatrix[0][1]*(keyMatrix[1][0]*keyMatrix[2][2] - keyMatrix[2][0]*keyMatrix[1][2] ) + keyMatrix[0][2]*(keyMatrix[1][0]*keyMatrix[2][1] - keyMatrix[1][1]*keyMatrix[2][0]);
    if(determinant<0)
        determinant = 26 - (int(-determinant)%26);
    else
        determinant = int(determinant)%26;

    determinant = GetInverseDeterminant(determinant, 26);

    return determinant;
}

string Multiply(string msg_group, int matrix[][100])
{
    string result;
    for(int i=0; i<order; i++)
    {
        float val = 0 ;
        for(int j=0;j<order; j++)
            val = val +  (msg_group[j] - 'a') * matrix[j][i];

        if(val>=0)
            val =  int(val)%26 + 'a'; 				//WE NEED TO USE INT
        else
            val = 26 - (int(-val)%26) + 'a';

        result += char(int(val));							//WE NEED TO USE INT BCOZ VAL IS FLOAT
    }
    return result;
}

void FindInverse(int determinant)
{
    if(order==2)
    {
        inverseMatrix[0][0] = keyMatrix[1][1]*determinant;
        inverseMatrix[1][1] = keyMatrix[0][0]*determinant;
        inverseMatrix[0][1] = -keyMatrix[0][1]*determinant;
        inverseMatrix[1][0] = -keyMatrix[1][0]*determinant;
    }
    else
        for(int j=0; j<order; j++)
            for(int i=0; i<order; i++)
                inverseMatrix[i][j] = ((keyMatrix[(j+1)%3][(i+1)%3] * keyMatrix[(j+2)%3][(i+2)%3])
                    -  (keyMatrix[(j+1)%3][(i+2)%3] * keyMatrix[(j+2)%3][(i+1)%3]))*determinant;

	//applying mod!
	 for(int j=0; j<order; j++)
            for(int i=0; i<order; i++)
                if(inverseMatrix[i][j] < 0 )	inverseMatrix[i][j] = 26 - int(-inverseMatrix[i][j])%26;
				else inverseMatrix[i][j] = int(inverseMatrix[i][j]) %26;
}

string Encrypt(string message)
{
    string enc_msg;
    for(int i=0;i<message.length();i+=order)
    {
        string msg_group = message.substr(i, order);
        msg_group = Multiply(msg_group, keyMatrix);
        enc_msg += msg_group;
    }
    return enc_msg;
}

string Decrypt(string message)
{
    string msg;
    FindInverse(GetDeterminant());
    for(int i=0;i<message.length();i+=order)
    {
        string msg_group = message.substr(i, order);
        msg_group = Multiply(msg_group, inverseMatrix);
        msg += msg_group;
    }
    return msg;
}

int main()
{
	string message;
    cout << "Enter the key matrix order: ";
    cin >> order;

	cout << "Enter the keys:";
	for(int i = 0; i < order; i++)
	    for(int j=0;j<order; j++)
	        cin >> keyMatrix[i][j];
    cin.get();
    string t;
    getline(cin, t);
    cout<<"Enter a message to be encrypted: ";
    getline(cin, message);                      //to read space imppppppppppppppppppppp
    //cin>>message;

    FormatMessage(message);
    string enc_msg = Encrypt(message);
    string dec_msg = Decrypt(enc_msg);
    cout<<"Message: "<<message<<endl;
    cout<<"Encrypted Message: "<<enc_msg<<endl;
    cout<<"Decrypted Message: "<<dec_msg<<endl;

	return 0;
}

/*
-------------
Sample Output
-------------
Enter the key matrix order: 3
Enter the keys:17 17 5
21 18 21
2 2 19
Enter a message to be encrypted: paymoremoney
Message: paymoremoney
Encrypted Message: rrlmwbkaspdh
Decrypted Message: paymoremoney

*/
