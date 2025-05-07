//🙊
#include<iostream>
#include<vector>
#include<complex>
#include<cmath> //引入M_PI、cos、sin    
#include<algorithm>// 引入reverse
using namespace std;

typedef complex<double> Complex;

void fft(vector<Complex>& a, bool invert) { //invert = true for inverse FFT 
    int n=a.size();
    if(n<=1) return;

    vector<Complex> a_even(n/2), a_odd(n/2);//奇函数和偶函数
    for(int i=0;i<n/2;++i){
        a_even[i]=a[2*i];
        a_odd[i]=a[2*i+1];
    }
    fft(a_even,invert);
    fft(a_odd,invert);

    double angle=2*M_PI/n*(invert? -1 : 1 );
    Complex w(1), wn(cos(angle),sin(angle));//欧拉公式
    for(int i=0;i<n/2;++i){
        a[i]=a_even[i]+w*a_odd[i];
        a[i+n/2]=a_even[i]-w*a_odd[i];
        if(invert){
            a[i]/=2;
            a[i+n/2]/=2;  //相当于整体上除了一个n
        }
        w*=wn;
    }
}

void ifft(vector<Complex>& a) {//逆变换
    fft(a, true);
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    int n=a.size();
    int m=b.size();
    int size=n+m-1;
    //FFT算法要求 ：输入长度必须是2的整数次幂
    int L=1;
    while(L<size) L<<=1;  //通过位运算快速找到最小二次幂，左移一位相当于乘2

    vector<Complex> fa(a.begin(),a.end()), fb(b.begin(),b.end());
    fa.resize(L,0);//补齐长度 fft用于计算L个L次方根对应的值
    fb.resize(L,0);

    fft(fa,false);
    fft(fb,false);

    for(int i=0;i<L;++i)
        fa[i]*=fb[i];

    ifft(fa); //逆变换

    vector<int> result(size);
    for(int i=0;i<size;++i)
        result[i]=round(fa[i].real());
    
    return result;
}

int main() {
    int n,m=0;
    cin>>n>>m;
    vector<int> A; 
    vector<int> B;     
    for(int i=0;i<n+1;i++){
        int x;
        cin>>x;
        A.push_back(x);
    }
    for(int i=0;i<m+1;i++){
        int x;
        cin>>x;
        B.push_back(x);
    }
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    vector<int> C = multiply(A, B);
    reverse(C.begin(), C.end());
    for (int c : C)
        cout << c << " ";
    cout << endl; 

    return 0;
}