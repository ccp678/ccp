#include <bits/stdc++.h>
using namespace std;
void experiment0203();
double f(double x)
{
    return 1./(1+x*x);
}
double shizi(double Xk/*表示第几个节点*/,double x_predict/*输入的预测x*/,vector<double> &v)
{
    double num = 1.;
    for(vector<double>::iterator i = v.begin();i!=v.end();++i)
    {
        if(!(abs(*i-Xk) < 1e-6))
        {
               num = num*((x_predict - *i)/(Xk - *i));
        }
    }
    return num;
}
vector<double > v_x;
vector<double> v_y;
void init(double x_left,double x_right, int n)
{
    v_x.clear();
    v_y.clear();
    double h = (x_right-x_left)/(n-1);   //表示一小份有多长
    for(int i = 0;i < n;++i)
    {
        double  x = x_left + i*h;
        double y = f(x);
        v_x.push_back(x);
        v_y.push_back(y);
    }
}
double Lchazhi(double x_left,double x_right, int n,  double x_predict)
{
    init(x_left,x_right,n);
    //处理数据
    double sum = 0;
    for(int i = 0;i < n;++i)
    {
        sum += shizi(v_x[i],x_predict,v_x)*v_y[i];
    }
    return sum;
}


double Fchazhi(double x_left,double x_right, int n,  double x_predict)
{
    init(x_left,x_right,n);
    int k;
    for(int i = 0;i < n-1;++i)
    {
        if(v_x[i] < x_predict && x_predict < v_x[i+1])
        {
            x_left = v_x[i];
            x_right = v_x[i+1];
            k = i;
            break;
           //cout<<k<<endl;
        }
    }
    //k = 5;
    return v_y[k]*((x_predict-v_x[k+1])/(v_x[k]-v_x[k+1])) + v_y[k+1]*((x_predict - v_x[k])/(v_x[k+1]-v_x[k]));
    
    //return sum;
}

double d_f(int n,double x_predict)
{
    double liancheng = 1,sum = 0;
    for(int k = 0;k <= n;++k)
    {
        liancheng = 1;
        for(int j = 0;j <= n;++j)
        {
            if(k!=j)
            liancheng = liancheng  * 1./(v_x[k]-v_x[j]);
        }
        sum+=v_y[k]*liancheng;
    }
    double t = sum;
    for(int i = 0;i < n;++i)
    {
        t = t*(x_predict - v_x[i]);
    }
    return t;
}
double Newton(double x_predict,int n)
{
    double t = v_y[0];
    double sum = v_y[0];
    for(int i = 1;i < v_x.size();++i)
    {
        sum += d_f(i,x_predict);
    }
    return sum;
}

double f2(double x)
{
    return x*x;
}

void  experiment0201()
{
    vector<double> f;
    int n,a,b;
    cout<<"请输入等分的个数"<<endl;
    cin>>n;
    cout<<"请输入区间的左边界"<<endl;
    cin>>a;
    cout<<"请输入区间的右边界"<<endl;
    cin>>b;
   // cout<<"请输入函数的x值和对应的y值"<<endl;
    /*while(true)
    {
        pair<double,double> l_f;
        char flag;
        cout<<"x值为"<<endl;
        cin>>l_f.first;
        cout<<"对应的y值为"<<endl;
        cin>>l_f.second;
        cout<<"是否退出（Y or N）"<<endl;
        cin>>flag;
        f.insert(l_f);
        if(flag == 'Y') break;
    }*/

double h = (b-a)/n;
   for(int i = 0;i < n + 1;++i)
   {
       double x = a + i*h;
       double y = f2(x); 
       f.push_back(y);
  //  f.insert(pair<double,double>(-5+i,-4+i));
    
   }

//开始复化梯形求积运算
    double sum = 0;
    for(int i = 0;i < n;++i)
   {
       sum+=(f[i] + f[i+1])*h/2;
   }
   cout<< sum;
}

void experiment0202()
{
    int n,a,b;
    cout<<"请输入等分的段数";
    cin>>n;
    cout<<"请输入区间的左边界"<<endl;
    cin>>a;
    cout<<"请输入区间的右边界"<<endl;
    cin>>b;

    double x_y[n];
    double x_y_[n];
    double h = (b-a)/n;
    for(int i = 0;i < n+1;++i)
    {
        x_y[i] = f2(i*h + b);
        double x_1_2 =(i*h + b + b + (i+1)*h)/2; 
        x_y_[i] =  f2(x_1_2);
    }
double sum = 0;
    for(int i = 0;i < n;++i)
    {
        sum += (x_y[i] + x_y[i+1] + 4*x_y_[i])*h/6; 
    }
    cout<<sum;
}

double f3(double x)
{
    return sin(x)/x;
}

