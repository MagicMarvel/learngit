//#pragma GCC optimize(2)
#include<set>
#include<stack>
#include<vector>
#include<string>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include <cmath>
using namespace std;

struct edgeData{
    int from,to,next;
}edge[500001*2];

int father[500001*4][100];

int depth[500001*4];

int log_2[500001*4];

int home[500001*4];

bool myHash[500001*4];

template <typename T> void adjacencyListMake(T *edge, int *home, int a, int b, int &v)
// 放进edge里的结构体必须要有next,from,to,这几个,home指的是导航数组.如果edge[.].next为0说明结束了没有下一条边了，
// v用于计数，一定要记得初始化为0
{
        v++;
        edge[v].next=home[a];
        edge[v].from=a;
        edge[v].to=b;
        home[a]=v;
}


int LCA(int x,int y){
    if (depth[x]<depth[y]) swap(x,y);
    while ((depth[x]-depth[y])!=0){
        x=father[x][log_2[depth[x]-depth[y]]-1];
    }
    if (x==y) return x;
    int d;
    d=depth[x];
    for (int i=log_2[d]-1;i>=0;i--){
        if (father[x][i]!=father[y][i]){
            x=father[x][i];
            y=father[y][i];
            d=d-pow(2,i);
        }
    }
    return father[x][0];
}


void dfs(int v,int past) {
//    if (v==0){
//        cout<<"V==0"<<endl;
//    }
//    if (v==45898&&past==0){
//        cout<<"now"<<endl;
//    }
    if (v==826&&past==207841){
        cout<<"error 826"<<endl;
    }
//    cout<<v<<" "<<past<<endl;
    myHash[v]=true;
    depth[v]=depth[past]+1;
    father[v][0]=past;
    for (int i=1;i<=log_2[depth[v]];i++){
        father[v][i]=father[father[v][i-1]][i-1];
    }
    for (int i=home[v];i!=0;i=edge[i].next){
        int to=edge[i].to;
        if (!myHash[to]){
            if (to==45898&&v==0){
//                cout<<"to==0"<<endl;
            }
            dfs(to,v);
        }
    }
//    cout<<v<<" "<<past<<endl;
}

void LCAInitialize(int n, int root) {
    for (int i=0;i<=n;i++){
        log_2[i]=log(i)/log(2)+1;
    }
    myHash[0]==true;
    dfs(root,0);
}

int main(){
    int aa,bb;
    std::ios::sync_with_stdio(false);
//    freopen("read.txt","r",stdin);  //"CON" can output to screen (in stdio.h)
//    freopen("write.txt","w",stdout);
    int root,n,q,i,tmp;
    cin>>n>>q>>root;
    tmp=0;
    for (i=1;i<=n-1;i++){
        cin>>aa>>bb;
        adjacencyListMake(edge, home, aa, bb, tmp);
        adjacencyListMake(edge, home, bb, aa, tmp);
    }

    tmp=0;
//    cout<<"YES"<<endl;
    for (i=1;i<=q;i++){
        cin>>aa>>bb;
        LCAInitialize(n,root);
        cout<<LCA(aa,bb)<<endl;
    }
    return 0;
}