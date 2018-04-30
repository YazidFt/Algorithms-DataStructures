/*
   Problem link: http://www.spoj.com/problems/MATSUM/
   Execution Time: 0.37 
   Memory: 35M

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

#define ll long long

using namespace std;

const int maxN = 2*1024;
int BIT[2*1024][2*1024];


void update(int x, int y, int val){  
     while(x < maxN){
            int t = y;
            while(t < maxN){
                 BIT[x][t] += val;
                 t += (t&-t);
               }
             x += (x&-x);
           }
       }


int get(int x, int y){
        int s = 0;
        while(x > 0){
            int t = y;
            while(t > 0){
                s += BIT[x][t];
                t -= (t&-t);
              } 
            x -= (x&-x);
          }
        return s;     
      } 

 
int main(){
   
    int t;
    scanf("%d", &t);

    while(t--){
        int n;
        scanf("%d", &n);
        
        memset(BIT, 0, sizeof(BIT));
        int mat[n+1][n+1] = {0};

    while(true){    

        char s[4];
        scanf("%s", &s);

        if(s[1] == 'E'){
            int x, y, num;
            scanf("%d%d%d", &x, &y, &num);
            x++; y++;
            update(x, y, num - mat[x][y]);
            mat[x][y] = num;
            
        }
        else if(s[1] == 'U'){
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1++, y1++, x2++, y2++;
            int res = get(x2, y2) - get(x1-1, y2) - get(x2, y1-1) + get(x1-1, y1-1);
            printf("%d\n", res);
         }
        else{
             break;
          }

       }

   }

    return 0;

}