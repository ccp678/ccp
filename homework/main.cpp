#include <bits/stdc++.h>
#include<algorithm>
//#include<vector>
#include <utility> 
using namespace std;

typedef struct point
{
    /* data */
    int x;
    int y;
}Point;
int MAX=8;
vector<Point> p;
int sum = 1;
bool visited[8][8]={0};
bool judgeOver(Point &p)
{
    return p.x <= MAX&&p.x >= 0&&p.y <= MAX&&p.y>=0;
}

//第一章
void experiment0101()
{
    //vector部分
    vector<int> v;
srand(int(time(NULL)));
for(int i = 0;i < 10;++i)
{
    int n = rand()%10;
    v.push_back(n);
}
for(vector<int> :: iterator i = v.begin();i!=v.end();++i)
{
    cout<<*i<<" ";
}
int willFind = rand()%10;
vector<int>::iterator it = find(v.begin(),v.end(),willFind);
if(it == v.end())
{
    v.push_back(willFind);
}
else
{
    cout<<*it;
}

sort(v.begin(),v.end());
for(vector<int> :: iterator i = v.begin();i!=v.end();++i)
{
    cout<<*i<<" ";
}

cout<<endl;
v.pop_back();
for(vector<int> :: iterator i = v.begin();i!=v.end();++i)
{
    cout<<*i<<" ";
}
v.clear();


//list部分
list<int> l;
for(int i = 0;i < 10;++i)
{
    int n = rand()%10;
    l.push_back(n);
}
cout<<endl;
for(list<int>::iterator i = l.begin();i != l.end();++i)
{
    cout<<*i<<" ";
}


list<int>::iterator it2 = find(l.begin(),l.end(),willFind);

if(it2 == l.end())
{
    l.push_back(willFind);
}
else
{
cout<<*it2;
}

l.sort();
cout<<endl;
for(list<int>::iterator i = l.begin();i != l.end();++i)
{
    cout<<*i<< " ";
}

l.pop_back();
cout<<endl;
for(list<int>::iterator i = l.begin();i != l.end();++i)
{
    cout<<*i<<" ";
}
l.clear();

}

void experiment0102()
{
vector<int> v;
srand(int(time(NULL)));
for (int i = 0;i < 10;++i)
{
    int n = rand()%10;
    v.push_back(n);
}

//升序排列
sort(v.begin(),v.end());
for(vector<int>::iterator i = v.begin();i!=v.end();++i)
{
    cout<<*i<<" ";
}

sort(v.begin(),v.end(),[](const int num1,const int num2 )
{
    return num1 > num2;
});
cout<<endl;
for(vector<int>::iterator i = v.begin();i!=v.end();++i)
{
    cout<<*i<<" ";
}
int willFind = 2;

vector<int>::iterator it = find(v.begin(),v.end(),willFind);
if(it != v.end())
{
    cout<<"找到了"<<endl;
}
else 
{
    cout<<"没找到"<<endl;
}

it = max(v.begin(),v.end());
cout<<"最大值为"<<*it<<endl;
it=min(v.begin(),v.end());
cout<<"最小值为"<<*it<<endl;
}


bool DFS(Point point)
{
    p.push_back(point);
    visited[point.x][point.y] = 1; //当前节点已经访问过
    if(sum == 64) return true;
    const int dir[8][2]={{-1, 2}, {-2, 1}, {-2, -1}, {-1, -2},{1, 2}, {2, 1}, {2, -1}, {1, -2}};
    //遍历所有方向
    for(int i = 0;i < MAX;++i)
    {
        Point next = point;
        next.x += dir[i][0];
        next.y += dir[i][1];
        
        if(judgeOver(next)&&0==visited[next.x][next.y])
        {
            sum++;
            bool b = DFS(next);
            if(b)
            {
                return true;
            }
            sum--;
        }
    }

    visited[point.x][point.y] = 0;
    p.pop_back();
    return false;
}

