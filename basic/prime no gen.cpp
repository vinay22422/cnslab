#include <bits/stdc++.h>
#include<cmath>

using namespace std;
int gp(int f, int t){
int i,j,k;
for(i=f;i<=t;i++){k=1;
    for(j=2;j<=(int)i/2;j++){
        if(i%j==0){
            k=0;break;
        }
    }
    if(k)
        cout<<" "<<i<<" ";

}


}
int main()
{
    cout << "Hello world!" << endl;

    int no1,no2;

    cin>>no1>>no2;
    gp(no1,no2);



    return 0;

}
