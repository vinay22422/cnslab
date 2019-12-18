#include<bits/stdc++.h>
#include<arpa/inet.h>
#define BIT_SIZE 16

using namespace std;
int se(){
    int sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in a={AF_INET,htons(1234),inet_addr("127.0.0.1")};
    while(connect(sock,(struct sockaddr* )&a,sizeof(a)));

    return sock;
}

int powmodn(int n,int p,int m){
int res=1;
for (int i=0;i<p;i++)
    res=(res*n)%m;

    return res;
}
int main()
{
int sock=se();

int q,alf,xb,ya,yb;
cout<<"\nenter q alfa xb\n";
cin>>q;cin>>alf;cin>>xb;
yb=powmodn(alf,xb,q);
send(sock,&yb,sizeof(yb),0);
recv(sock,&ya,sizeof(ya),0);

cout<<"\n\nkey is ="<<powmodn(ya,xb,q);


/*
int pc=101,qc=103,nc,ec,dc,es,ns;
cout<<"enter p q\n";
//cin>>pc;cin>>qc;
nc=pc*qc;
genk(pc,qc,nc,ec,dc);


int s[2]={ec,nc};

send(sock,s,sizeof(s),0);



recv(sock,s,sizeof(s),0);
es=s[0],ns=s[1];
cout<<"\n\nes ns recived"<<es<<" "<<ns<<"\n\n";

int cnounce2=23,snounce;

recv(sock,s,sizeof(s),0);
snounce=s[0];
snounce=powmodn(snounce,dc,nc);
cout<<"\ngot snounce="<<snounce<<endl<<" encr noun"<<s[0]<<endl;
s[0]=powmodn(snounce,es,ns);
s[1]=powmodn(cnounce2,es,ns);

send(sock,s,sizeof(s),0);
int t;
recv(sock,&t,sizeof(t),0);

recv(sock,&t,sizeof(t),0);

t=powmodn(t,dc,nc);
t=powmodn(t,es,ns);

cout<<"success fully done k="<<t;


*/


}


