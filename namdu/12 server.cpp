/*
Program: RSA Key Exchange server
Author: Gangadhara Shetty P J
*/
# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;
char buffer[100];
int createServer(int port)
{
    int sersock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};
    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
    listen(sersock, 5);
    int sock = accept(sersock, NULL, NULL);
    return sock;
}
int powModN(int num,int p,int n)
{
	int res=1;
	for(int i=0; i<p; i++)
        res = (res * num) % n;
	return res;
}

int GetInverseDeterminant(int e ,int fi){ 
	for(int i=1;i<fi;i++)
		if((i*e)%fi==1) return i;
	return -1;
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
	cout<<"Public key of server: ("<<e<<"|"<<n<<")"<<endl;
	cout<<"Private key of server: ("<<d<<"|"<<n<<")"<<endl;
}

int main()
{
    int port=1234, sid, sid1, cid, nonces,nonces1, noncec, pue, ns, nc, pus, prs, key, p, q;
    int sock = createServer(port);
	srand(time(NULL));
	int s[2];
	recv(sock, s, sizeof(s), 0);
	pue=s[0],nc=s[1];
	cout<<"received pue|n "<<s[0]<<s[1]<<endl;
	
	cout << "\n2. Enter two prime numbers : "; 
	cin >> p >> q;
	
	generateKey(p, q, pus, prs, ns);
	s[0]=pus,s[1]=ns;
	
	cout<<"Sending pue|n "<<s[0]<<s[1]<<endl;
	send(sock, s, sizeof(s), 0);
	
	cout<<"3. Enter server ID: ";
	cin>>sid;
	nonces = rand()%100;

	s[0]=powModN(sid, pue,nc),s[1]=powModN(nonces, pue,nc);
	send(sock, s, sizeof(s), 0);
	cout<<"sending plain sid|nonces "<<sid<<"|"<<nonces<<endl;
	cout<<"sending encrypted sid|nonces "<<s[0]<<s[1]<<endl;
	
	recv(sock, s, sizeof(s), 0);
	nonces1=s[0], noncec=s[1];
	nonces1 = powModN(nonces1,prs,ns);
	noncec= powModN(noncec, prs,ns);
	cout<<"received encrypted nonces|noncec from client "<<s[0]<<s[1]<<endl;
	cout<<"received decrypted nonces|noncec from client "<<nonces1<<"|"<<noncec<<endl;
	if(nonces!=nonces1)
		{	cout<<"Nonce din't match"<<endl;	exit(0);	}
	else	cout<<"Client Authenticated"<<endl;
	
	int s1=powModN(noncec, pue, nc);
	send(sock, &s1, sizeof(s1), 0);
	cout<<"Sending plain noncec "<<noncec<<endl;
	cout<<"Sending encrypted noncec "<<s<<endl;
	
	cout<<"4. Enter the key: ";
	cin>>key;
	cout<<"Sending plain key "<<key<<endl;
	key = powModN(key, prs, ns);
	key = powModN(key, pue, nc);
	
	s1=key;
	send(sock, &s1, sizeof(s1), 0);
	cout<<"Sending encrypted key "<<buffer<<endl;
  
}

/*
received pue|n 7477|18281
3. Enter server (e|n): 4551|13231  
4. Enter server (d): 1951   
5. Enter server ID: 29    
sending plain sid|nonces 29|28       
sending encrypted sid|nonces 4168|11880  
received encrypted nonces|noncec 6840|6840  
received decrypted nonces|noncec 28|28
Sending plain noncec 28 
Sending encrypted noncec 28
6. Enter the key: 454
Sending plain key 454                                                                                                                                                                                              
Sending encrypted key 5502 
*/