//第二章第三题
void experiment0203()
{
    int x,y;
    cin>>x>>y;
    Point point;
    point.x = x;
    point.y = y;
    DFS(point);
    for(vector<Point>::iterator i = p.begin();i!=p.end();++i)
    {
        cout<<i->x<<" "<<i->y<<endl;
    }
}

int counter  = 0;
bool  hadQueen[9] = {false};  //表示行上有没有皇后
int y_x[9];        //表示皇后出现的列和行，数组下表表示列，数组存储元素表示行
bool judgeRight(int k)
{
    for(int i = 0 ;i < k;++i)
    {
        if(y_x[i] == y_x[k]||abs(y_x[i]-y_x[k]) == abs(i - k))  //在同一列或者同一斜线上
        return false;
    }
    return true;
}
int queen(int maxn)
{
    int k = 0;
    int sum = 0;
    while(k>=0)
    {
        y_x[k]++;  //放置第k个皇后，找到合适的摆放方法后直接会寻找下一个列数区遍历再次寻找
        while(y_x[k] < maxn&& judgeRight(k) == false)
        {
            y_x[k]++;                       //找到合适的列数
        }
        if(y_x[k] < maxn&&k == maxn-1)
        {
            sum++;
        }
        if(y_x[k] < maxn&&k < maxn - 1)
        {
            k++;
        }
        else
        {
            y_x[k] = -1;
            k--;
        }
        
    }
    return sum;
}

//八皇后问题
void eightQueen()
{
    for(int i = 0;i < 9;++i)
    {
        y_x[i] = -1;
    }
    cout<<queen(8)<<endl;
}

struct  wall
{
    /* data */
    double x,y[5];
}w[20];  //表示每一面墙的信息。
const int INF = 1234567;  //将一个不可能的是作为路径的初始值，加上直线后，找到最短路径 
double path[300][300];   //表示原点对每一个节点的距离，即为floyd算法的权值

//判断直线之间是否穿过门，穿过中间所有墙的返回true，否则返回false
bool check(int x1,int x2,int y1,int y2)
{
    if(x2-x1 < 2) return true;
    double xi = w[x1].x, xii = w[x2].x;
    double yi = w[x1].y[y1],yii = w[x2].y[y2];
    double k = (yii-yi)/(xii - xi);
    double B = yi - k*xi;
    for(int i = x1+1;i < x2;++i)
    {
        double y = k*w[i].x + B;

        //当直线之间没有穿过中间墙的门，返回false
        if(!((y > w[i].y[1]&&y < w[i].y[2])||(y > w[i].y[3]&&y < w[i].y[4])) )  return false;  
    }
    return true; 
}

void add(int x1,int x2,int y1,int y2)
{
    if(!check(x1,x2,y1,y1))  return;   //直线不能增加
    double xi = w[x1].x,xii = w[x2].x;
    double yi = w[x1].y[y1],yii = w[x2].y[y2];
    path[(x1<<2) + y1][(x2<<2) + y2] = sqrt(pow(xii-xi,2)+pow(yii-yi,2));
}


void floyd(int n)
{
    for(int k = 1;k <= 4*n + 4;++k)
    {
        for(int i = 1;i <= 4*n + 4;++i)
        {
            for(int j = 1;j <= 4*n+4;++j)
            {
                path[i][j] = min(path[i][j],path[i][k] + path[k][j]);
            }
        }
    }
}
//第三章第四题
void experiment0304()
{
    int n;
    cout<<"请输入墙的个数"<<endl;
    cin>>n;
    for(int i = 1;i <= n;++i)
    {
         printf("输入%d号墙的x值",i+1);
         cin>>w[i].x;
        printf("输入%d号墙的y值的范围",i+1);
        for(int j = 1;j < 5;++j)
        {
            cin>>w[i].y[j];
        }
    }

    w[0].x = 0;
    w[++n].x = 10;

    for(int i = 1;i < 5;++i )
    {
        w[0].y[i] = w[n].y[i] = 5;
    }
    for(int i = 1;i <= 4*n + 4;++i)
    {
        for(int j = 1;j <= 4*n + 4 ;++j)
        {
            path[i][j] = INF;
        }
    }

    for(int i = 0;i <= n;++i)
    {
        for(int j = i + 1;j <= n;++j)
        {
            for(int k = 1;k < 5;++k)
            {
                for(int l = 1;l < 5;++l)
                add(i,j,k,l);
            }
        }
    }
    
    floyd(n);
    cout<<path[1][n*4+1]<<endl;

}



