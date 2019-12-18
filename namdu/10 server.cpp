/*
Program: RSA server
Author: Gangadhara Shetty P J
*/
# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;
char buffer[100];
int createServer()
{
    int p=1235;
    int sersock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(p), INADDR_ANY};
    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
    cout << "\nServer Online. Waiting for client...." << endl;
    listen(sersock, 15);
    int sock = accept(sersock, NULL, NULL);
    cout << "Connection Established." << endl;
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
    int  e,n, M;
    int sock = createServer();
    int s[2];
    recv(sock, s, sizeof(s), 0);
  
    e=s[0],n=s[1];
    cout << "\nPublic key received from client : (" << e << ", " << n << ")" << endl;

    cout << "\nEnter message(M<" << n << ") to encrypt : "; 
    cin >> M;

    int C = powModN(M, e, n);
    cout << "\nEncrypted Text : " << C << endl;
    send(sock, &C, sizeof(C), 0);
    cout << "\nSent ciphertext to client." << endl << endl;

}
/*
Public key received from client : {7, 77}                                                                                                                                   
Enter message(M<77) to encrypt : 36                                                                                                                                         
Encrypted Text : 64                                                                                                                                                         
Sent ciphertext to client.
*/