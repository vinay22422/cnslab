#include<bits/stdc++.h>
#include<arpa/inet.h>
#define BIT_SIZE 16

using namespace std;
int gcd(int p,int q){
if (q==0) return p;
return gcd(q,p%q);

}
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
void genk(int p,int q,int n,int& es,int & ds){

    int i,fi=(p-1)*(q-1);
    for(i=2;i<fi;i++){
        if(gcd(i,fi)==1)
            {es=i;break;}

    }
    cout<<"\ne="<<es;
    for(i=1;i<fi*1000;i++){
        if((i*es)%fi==1)
            {
            	ds=i;
            	break;
            }
    }
cout<<"\nd="<<ds;
}

int main()
{
int sock=se();
int ec,nc,s[2],m=3,ps=107,qs=131,ns,ds,es;
recv(sock,s,sizeof(s),0);
ec=s[0],nc=s[1];
cout<<"\n\nec nc recived\n\n"<<ec<<"  "<<nc<<"\nenter p q \n";
//cin>>ps;cin>>qs;
/*
cout<<"\ne and n"<<e<<"-- "<<n<<"\nsending "<<m;
m=powmodn(m,e,n);
send(sock,&m,sizeof(m),0);
cout<<"\n\nsending"<<m;
*/
ns=ps*qs;
genk(ps,qs,ns,es,ds);
cout<<"\n\nsending es ns "<<es<<" "<<ns;
int s1[2]={es,ns};

send(sock,s1,sizeof(s1),0);
cout<<"\n\nsent es ns "<<es<<" "<<ns;

int snounce1=13,sid=4,k=6;
int esnounce,esid,ek;

esnounce=powmodn(snounce1,ec,nc);
esid=powmodn(sid,ec,nc);
s[0]=esnounce;s[1]=esid;

cout<<"\nsending    "<<s[0]<<" \n\n";
send(sock,s,sizeof(s),0);

recv(sock,s,sizeof(s),0);
s[0]=powmodn(s[0],ds,ns);
s[1]=powmodn(s[1],ds,ns);
if(snounce1!=s[0]){
    cout<<"\nfailed    "<<s[0]<<" was got";
    exit(0);
}
int ecnounce=powmodn(s[1],ec,nc);
send(sock,&ecnounce,sizeof(ecnounce),0);

ek=powmodn(k,ds,ns);

ek=powmodn(ek,ec,nc);
send(sock,&ek,sizeof(ek),0);










}
