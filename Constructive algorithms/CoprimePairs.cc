/*
  From CS Academy link: https://csacademy.com/contest/round-43/task/coprime/
*/

#include<iostream>
#include<vector>


using namespace std;

int vis[1000008];
vector<int> p;


   void sieve(){

          for(int i=2;i*i<1000008;i++){
                if(!vis[i]){
                    vis[i]=true;
                    p.push_back(i);

                    for(int j=i*i;j<1000008;j+=i){
                         vis[j]=true;
                    }
                }

          }

            for(int i=2;i<1000008;i++){
                 if(!vis[i]){
                     p.push_back(i);
                 }
            }

      }



int main(){

   int n,k;
   cin>>n>>k;
   
   sieve();
   
   int a[n];

   for(int i=0;i<n;i++)a[i]=p[i+2];

   long x = n*(n-1)/2 - k;

   long t=1;
   while((t*(t-1)/2)<=x)t++;
   t--;

   //We have now t(t-1)/2 coprime with gcd 2 
   for(int i=0;i<t;i++){
       a[i]*=2;
    } 

   //we need x - (t*(t-1)/2) more (gcd will be 3)
   a[t]*=3;
   for(int i=0;i<(x-(t*(t-1)/2));i++){
       a[i]*=3;
    }

   for(int i=0;i<n;i++){
         cout<<a[i]<<" ";
    }

    return 0;
}