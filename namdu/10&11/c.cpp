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

int gcd(int p,int q){
if (q==0) return p;
return gcd(q,p%q);

}
void genk(int p,int q,int n,int& e,int & d){
int i,fi=(p-1)*(q-1);
for(i=2;i<fi;i++){
    if(gcd(i,fi)==1)
        {e=i;break;}

}
cout<<"\ne="<<e;
for(i=1;i<fi*1000;i++){
    if(((i*e)%fi)==1)
        {d=i;break;}

}
cout<<"\nd="<<e;

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
int p,q,n,e,d;
cout<<"enter p q\n";
cin>>p;cin>>q;
n=p*q;
genk(p,q,n,e,d);
int s[2]={e,n};

send(sock,s,sizeof(s),0);
int m;
recv(sock,&m,sizeof(m),0);
/*cout<<"\nrecived m\n"<<m;
cout<<"\n msg is   "<<powmodn(m,d,n);
*/
int arr[m];
recv(sock,arr,sizeof(arr),0);
cout<<"\n\nrecived\n\n";
for(int i=0;i<m;i++){

cout<<arr[i]<<" ";

}
cout<<"\n\ndecrypted\n\n";
for(int i=0;i<m;i++){

cout<<(char)powmodn(arr[i],d,n);

}




}


