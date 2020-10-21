#include <bits/stdc++.h>
using namespace std;
int main(int, char**) {
    //std::cout << "Hello, world!\n";
    int n,m;
    char cat[1000][1001],str[100][32];
    char notes[1000][1001][26];
    cin>>n>>m;
    for(int i = 1;i < n;++i)
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
           /* for(int k = 1;k <= slen;++k)
            {
                p = notes[i][p][str[j][k] - 'a'];
                if(p > catlen)
                {
                    flag = 0;
                    break;
                }
            }*/
            if(flag) num++;
        }
        cout<<num<<endl;
    }
}   
