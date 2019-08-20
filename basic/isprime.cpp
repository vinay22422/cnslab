#include <bits/stdc++.h>
#include<cmath>

using namespace std;
void cp(int n){
    cout<<"n="<<n<<endl;
    int i;
    for (i=2;i<=(int)n/2;i++){
            //cout<<"\n"<<(i%n)<<"is mod val & i="<<i;
            //cout<<endl<<"i%n="<<i<<"%"<<n<<" = "<<(i%n)<<endl;

        if (n%i == 0)
        {
            cout<<"False";
            //cout<<"\n"<<i;
            return ;
        }

    }

    cout<<"True";




}
int main()
{
    cout << "Hello world!" << endl;
    int n;
    cin>>n;
    cp(n);

    return 0;

}
