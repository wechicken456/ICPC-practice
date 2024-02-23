#include<bits/stdc++.h>
#define v vector
#define u int
using namespace std;v<v<u>>e;v<u>l;v<u>z;u n,m;u t=0;void d(u q,u par){z[q]=l[q]=t++;for(u i=0;i<n;i++){if(e[q][i]){e[i][q]=0;if(i==par)continue;if(z[i]==-1){d(i,q);l[q]=min(l[q],l[i]);}else{l[q]=min(l[q],z[i]);}if(z[q]<l[i]){cout<<"NO";exit(0);}}}}u main(){cin>>n>>m;e.assign(n,v<u>(n,0));l.resize(n);z.assign(n,-1);for(u i=0;i<m;i++){u a,b;cin>>a>>b;a--;b--;e[a][b]=1;e[b][a]=1;}d(0,-1);cout<<"YES\n";for(u i=0;i<n;i++){for(u j=0;j<n;j++){if(e[i][j])cout<<i+1<<" "<<j+1<<"\n";}}}