/*void experiment0203()
{
    double x_y[2];
    x_y[0]  = 1.;
    x_y[1] = sin(1);
    int n = 4;
    vector<double> T;    
    double h,b = 0;
    for(int i = 0;i < n;++i)
    {
    
        if(i == 0)
        {
            h = 1;
            T.push_back((x_y[0] + x_y[1])*h/2);
            cout<<T[0]<<endl;
            h = h/2;
            continue;
        }
        double sum  =0;
        for(int j = 0;j < pow(2,i);++j)
        {
            double x_ = (b + j*h + b +(j + 1)*h)/2;
            cout<<x_<<endl;
            sum+=f3(x_);
        }
        T.push_back(T[i-1]*1./2 + sum*h/2);
        h = h/2;
        cout<<"T"<<T[i]<<endl;
    }

    vector<double> S;
    n--;
    for(int i = 0;i < n;++i)
    {
        S.push_back(T[i+1]*4./3 - T[i]*1./3);
        cout<<"S"<<S[i]<<endl;
    }
    n--;
    vector<double>C;
    for(int i = 0;i < n;++i)
    {
        C.push_back( S[i+1]*16./15 - S[i]*1./15);
        cout<<"C"<<C[i]<<endl;
    }
    n--;
    vector<double> R;
    for(int i = 0;i < n;++i)
    {
        R.push_back( C[i+1]*64./63 - C[i]*1./63);
        cout<<R[i];
    }
}
*/
void experiment0203()
{
    double x_y[2];
    x_y[0]  = 1.;
    x_y[1] = sin(1);
    int n = 5;
    double a = 0,b = 1;
double h = 1;
    double T1,T2,S1,S2,C1,C2,R1,R2;
    int k = 1;
    T1 = (x_y[0] + x_y[1])*h/2;
    while (true)
    {
    
        double sum = 0;
        double x = a+h/2;
        cout<<h<<endl;
        do
        {
            /* code */
            sum += f3(x);
            x += h;
        } while (x < b);
        T2 = T1*1./2 + sum*h/2;
        //cout<<T1<<" "<<T2<<endl;
        S2 = T2+1./3*(T2-T1);
       // cout<<"S2"<<S2<<endl;
       if (k == 1)
        {
             k++;
            h = h/2;
            T1 =  T2;
            S1 = S2;
            continue;
        }
        C2 = S2+1./15*(S2-S1);
        if(k==2)
        {
            C1= C2;
             k++;
            h = h/2;
            T1 =  T2;
            S1 = S2;
            continue;
        }
        R2 = C2 + 1./63*(C2-C1);
        if(k==3)
        {
            R1 = R2;
            C1 = C2;
             k++;
            h = h/2;
            T1 =  T2;
            S1 = S2;
            continue;
        }
         
         if(abs(R1-R2) < 1e-6)
         {
           break;
         } 
            R1 = R2;
            C1 = C2;
             k++;
            h = h/2;
            T1 =  T2;
            S1 = S2;   
    }
cout<<R2<<endl;

}

double f_d(double x)
{
    return 3*x*x - 1;
}
double f4(double x)
{
    return pow(x,3) - x - 1;
}
void experiment0401()
{
    double x0,e;
    int N,M;
    cout<<"输入 x0,e,N,M"<<endl;
   
    cin>>x0>>e>>N>>M;
    int k = 0;
    double x1,l = 1;
   do
   {
        if(f_d(x0) == 0)
        {
        cout<<"错误"<<endl;
        return;
        }
        int i = 0;
        double l = 1;
        while(true)
        {
            x1 = x0-l*f4(x0)/f_d(x0);
            if((abs(f4(x1)) < abs(f4(x0)))) break;
            
                i++;
                l = l*1./2;
             if(!(i >= M)) continue;
                else 
                {
                    cout<<"重新输入x0";
                    cin>>x0;
                }
             
        }
        
        if(abs(x1-x0) < e)
        {
            cout<<x1<<endl;
            break;
        }
        k++;
        x0 = x1;
   } while (!(k >= N));
   
}

int main(int, char**) {
    //std::cout << "Hello, world!\n";
   /* double x_left,x_right,x_predict;
    int n;
    int sign = 1;
    while(true)
    {
        cout<<"请输入区间长度和预测值";
    cin>>x_left>>x_right>>x_predict;
    cout<<"输入差值段个数";
    cin>>n;
    ++n;
    cout<<"X            Y(精确)         Y(拉格朗日)         Y(分段线性)             误差（拉）          误差（分）"<<endl;
    double l = Lchazhi(x_left,x_right,n,x_predict);
    double F = Fchazhi(x_left,x_right,n,x_predict);
    double y = f(x_predict);
    printf("%lf      %lf        %lf     %lf         %lf     %lf\n",x_predict,y,l,F,y-l,(y-F));
    
    if(sign==2 ) break;
    sign++;
    }

    
    cout<<"请输入牛顿差值的点集（小于0退出）"<<endl;
    v_x.clear();
    v_y.clear();
    while(true)
    {
        double x;
        cin>>x;
        if(x<0) break;
        v_x.push_back(x);
        v_y.push_back(sqrt(x));
        
    }
    cout<<"请输入牛顿差值的预测值"<<endl;
    cin>>x_predict;
    cout<<"牛顿差值的结果为"<<endl;
    cout<<Newton(x_predict,v_x.size());
    */
   //experiment0201();
   experiment0203();
   //experiment0401();
}
