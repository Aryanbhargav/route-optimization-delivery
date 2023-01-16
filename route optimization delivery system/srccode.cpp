#include<bits/stdc++.h>
using namespace std;
#define file_write freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
bool valid(int i, int j, int n, int m)
{
  if(i < 0 || j < 0 || i >= n || j >= m)
  return false;
  return true;
}
int dis(int x1, int y1, int x2, int y2)
{
   return (int)sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}


double disfloat(int x1, int y1, int x2, int y2)
{
   return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}


double func(vector<pair<int, int>> a){
 map<pair<int, int>, int> mp;
 map<int, pair<int, int>> ump;
 // mp[{phx, phy}] = 1;
 // ump[0] = {phx, phy}; 
 int cnt = 0;
 for(int i=0;i<a.size();i++){
  mp[a[i]] = cnt;
  ump[cnt] = a[i];
  cnt++;
 }
 // vector<vetor<int>> adj(cnt+1);
 double adj[cnt+1][cnt+1];
 memset(adj, 0, sizeof(adj));
 for(int i=0;i<cnt;i++){
  for(int j=0;j<cnt;j++){
   if(i == j) continue;
    // adj[cnt].push_back({j, dist(ump[i], ump[j])});
    adj[i][j] = disfloat(ump[i].first, ump[i].second, ump[j].first, ump[j].second);
  }
 }
 int s = 0;
 vector<int> vertex;
    for (int i = 0; i < cnt; i++)
        if (i != s)
            vertex.push_back(i);
    double min_path = INT_MAX;
    do {
        double current_pathweight = 0;
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += adj[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += adj[k][s];
        min_path = min(min_path, current_pathweight);
    } while (
        next_permutation(vertex.begin(), vertex.end()));
    return min_path;

}

int main()
{
   file_write
    int n,m;
    cout<<"Enter the size of City : "<<endl;
    cin>>n>>m;
    int shop_num;
    cout<<"Enter number of Pharmacy :"<<endl;
    cin>>shop_num;
    vector<pair<int,int>> v(shop_num);
    cout<<"Enter the coordinates of each Pharmacy :"<<endl;
    for(int i = 0; i < shop_num; i++)
    {
     int a,b;
     cin>>a>>b;
     v[i] = {a,b};
    }
    sort(v.begin(),v.end());
    int l = 1, r = 4, mr = -1, mpt = shop_num;
    // mpt = min possible tower
    // mr = min coverage radius
    vector<pair<int,int>> ans;
   while(l <= r)
   {
       int mid = (l+r)/2;  // current coverage radius
       vector<vector<set<int>>> mat(n,vector<set<int>>(m));
       for(int i = 0; i < shop_num; i++)
       {
        vector<vector<int>> vis(n,vector<int>(m));
        queue<pair<int,int>> q;
        q.push(v[i]);
        while(!q.empty())
        {
          pair<int,int> op = q.front();
          q.pop();
          if(vis[op.first][op.second] == 1)
          continue;
          mat[op.first][op.second].insert(i+1);
          vis[op.first][op.second] = 1;
          vector<int> x = {1,-1,0,0}, y = {0,0,1,-1};
          for(int j = 0; j < 4; j++)
          {
           int pp = x[j]+op.first,qq = y[j]+op.second;
           int d = dis(pp,qq,v[i].first,v[i].second);
           if(valid(pp,qq,n,m) && d <= mid)
           q.push({pp,qq});
          }
        }
       }

        int f = 0;
        for(int i = 0; i < n; i++)
        {
         for(int j = 0; j < m; j++)
         {
            if(mat[i][j].size() == 0)
            {
             f = 1;
             break;
            }
         } 
         if(f)
         break;
        }
        if(f)
        {
          l = mid+1;
          continue;
        }
        mr = mid;
        vector<pair<int,int>> cans;
       for(int i = 0; i < shop_num; i++)
       {
         vector<vector<int>> vis(n,vector<int>(m));
        queue<pair<int,int>> q;
        q.push(v[i]);
        while(!q.empty())
        {
          pair<int,int> op = q.front();
          q.pop();
          if(vis[op.first][op.second])
          continue;
          if(mat[op.first][op.second].size() == 1)
          {
            f = 1;
            break;
          }
          vis[op.first][op.second] = 1;
          vector<int> x = {1,-1,0,0}, y = {0,0,1,-1};
          for(int j = 0; j < 4; j++)
          {
           int pp = x[j]+op.first,qq = y[j]+op.second;
           int d = dis(pp,qq,v[i].first,v[i].second);
           if(valid(pp,qq,n,m) && d <= mid)
           q.push({pp,qq});
          }
        }
         if(f)
         cans.push_back(v[i]);
         else
         {
            for(int j = 0; j < n; j++)
            {
             for(int k = 0; k < m; k++)
             {
              if(mat[j][k].find(i+1) != mat[j][k].end())
              mat[j][k].erase(mat[j][k].find(i+1));
             }
            }
         }
       }
       if(cans.size() > mpt)
       l = mid+1;
       else
       {
        r = mid-1;
        mpt = cans.size();
        ans = cans;
       }
     }
   cout<<"Min coverage radius: "<<mr<<"\n";
   cout<<"Min number of shops: "<<mpt<<"\n";
   cout<<"Requried shops after removing redundant pharmacy :"<<endl;
   for(int i = 0 ;i  < mpt; i++)
   cout<<ans[i].first<<" "<<ans[i].second<<"\n";
  int phar[n][m],phar1[n][m],vis[n][m];
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      phar[i][j]=0,phar1[i][j]=0;
    }
  }
  for(int i=0;i<mpt;i++)
  phar[ans[i].first][ans[i].second]=i+1;
  pair<int,int> te;
  int x,y,val;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
    	
      if(phar[i][j]!=0)
      {
      	for(int k=0;k<n;k++)
      	{
      		for(int h=0;h<m;h++)
      		vis[k][h]=0;
		  }
        queue<pair<int,int> > q;
        val=phar[i][j];
        q.push({i,j});
        vis[i][j]=0;
        while(q.size())
        {
          te=q.front();
          q.pop();
          x=te.first,y=te.second;
            if(vis[x][y]!=0)
            continue;
            vis[x][y]=1;
          if(dis(x,y,i,j)<=mr)
          {
            phar1[x][y]=val;
          }
          else
          continue;
          if(valid(x-1,y,n,m)&&vis[x-1][y]==0)
            q.push({x-1,y});
          if(valid(x+1,y,n,m)&&vis[x+1][y]==0)
            q.push({x+1,y});
          if(valid(x,y-1,n,m)&&vis[x][y-1]==0)
            q.push({x,y-1});
          if(valid(x,y+1,n,m)&&vis[x][y+1]==0)
            q.push({x,y+1});
        }
      }
    }
  }
  cout<<"List of shops that cover a part of city :"<<endl;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
      cout<<phar1[i][j]<<" ";
    cout<<endl;
  }
  int number_of_customers;
  cout<<"Enter number of Customers :"<<endl;
  cin>>number_of_customers;
  
  vector<pair<int,int>> a[mpt+1];
  vector<vector<int>> adj;
  for(int i=0;i<mpt;i++)
  a[i].push_back({ans[i].first,ans[i].second});
  cout<<"Enter the coordinates of Customers :"<<endl;
  for(int i=0;i<number_of_customers;i++)
  {
  	cin>>x>>y;
  	if(phar[x][y]==0)
  	a[phar1[x][y]-1].push_back({x,y});
  }
  vector<double> distancemin;
  cout<<"clustering pharmacy with customers"<<endl;
  for(int i=0;i<mpt;i++)
  {
  	for(int j=0;j<a[i].size();j++)
  	{
  		cout<<a[i][j].first<<" "<<a[i][j].second<<"            ";

	  }
   double mndis = func(a[i]);

   // cout << mndis;
   distancemin.push_back(mndis);
	  cout<<endl;
   }
   for(int i=0;i<mpt;i++){
    cout <<"P"<<i+1<<" ( "<< a[i][0].first << " " << a[i][0].second << ") - Total Cost is :"<< distancemin[i] << endl;
   }
}

