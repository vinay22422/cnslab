/*
Program: B Algorithm

*/

#include<bits/stdc++.h>
#define BIT_SIZE 16

using namespace std;
// nos will be big do like this only
int powModN(int num,int p,int n)
{
	int res=1;
	for(int i=0; i<p; i++)
	{
        res = (res * num)%n;
	}
	return res;
}

bool rabinMiller(int n)
{
	int k, q=n-1;
	for(k=0; q%2==0; k++, q/=2);

//to make sure we check for 4 different random nos
    for(int i=0; i<4; i++)
    {
        int a = rand()%(n-1)+1;
        if(powModN(a,q,n) == 1)	
			return true;
        for(int j=0; j<=k-1; j++)
            if(powModN(a, pow(2,j)*q, n) == n-1)
                return true;
	}
    return false;
}

int main()
{
    long long int s, p, q, n;
    string bits="";
	srand(time(NULL));
    cout<<"Enter P, Q and Seed value: ";
    cin>>p>>q>>s;
    n = p*q;
    s=(s*s)%n;
	cout<<"bits generated: ";
    for(int i=0;i<BIT_SIZE;i++)
        s=(s*s)%n, bits+=(char)(s%2+'0'), cout<<s%2<<" "; //cout here is  for dubbugging...
    int num = bitset<BIT_SIZE>(bits).to_ulong();  //memorize u long
    cout<<endl<<"Random Number: "<<num<<endl;
	cout<<"Rabin Miller test: ";
    if(rabinMiller(num))
		cout<<"InConclusive"<<endl;
	else
		cout<<"Composite"<<endl;
	
    
}
/*
output:
Enter P, Q and Seed value: 7 11 7
bits generated: 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1
Random Number: 4369
Rabin Miller test: InConclusive


2047=23 * 89

First, choose two large prime numbers, p and
q, that both have a remainder of 3 when divided by 4. That is,
p K q K 3(mod 4)
This notation, explained more fully in Chapter 4, simply means that
(p mod 4) = (q mod 4) = 3 . For example, the prime numbers 7 and 11 satisfy
7 K 11 K 3(mod 4) . Let n = p * q . Next, choose a random number s , such that s is
relatively prime to n ; this is equivalent to saying that neither p nor q is a factor of s .
Then the BBS generator produces a sequence of bits B i according to the following
algorithm:
X 0
for i
X i
B i
=
=
=
=
s 2 mod n
1 to q
(X i - 1 ) 2 mod n
X i mod 2
*/