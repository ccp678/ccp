#include <bits/stdc++.h>
using namespace std;
//你的名字,具体可参考实验四第一题，本质是一样的。
void first()
{
        int n =0,m = 0;
    char cat[100][100],str[100][32];
    int notes[100][100][26] ={0};
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;++i)
    {
        scanf("%s",(cat[i]+1));     
        int len = strlen(cat[i] + 1);
        for(int j = 1;j < len;++j)
        {
            cat[i][j] = tolower(cat[i][j]);   //将字符串转化成小写
        }
        //对每一个字符串对应一页来储存相应的信息
        for(int j= len;j >= 1;--j)
        {
            if(j == len)
            {
                for (int k = 0;k < 26;++k)
                {
                    notes[i][j][k] = len + 1;       //将三维数组第i页第j行进行初始化
                }
            }
            for(int k = 0;k < 26;++k)
            {
                notes[i][j-1][k] = notes[i][j][k];          //初始化上一行
            }
            notes[i][j-1][cat[i][j] - 'a'] = j;                 //j行即表示字符串的j列，在这一页中的j-1行对应的字母列填上j,便于跳转
        }
    }

    for (int i = 1;i <= m;++i)
    {
        scanf("%s",str[i] + 1);
        int len = strlen(str[i] + 1);
        for (int j = 1;j < len;++j)
        {
            str[i][j] = tolower(str[i][j]); 
        }
    }
    for (int i = 1;i <=n;++i)
    {
        int num = 0;
        int catlen = strlen(cat[i] + 1);
        for(int j = 1;j <= m;++j )
        {
            int p = 0,flag = 1;
            int slen = strlen(str[j] + 1);
            for(int k = 1;k <= slen;++k)
            {
                p = notes[i][p][str[j][k] - 'a'];
                if(p > catlen)
                {
                    flag = 0;
                    break;
                }
            }
            if(flag) num++;
        }
        cout<<num<<endl;
    }
}
//在全局变量中这些数组会自动赋值为0
const int manx=200;
typedef long long ll;
const ll inf=1e18+1;
int n,k;
ll f[manx][manx];
char ans[manx];
void second()
{
    /*
    int n,k;
    long long f[2010][2010];
    char ans[2010];
    cin>>n>>k;
    d[0][0] = 1;
    for(int i = 1;i <= n;++i)
    {
        for(j = 0;j <= n;++j)
        {
            if(f[i-1][])
        }
    }*/

    scanf("%d%d",&n,&k);
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(f[i-1][j]){
                f[i][j+1]+=f[i-1][j];
             	if(j)f[i][j-1]+=f[i-1][j];
                f[i][j+1]=min(f[i][j+1],inf);
                if(j)f[i][j-1]=min(f[i][j-1],inf);
            }
        }
    }
    int now=0;
    for(int i=1;i<=n;i++){
        if(f[n-i][now+1]>=k)ans[i]='(',++now;
        else ans[i]=')',k-=f[n-i][now+1],--now;
    }
    puts(ans+1);
}


int main() {
second();
}   
