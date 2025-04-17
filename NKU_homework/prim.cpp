//😺
#include<iostream>
#include<vector>
#include<queue>
#include<climits> //提供INT_MAX
using namespace std;

typedef unsigned long long int ull;

//最小字典序：1.选择加入时需要考虑 2.更新时需要考虑
struct Edge{
    int to; //目标节点
    int weight; //边权重
    int id; //边编号
};

struct QueueElement{
    int dist; //到连通分支的最小距离
    int node; //当前节点编号
    int edge_id;   //边编号
    //自定义比较规则：优先距离小，其次边编号小 为优先队列提供判断逻辑
    bool operator>(const QueueElement& other) const{
        if(dist==other.dist){
            return edge_id>other.edge_id;
        }
        return dist>other.dist;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin>>n>>m;
    vector<vector<Edge>>adj(n); //使用了Edge
    //1.构建临接表
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u-1].push_back({v-1,w,i});
        adj[v-1].push_back({u-1,w,i});
    }
    vector<int>dist(n,INT_MAX);
    vector<bool>vis(n,false);
    vector<int>edge_num(n,-1); //表示插入这个节点所使用的边
    //优先队列元素：(距离, 当前节点, 边编号)
    priority_queue<QueueElement,
                    vector<QueueElement>,
                    greater<QueueElement> >pq;
    dist[0]=0;
    pq.push({0,0,-1});
    //3.选择dist最小的节点
    while(!pq.empty()){
        auto [d,u,e]=pq.top();
        pq.pop();
        
        if(vis[u])continue;
        vis[u]=true;

        if(e!=-1){
            edge_num[u]=e; //添加了节点u使用了e这条边
        }
        //2.更新dist
        for(auto& edge:adj[u]){
            int v=edge.to;
            int w=edge.weight;
            int id=edge.id;
            //发现更小距离 或 距离相等但边编号更小
            if(!vis[v] && (w<dist[v] || (w==dist[v]&&id<edge_num[v]))){
                dist[v]=w;
                edge_num[v]=id;//这一步是必要的，因为对一个未加入的节点来说也有可能需要调整为更小的边
                pq.push({dist[v],v,id});//更新pq
            }
        }
    }
    ull total_weight=0;
    //权重和
    for(int i=0;i<n;i++){
        if(!vis[i]){
            cout<<"-1"<<endl;
            return 0;
        }
        total_weight+=dist[i];
    }
    //计算异或结果
    int xor_result=0;
    for(int i=1;i<n;i++){
        xor_result^=edge_num[i];
    }

    cout<<total_weight<<" "<<xor_result<<endl;
    return 0;
}


//😺
#include<iostream>
#include<vector>
#include<queue>
#include<climits> //提供INT_MAX
using namespace std;

typedef unsigned long long int ull;

//最小字典序：1.选择加入时需要考虑 2.更新时需要考虑
struct Edge{
    int to; //目标节点
    int weight; //边权重
    int id; //边编号
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin>>n>>m;
    vector<vector<Edge>>adj(n); //使用了Edge
    //1.构建临接表
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u-1].push_back({v-1,w,i});
        adj[v-1].push_back({u-1,w,i});
    }
    vector<int>dist(n,INT_MAX);
    vector<bool>vis(n,false);
    vector<int>edge_num(n,-1); //表示插入这个节点所使用的边
    //优先队列元素：(距离, 当前节点, 边编号)
    //​​优先队列比较的是 tuple 的第一个元素 距离（dist）​​若相等，接着会比较第二个、第三个...
    priority_queue<tuple<int,int,int>,
                    vector<tuple<int,int,int>>,
                    greater<tuple<int,int,int>> >pq;
    dist[0]=0;
    pq.emplace(0,-1,0);
    //3.选择dist最小的节点
    while(!pq.empty()){
        auto [d,e,u]=pq.top();
        pq.pop();
        
        if(vis[u])continue;
        vis[u]=true;

        if(e!=-1){
            edge_num[u]=e; //添加了节点u使用了e这条边
        }
        //2.更新dist
        for(auto& edge:adj[u]){
            int v=edge.to;
            int w=edge.weight;
            int id=edge.id;
            //发现更小距离 或 距离相等但边编号更小
            if(!vis[v] && (w<dist[v] || (w==dist[v]&&id<edge_num[v]))){
                dist[v]=w;
                edge_num[v]=id;//这一步是必要的，因为对一个未加入的节点来说也有可能需要调整为更小的边
                pq.emplace(dist[v],id,v);//更新pq
            }
        }
    }
    ull total_weight=0;
    //权重和
    for(int i=0;i<n;i++){
        if(!vis[i]){
            cout<<"-1"<<endl;
            return 0;
        }
        total_weight+=dist[i];
    }
    //计算异或结果
    int xor_result=0;
    for(int i=1;i<n;i++){
        xor_result^=edge_num[i];
    }

    cout<<total_weight<<" "<<xor_result<<endl;
    return 0;
}