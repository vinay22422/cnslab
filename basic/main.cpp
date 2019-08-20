#include <bits/stdc++.h>
#include<cmath>

using namespace std;
int gcd(int no1, int no2){

    if (no1==0)
        return no2;
    gcd(no2%no1,no1);




}
int main()
{
    cout << "Hello world!" << endl;

    int no1,no2;

    cin>>no1>>no2;
    cout<<min(no1,no2)<<max(no1,no2);
    cout<<gcd(min(no1,no2),max(no1,no2));
    cout<<__gcd(min(no1,no2),max(no1,no2));



    return 0;

}
