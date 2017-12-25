/*
    Consider the decomposition of an array in blocks of x elements.
    And the function f: x -> x + n/x where: x is time for an update and n/x is time needed to sum range query 

    f'=1-n*(1/x2) rich the minium in x=sqrt(n) ==> So the optimized decomposition for such tasks (combined) is the square root decompositon.
*/

#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;


int main(){

    int n;cin>>n;

    int a[n+2];
    for(int i=0;i<n;i++)cin>>a[i];
        
    //block size
    int bz = ceil(sqrt(n));
    int block[bz];


    //Build
    //Complexity O(sqrt(n)*sqrt(n))==O(n)
    // for(int i=1;i<=block_size;i++){
    //       int s=0;
    //       for(int j=1;j<=block_size;j++){
    //              s = s + a[j+(i-1)*block_size];
    //            }
    //       block[i]=s;     
    //     }

    //OR
    for(int i=0;i<n;i++){
          block[i/bz]+=a[i];  
     }

     int t;cin>>t;

     while(t--){
         int l,r;
         cin>>l>>r;

         //Complexité total par query: O(sqrt(n)+sqrt(n)+sqrt(n))=O(3*sqrt(n))=O(sqrt(n))
         l--,r--;
         int p = l/bz;
         int q = r/bz;

         int result=0;

         if(l==r){
             result=a[l];
         }else{
            
             for(int i=p+1;i<=q-1;i++){
                      result+=block[i];
                    }
         
             for(int i=l;i<(p+1)*bz&&i<r;i++){
                      result+=a[i];
                    }    
             for(int i=max(q*bz,l+1);i<=r;i++){
                      result+=a[i];
                    }
          
             cout << result << endl;
          }
           
       }
  
    return 0;
}