//第四章第3题
//首先确定行，再根据列的和确定选择哪一列.
//再根据遍历的情况遍历一遍列

//行方向上是连续，但是列方向不连续的情况。
double submatrix_sum_row(int y1,int y2,double matrix[4][4],int n)
{
   // vector<double> v_column;
    double sum_column[n] = {0};
    double judege_sum = 0;
    bool sign = false;   //判断是否要更新列数据和的子段
    for(int i = 0;i < n;++i)
    {
        double sum = 0;
        for(int j = y1;j <= y2 ;++j)
        {
            sum+=matrix[j][i];
        }
        sum_column[i] = sum;
    }   

double sum_max = sum_column[0];
    for(int i = 0;i < n;++i)
    {
        judege_sum += sum_column[i];
        if(sign)
        {
            judege_sum = sum_column[i];
            sign = false;
        }
        if(judege_sum > sum_max)
        {
            sum_max = judege_sum;
        }
        if(judege_sum < 0)
        {
            sign = true;
        }
    }
    return sum_max;
}
//在列方向上是连续，但是航方向不连续的构成子矩阵的情况
double submatrix_sum_column(int x1,int x2,double matrix[4][4],int n)
{
   double sum_row[n];
    for(int i = 0;i < n;++i)
    {
        double sum = 0;
        for(int j = x1;j <= x2;++j)
        {
            sum+=matrix[i][j];
        }
        sum_row[i] = sum;;
    }
    double sum_max = sum_row[0];
    double judge_sum = 0;
    bool sign = false;
    for(int i = 0;i < n;++i)
    {
        judge_sum += sum_row[i];
        if(sign)
        {
            judge_sum = sum_row[i];
            sign = false;
        }
        if(judge_sum>sum_max)
        {
            sum_max = judge_sum;
        }
        if(judge_sum < 0)
        {
            sign = true;
        }
    }
    return sum_max;
}
void experiment0403()
{
    //输入数据
    int n;
    /*cout<<"请输入矩阵的阶数"<<endl;
    cin>>n;
    double matrix[n][n];
    for(int i = 0;i < n;++i)
    {
        printf("请输入矩阵第%d行的数据\n",i+1);
        for(int j = 0;j < n;++j)
        {
            cin>>matrix[i][j];
        }
    }*/
    double matrix[4][4] = {
     {0 ,-2, -7 ,0 },
{9 ,2 ,-6 ,2 },
{-4 ,1 ,-4 ,1 },
{-1, 8 ,0 ,-2 }
    };
    n = 4;
    vector<double> v_sum;
    double sum1,sum2;
    for(int i = 0;i < n;++i)
    {
        for(int j = i+1;j < n;++j)
        {
            v_sum.push_back(submatrix_sum_row(i,j,matrix,n));
            v_sum.push_back(submatrix_sum_column(i,j,matrix,n));
        }
    }
    double sum_max = *max_element(v_sum.begin(),v_sum.end());
    cout<< sum_max;
}

//最长子序列问题
void experiment0401(char str1[],char  str2[])
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int sum[len1+1][len2 + 1];
    
    for(int i = 0;i <= len1;++i)
    for(int j = 0;j <= len2;++j)
    sum[i][j] = 0;
    for(int i = 1;i <= len1;++i)
    {
        for(int j = 1;j <= len2;++j)
        {
            if(str1[i-1] == str2[j-1])
            {
                sum[i][j] = sum[i-1][j-1] + 1;
            }
            else
            {
                sum[i][j] = max(sum[i-1][j],sum[i][j-1]);
            }
            
        }
    }

    int i, j;
    stack<char> s;
    for(i = len1, j = len2;i>=1&&j>=1;)
    {
        char c1 = str1[i-1],c2 = str2[j-1];
        if(str1[i-1]==str2[j-1])
        {
            s.push(str1[i-1]);
            i--;
            j--;
        }
        else
        {
            if(sum[i-1][j] > sum[i][j-1])
            {
                i--;
            }
            else
            {
                j--;
            }
            
        }
    }
   

   while(!s.empty())
   {
       cout<<s.top();
       s.pop();
   }
}


