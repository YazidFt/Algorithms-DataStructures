
/*  Intro:
    Consider the decomposition of an array in blocks of x elements.
    And the function f: x -> x + n/x where: x is time for an update and n/x is time needed to sum range query 
    f'=1-n*(1/x2) rich the minium in x=sqrt(n) ==> The optimized decomposition for such tasks (combined) is the square root decompositon.
    
    Example: Range-Sum-Qeries
*/

#include<iostream>
#include<vector>
#include<cmath>


using namespace std;

int main(){
     
     //Array for tests
     int siz;
     cin>>siz;
     int a[siz];
     
     for(int i=0;i<siz;i++){cin>>a[i];}

     //blocks size
     int n = ceil(sqrt(siz));
     //sqrt decomp blocks
     int blocks[n]={0};


     for(int i=0;i<siz;i++){
         blocks[i/n] += a[i];
      }

     
      //Queries (Range-sum-Q)
      int q;cin>>q;

      while(q--){
          int l,r;
          cin>>l>>r;

          int sum=0;

          for(int i=l;i<=r;i++){
                if(i%n==0 && i+n-1<=r){
                   sum += blocks[i/n];
                   i += n-1;
                }
                else{
                  sum += a[i];
                }
           }
         
         cout << sum << endl;
        }


    return 0;
}