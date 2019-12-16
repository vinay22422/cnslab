/*
Program: RSA client
Author: Gangadhara Shetty P J
*/
# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;
char buffer[100];
int connectToServer()
{
	int p=1235;char ip[50]="127.0.0.1";
    int sock = socket(AF_INET, SOCK_STREAM, 0);//ipv4,tcp,protocol
    struct sockaddr_in addr = {AF_INET, htons(p), inet_addr(ip)};
    while(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0 ){
        
    }
    
    return sock;
}
int powModN(int num,int p,int n)
{
	int res=1;
	for(int i=0; i<p; i++)
        res = (res * num) % n;
	return res;
}
int gcd(int p, int q)
{
    if(q==0)    return p;
    gcd(q, p%q);
}

int GetInverseDeterminant(int e ,int fi){ 
	for(int i=1;i<fi;i++)
		if((i*e)%fi==1) return i;
	return -1;
}
void generateKey(int p, int q, int &e, int &d, int &n)
{
	n = p*q;
    int fi=(p-1)*(q-1);
    for(int i=2;i<fi; i++)
        if(gcd(i, fi) ==1)
            {e=i;  break;}
	d = GetInverseDeterminant(e, fi);
	cout<<"Public key of server: ("<<e<<"|"<<n<<")"<<endl;
	cout<<"Private key of server: ("<<d<<"|"<<n<<")"<<endl;
}
int main()
{
    int  p, q, e, d, n, C;
    int sock = connectToServer();

    cout << "\nEnter two prime numbers : "; 
	cin >> p >> q;
    generateKey(p, q, e, d, n);
	
	int s[2]={e,n};
    send(sock,s , sizeof(s), 0); 
    cout << "\nSent Public key to server." << endl;

    recv(sock, &C, sizeof(C), 0);  //reading using integer
    cout << "\nCiphertext received from server : " << C << endl;

    int M = powModN(C, d, n); 
    cout << "\nDecrypted Text : " << M << endl << endl;

}

/*
Enter two prime numbers : 11 7                                                        
d= 43                                                                                                                                                                       
Sent Public key to server.                                                                                                                                                  
Ciphertext received from server : 64                                                                                                                                        
Decrypted Text : 36
*/