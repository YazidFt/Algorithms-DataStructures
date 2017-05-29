/*
  The code represent one of the most efficient string searching algorithm: KMP
  Problem:
          Given a Text(T) and a pattern (P) we output the number of occurrences of P in T
          Time complexity: O(p+t) p=|P| and t=|t|
*/

#include <iostream>
#include <vector>

using namespace std;

  vector<int> prefix_function(string s){
                 int n = s.length();
                 vector<int> f(n);
                 f[0]=0;

                 for(int i=1;i<n;i++){
                     int j = f[i-1];
                     while(j>0 && s[j]!=s[i]){
                         j = f[j-1];
                      }

                     if(s[j]==s[i]){j++;}
                     f[i]=j;
                  }

                  return f;
               }

int main()
{
    string T,P;
    int res=0,idx=0;
    cin>>P>>T;

    vector<int> F = prefix_function(P);


    for(int i=0;i<T.length();i++){

          while(idx > 0 && T[i]!=P[idx]){
               idx=F[idx-1];
             }

          if(T[i]==P[idx]){
                idx++;
              }

          if(idx==P.length()){
               res++;
             }
         }

    cout << res;

    return 0;
}
