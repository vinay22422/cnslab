/*
Program: RSA Key Exchange client
Author: Gangadhara Shetty P J
*/
# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;
char buffer[100];
int connectToServer()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(1234), inet_addr("127.0.0.1")};
    while(connect(sock, (struct sockaddr *) &addr, sizeof(addr)));
    return sock;
}
int GetInverseDeterminant(int e ,int fi){ 
	for(int i=1;i<fi;i++)
		if((i*e)%fi==1) return i;
	return -1;
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
void generateKey(int p, int q, int &e, int &d, int &n)
{
	n = p*q;
    int fi=(p-1)*(q-1);
    for(int i=2;i<fi; i++)
        if(gcd(i, fi) ==1)
            {e=i;  break;}
	d = GetInverseDeterminant(e, fi);
	cout<<"Public key of client: ("<<e<<"|"<<n<<")"<<endl;
	cout<<"Private key of client: ("<<d<<"|"<<n<<")"<<endl;
}
int main()
{
    int  pue, pre, pus, sid, nonces, noncec, cid, noncec1, ns, nc, p, q;
    int sock = connectToServer();
	srand(time(NULL));
	
	cout << "\n1. Enter two prime numbers : "; 
	cin >> p >> q;
	
	generateKey(p, q, pue, pre, nc);
	int s[2]={pue,nc};
	
	cout<<"Sending pue|n "<<buffer<<endl;
	send(sock, s, sizeof(s), 0);
	
	recv(sock, s, sizeof(s), 0);
	pus=s[0],ns=s[1];
	cout<<"received server pus|n "<<buffer<<endl;
	
	
	recv(sock, s, sizeof(s), 0);
	sid=s[0],nonces=s[1];
	nonces = powModN(nonces, pre, nc);
	sid=powModN(sid, pre, nc);
	cout<<"received encrypted sid|nonces "<<s[0]<<s[1]<<endl;
	cout<<"received decrypted sid|nonces "<<sid<<"|"<<nonces<<endl;
	
	noncec = rand()%100;
	s[0]=powModN(nonces, pus, ns), s[1]=powModN(noncec, pus, ns);
	send(sock, s, sizeof(s), 0);
	cout<<"Sending plain nonces|noncec "<< nonces<<"|"<<noncec<<endl;
	cout<<"Sending encrypted nonces|noncec "<<s[0]<<s[1]<<endl;
	
	int s1;
	recv(sock, &s1, sizeof(s1), 0);

	noncec1 = s1;
	noncec1 = powModN(noncec1, pre, nc);
	cout<<"received encrypted noncec "<<s1<<endl;
	cout<<"received decrypted noncec "<<noncec1<<endl;
	if(noncec!=noncec1)
		{	cout<<"Nonce din't match"<<endl;	exit(0);	}
	else	cout<<"Server Authenticated"<<endl;
	
	recv(sock, &s1, sizeof(s1), 0);
	cout<<"received encrypted key "<<s1<<endl;
	int key = powModN(s1, pre, nc);
	key = powModN(key, pus, ns);
	cout<<"received decrypted key "<<key<<endl;
	return 0;
}

/*
1. enter client (e|n): 7477|18281                                                                                                                                                                                  
Sending pue|n 7477|18281   
2. enter client (d): 14413 
received server pus|n 4551|13231 
received encrypted sid|nonces 4168|11880                                                                                                                                                                           
received decrypted sid|nonces 29|28 
Sending plain nonces|noncec 28|28       
Sending encrypted nonces|noncec 6840|6840  
received encrypted noncec 6726  
received decrypted noncec 14381
received encrypted key 5502  
received decrypted key 454
*/