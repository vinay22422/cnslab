#include<bits/stdc++.h>
#include<arpa/inet.h>
#define BIT_SIZE 16

using namespace std;

int se(){
    int ssock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in a={AF_INET,htons(1234),INADDR_ANY};

    bind(ssock,(struct sockaddr *)&a,sizeof(a));
    listen(ssock,15);
    int sock=accept(ssock,NULL,NULL);
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
int e,n,s[2],m=3;
recv(sock,s,sizeof(s),0);
e=s[0],n=s[1];
/*
cout<<"\ne and n"<<e<<"-- "<<n<<"\nsending "<<m;
m=powmodn(m,e,n);
send(sock,&m,sizeof(m),0);
cout<<"\n\nsending"<<m;
*/
cout<<"\n\nenter msg to send\n\n";
string msg;
cin>>msg;
int len=msg.length();
send(sock,&len,sizeof(len),0);
//Sleep(2);
int arr[len];
cout<<"\nem is\n";
for(int i=0;i<len;i++){
arr[i]=powmodn((int)msg[i],e,n);
cout<<arr[i];

}
send(sock,arr,sizeof(arr),0);

}
