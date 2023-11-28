#并查集
typedef struct node
{
	int data;		//结点对应人的编号
	int rank;		//结点对应秩
	int parent;		//结点对应双亲下标
} UFSTree;

void MAKE_SET(UFSTree t[],int n)   //初始化并查集树
{
    for(int i=0;i<n;i++)
    {
        t[i].data=i;
        t[i].rank=0;
        t[i].parent=i;
    }
}

int FIND_SET(UFSTree t[],int x)     //查找元素所属的集合
{
    if(x!=t[x].parent)
        return(FIND_SET(t,t[x].parent));
    else
        return(x);
}

void UNION(UFSTree t[],int x,int y)   //两个集合的合并
{
    x=FIND_SET(t,x);
    y=FIND_SET(t,y);
    if(t[x].rank>t[y].rank)
        t[y].parent=x;
    else
    {
        t[x].parent=y;
        if(t[x].rank==t[y].rank)
            t[y].rank++;
    }
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) {
    int m=isConnectedSize;   //用来计数
    UFSTree t[isConnectedSize];       //初始化一个结构体数组
    MAKE_SET(t,isConnectedSize);      //初始化数组中的每一个编号
    for(int i=0;i<isConnectedSize;i++)
    {
        for(int j=0;j<isConnectedSize;j++)
        {
            if(isConnected[i][j]==1)
            {
                UNION(t,i,j);   //对于矩阵中的任何一项，如果有关联，将i,j所在的集合合并
            }
        }
    }
    for(int i=0;i<isConnectedSize;i++)    
    {
        int k=0;
        for(int j=i+1;j<isConnectedSize;j++)
        {
            if(FIND_SET(t,i)==FIND_SET(t,j))
            {
                k=1;
                break;
            }
        }
        if(k==1)
        m--;
    }
    return m;
}
