# include <bits/stdc++.h>
# include <arpa/inet.h>
using namespace std;

int createServer()
{
int sersock = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in addr = {AF_INET, htons(1234), INADDR_ANY};
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
int main()
{
int  e,n, len;
int sock = createServer();
string message;
int s[2];
recv(sock, s, sizeof(s), 0);
e=s[0],n=s[1];
cout << "\nddddPublic key received from client : (" << e << ", " << n << ")" << endl;
cout << "\nEnter message to be send : ";
cin >> message;
len = message.length();
send(sock, &len, sizeof(len), 0);

cout << "\nEncrypted Message : ";
for(int i=0; i<message.length(); i++)
{
int C = powModN(message[i], e, n);
send(sock, &C, sizeof(C), 0);
cout<<C<<" ";
}
cout<<endl<<"Message Sent"<<endl;
}
/*
Public key received from client : {3, 13231}
Enter message to be send : cnslab
Encrypted Message :
4436 7900 12541 2767 12965 1791
Message Sent
*/