typedef pair<double,double> POINT; 

// function dirction determines the direction that the segment 
//p1p turns to p2p with respect to point p 
//if return value is positive, means clockwise; 
//if return value is negative, menas counter-clockwise; 
// naught means on the same line; 
double direction(POINT p,POINT p1,POINT p2) 
{ 
 POINT v1,v2; 
 v1.first =p2.first -p.first ; 
 v1.second=p2.second-p.second; 
 v2.first =p1.first -p.first; 
 v2.second=p1.second-p.second; 
 return v1.first*v2.second-v1.second*v2.first; 
} 
//function on_segment determines whether the point p is on the segment 
//p1p2 
bool on_segment(POINT p,POINT p1,POINT p2) 
{ 
 double min_x=p1.first <p2.first ?p1.first :p2.first ; 
 double max_x=p1.first >p2.first ?p1.first :p2.first ; 
 double min_y=p1.second<p2.second?p1.second:p2.second; 
 double max_y=p1.second>p2.second?p1.second:p2.second; 
 if (p.first >=min_x && p.first <=max_x 
 && p.second>=min_y && p.second<=max_y) return true; 
 else return false; 
} 
//point startPoint is the polor point that is needed for comparing 
//two other points; 
POINT startPoint; 
//function sortByPolorAngle provides the realizing of comparing two 
//points, which support 
//the STL function sort(); 
bool sortByPolorAngle(const POINT & p1, const POINT & p2) 
{ 
 double d=direction(startPoint, p1, p2); 
 if (d<0) return true; 
 if (d>0) return false; 
 if (d==0 && on_segment(startPoint, p1, p2) )return true; 
 if (d==0 && on_segment(p2,startPoint,p1) ) return true; 
 return false; 
} 
//here realizes the process of finding convex hull 
void find_convex_hull(vector<POINT> & point) 
{ 
 POINT p0=point[0]; 
 int k=0; 
 for (int i=1;i<point.size();i++) 
 { 
 if (point[i].second<p0.second || 
 point[i].second==p0.second && point[i].first<p0.first) 
 { 
 p0=point[i]; 
 k=i; 
 } 
 } 
 point.erase(point.begin()+k); 
 point.insert(point.begin(),p0); 
 vector<POINT> convex_hull; 
 do { 
 convex_hull.push_back(point[0]); 
 startPoint=point[0]; 
 point.erase(point.begin()); 
 sort(point.begin(),point.end(),sortByPolorAngle); 
 if (point[0]==convex_hull[0]) break; 
 point.push_back(convex_hull[convex_hull.size()-1]); 
 } while (1); 
 for(int i=0;i<convex_hull.size();i++) 
 { 
 cout<<convex_hull[i].first<<' ' 
<<convex_hull[i].second<<endl; 
 } 
} 

int main() {
    //std::cout << "Hello, world!\n";  
    //eightQueen();
    //experiment0304();
    //experiment0403();

    /*char str1[10]= "peach";
    char str2[20] = "peat";
    experiment0401(str1,str2);*/
    
    //experiment0101();

    //experiment0102();
   //int i = 1;
   //cout<<str1[i]<<endl;
   double x[10][10] = {
       {0 ,0 },
{0, 1 },
{0.5 ,0.5 },
{1, 1 },
{1 ,0 }
};
   vector<POINT> v;
   for(int i = 0;i < 5;i++)
   {
       pair<double,double> p(x[i][0],x[i][1]);
       v.push_back(p);
   }
   find_convex_hull(v);
}
