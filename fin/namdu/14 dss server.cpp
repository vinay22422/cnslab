#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SA struct sockaddr
#define typeL long long
using namespace std;

typeL powermod(typeL a, typeL b, typeL  q)
{
    typeL res=1;
    for(typeL i=0;i<b;i++)
        res=(res*a)%q;
    return res;
}

typeL randno(typeL m, typeL n)  //range = (m,n)
{
    return rand()%(n-m-1)+m+1;
}

typeL mod(long m, typeL n)  //m%n
{
    return (m>=0)?m%n:mod(m+n,n);
}

typeL inverse(typeL num, typeL n)
{
    typeL i=0, p[1000],q[1000],t, r=num, d=n;
    if(d%r==0) return 1;
    do
    {
        t=d;
        q[i]=d/r;   
        d=r;
        r=t%r;
        if(i==0 || i==1) p[i]=i;
        else p[i]=mod(p[i-2]-p[i-1]*q[i-2],n);
        //cout<<t<<" = "<<q[i]<<"("<<d<<") + "<<r<<"\tP"<<i<<" = "<<p[i]<<endl;
        i++;    
    
    } 
    while(r!=0);
    p[i]=mod( (p[i-2]-p[i-1]*q[i-2]) , n);
        return p[i];
}

typeL H(typeL M)
{
    return ( M^1234 ); //hash key=1234 
}

int main()
{
    srand(time(NULL));
        int port;
        char addr[100]={'\0'};
        cout<<"Address  : "; scanf("%s",addr);
        cout<<"Port     : "; cin>>port;

    // ****Connection
    struct sockaddr_in server={AF_INET, htons(port), inet_addr(addr)}, client;
        int sockfd = socket(AF_INET, SOCK_STREAM,0);
        bind(sockfd, (SA*)&server, sizeof(server));
        listen(sockfd,1);
        socklen_t len=sizeof(client);
        int connfd = accept(sockfd,(SA*)&client,&len);
        // ****Connection Established
    
    typeL p,q,r,s,k,g,M,h,x,y,hashval;

    cout<<"p = "; cin>>p;
    cout<<"q = "; cin>>q;
    cout<<"M = "; cin>>M;
    
    hashval=H(M);
    do{ 
        h=randno(1,p-1);    // 1 < h < (p-1)
        g=powermod(h,(p-1)/q,p);    // g > 1
    }while(g<=1);   // because condition: g>1

    x=randno(0,q);  //User private key, 0 < x < q
    y=powermod(g,x,p);  //User public key

    k=randno(0,q);  // 0 < k < q

    //Signing
    r=mod(powermod(g,k,p) , q); //f2() = (g^k mod p) mod q 
    s=mod(inverse(k,q)*( hashval + x*r ) , q);  //f1() = [invk ( H(M) + xr )] mod q

    cout<<"Signature = ("<<r<<" , "<<s<<")"<<endl;

    send(connfd, &hashval, sizeof(hashval), 0); 
    send(connfd, &r, sizeof(r), 0);
    send(connfd, &s, sizeof(s), 0); 
    send(connfd, &g, sizeof(g), 0); 
    send(connfd, &y, sizeof(y), 0); 

    cout<<"Packet sent with values"<<endl;
    cout<<"Hash : "<<hashval<<endl;
    cout<<"R    : "<<r<<endl;
    cout<<"S    : "<<s<<endl;
    cout<<"Y    : "<<y<<endl;
    cout<<"G    : "<<g<<endl;

        return 0;
}

/*************************************
Output:
Address  : 127.0.0.1
Port     : 8000
p = 67
q = 11
M = 56
Signature = (4 , 5)
Packet sent with values
Hash : 1258
R    : 4
S    : 5
Y    : 40
G    : 22
***************************************/