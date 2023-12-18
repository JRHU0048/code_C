T100.相同的树
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {      //始终要记住，你处理的对象是当前节点，有三种情况，分别讨论，然后直接递归左子树和右子树即可，注意力放在当前节点上！
    if (p == NULL && q == NULL) { 
        return true; 
    } else if (p == NULL || q == NULL) {     //若p和q同时为NULL那么将在第一个if语句中执行true,所以本语句只能有一个为NULL
        return false; 
    } else if (p->val != q->val) {
        return false;
    } else {
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);   //递归调用 
    }
}

T83.删除排序链表中的重复元素
代码一：注意，因为程序的返回值为一个链表，所以不能直接在head节点上进行改动，应该先将head节点赋值给一个新节点，在新节点上进行操作！！！
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    if(head==NULL||head->next==NULL)   //第一、二节点为空节点时
    return head; 
    struct ListNode*p=head; 
    while(p->next!=NULL)    //使用while循环进行遍历
    {
        if(p->val==p->next->val)
        p->next=p->next->next;
        else
        p=p->next;
    }
    return head;
}
代码二：使用递归调用的方法进行遍历
使用递归调用的函数基本类似，但是leetcode上面跑不了，不知道为什么呜呜呜呜。

T94.二叉树的中序遍历
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left; 
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().  
 */
 //中序遍历的特点：中序遍历左子树，访问根节点，中序遍历右子树。
//利用递归思想进行
void InOrder(struct TreeNode* root,int *res, int* returnSize){ 
    if(root!=NULL)
    {
        InOrder(root->left,res,returnSize);
        res[(*returnSize)++]=root->val; 
        InOrder(root->right,res,returnSize);
    }
}
int* inorderTraversal(struct TreeNode* root, int* returnSize) {  
    int *res=malloc(sizeof(int)*2000);   //初始化一个数组用来存储结果
    *returnSize=0;   //*是对指针的解引用，&是取变量的地址，两者的作用是不同的，*returnSize 就表示 直接操作 returnSize 指向的变量，可以理解就是参数的一个引用，别名
    InOrder(root,res,returnSize);
    return res;
}

T104.二叉树的最大深度
/**
 * Definition for a binary tree node. 
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) { 
    int ldepth,rdepth;
    if(root==NULL)
    return NULL;
    else{
        ldepth=maxDepth(root->left);
        rdepth=maxDepth(root->right);
        return (ldepth>rdepth)?(ldepth+1):(rdepth+1); 
    }
}
//官方解法：
int maxDepth(struct TreeNode *root) {
    if (root == NULL) return 0;
    return fmax(maxDepth(root->left), maxDepth(root->right)) + 1; 
}

//刷题感悟：
//struct TreeNode* q = malloc(sizeof(struct TreeNode)); 创建了一个动态分配的内存空间，并将 q 指向该空间，而 struct TreeNode* p; 只是声明了一个未初始化的指针。

day1217
T1768 
char * mergeAlternately(char * word1, char * word2){
    int s1=strlen(word1);
    int s2=strlen(word2);
    char* a=(char *)malloc(sizeof(char)*(s1+s2+1)); 
    int i=0,t=0; 
   while(i<s1||i<s2)
   {
       if(i<s1)
       {
           a[t++]=word1[i];
       }
       if(i<s2)
       {
           a[t++]=word2[i];
       }
       i++;
   }
   a[t]='\0';
    return a;
}  //在C语言中，局部变量（例如函数内部声明的变量）的生命周期仅限于它们所在的代码块。一旦函数返回，a数组就会被销毁，因此无法将其作为函数返回值返回。

//为了解决这个问题，你可以使用动态分配内存的方法来分配足够的空间来存储合并后的字符串。可以使用malloc函数来动态分配内存，然后使用free函数来释放所分配的内存。
//在C语言中，字符串以空字符\0结尾，而不是NULL指针。因此，正确的判断条件应该是word1[i] != '\0'或word1[i] != 0。

242. 有效的字母异位词
bool isAnagram(char* s, char* t) {
    int temp[26]={0};
    for(int i=0;s[i]!='\0';i++)
    {
        int n = s[i]-97;
        temp[n]++;
    }
    for(int j=0;t[j]!='\0';j++)
    {
        int m = t[j]-97;
        temp[m]--;
    }
    for(int i=0;i<26;i++)
    {
        if(temp[i]!=0)
        return false;
    }
    return true;
}

283. 移动零
void moveZeroes(int* nums, int numsSize){
    int i=0,k=0,m=0;
    for(i=0;i<numsSize;i++){
        if(nums[i]==0){
            k++;
        }
    }
    for(int t=0;t<numsSize;t++){
        if(nums[t]!=0){
            nums[m]=nums[t];
            m++;
        }
    }
    for(int n=numsSize-k;n<numsSize;n++){
            nums[n]=0;
        }
}

1822. 数组元素积的符号
int arraySign(int* nums, int numsSize) {
    int c=1;   //不能将nums数组中的元素全部相乘，会超出int类型数据长度
    for(int i=0;i<numsSize;i++)
    {
        if(nums[i]<0)
        {
            c*=-1;   //判断负数的个数
        }
        else if(nums[i]==0)
        {
            return 0;   //出现一个0结果直接为0
        }
    }
    if(c<0)
    return -1;
    else 
    return 1;
}
//数组有0，则马上返回0；只用记录数组中负数个数，负数个数为偶数，则数组元素乘积为正，返回1；反之，返回-1。

1502. 判断能否形成等差数列
bool canMakeArithmeticProgression(int* arr, int arrSize) {
    for(int i=0;i<arrSize;i++)
    {
        for(int j=i+1;j<arrSize;j++)
        {
            if(arr[i]<arr[j])   //从大到小排
            {
            int t=arr[i];
            arr[i]=arr[j];
            arr[j]=t;
            }
        }
    }
    int d=arr[1]-arr[0];
    for(int i=1;i<arrSize-1;i++)
    {
        if(arr[i+1]-arr[i]!=d)
        return false;
    }
    return true;
}

896. 单调数列
bool isMonotonic(int* nums, int numsSize) {
    int j=0;
    long long t;
    while(j+1<numsSize&&nums[j+1]-nums[j]==0)
    {
        j++;
    }
    if(j==numsSize-1){
        return true;
    }else{
        t=nums[j+1]-nums[j];
    }
    
    for(int i=0;i<numsSize-1;i++)
    {
        if((nums[i+1]-nums[i])*t<0){
            return false;
        }
    }
    return true;
}

709. 转换成小写字母
char* toLowerCase(char* s) {
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]<=90&&s[i]>=65)
        {
            s[i]=s[i]+32;
        }
    }
    return s;
}

1672. 最富有客户的资产总量
int maximumWealth(int** accounts, int accountsSize, int* accountsColSize) {  //accountsSize表示矩阵的行数；
    //accountsColSize表示矩阵的列数且是一个指向数组列大小的指针，在调用时需要指出具体的行数，例如accountsColSize[i]-->表示矩阵的第i行有多少列
    
    int maxsum=0;
    for(int i=0;i<accountsSize;i++)
    {
        int y=0;
        for(int j=0;j<accountsColSize[i];j++)
        {
            y+=accounts[i][j];
        }
        if(maxsum<y)
        {
            maxsum=y;
        }
    }
    return maxsum;
}
//accountsColSize 是指向数组列大小的指针，因此需要使用 accountsColSize[i] 而不是 accountsColSize

1523. 在区间范围内统计奇数数目
int countOdds(int low, int high){
    int t=0;
    if(low%2==0 && high%2==0)
    {
        return (high-low)/2;
    }else 
    return (high-low)/2+1;
}
解法二：
int countOdds(int low, int high){
        return (high - low) / 2 + (low % 2 || high % 2);
}
作者：Arw
链接：https://leetcode.cn/problems/count-odd-numbers-in-an-interval-range/solutions/2565528/cyu-yan-yi-xing-dai-ma-gao-ding-by-qui22-42p9/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

860. 柠檬水找零
bool lemonadeChange(int* bills, int billsSize) {
    int k=0,l=0;
    for(int i=0;i<billsSize;i++)
    {
        if(bills[i]==5)
        {
            k++;
        }else if(bills[i]==10)
        {
            k--;
            l++;
        }
        else if(bills[i]==20)
        {
            if(l>0)
            {
                l--;
                k--;
            }
            else if(l==0)
            {
                k=k-3;
            }
        }
        if(k<0||l<0)
        return false;
    }
    return true;
}

976. 三角形的最大周长
int largestPerimeter(int* nums, int numsSize) {
    for(int i=0;i<numsSize;i++)  //排序:大->小
    {
        for(int j=i+1;j<numsSize;j++)
        {
            if(nums[i]<nums[j])
            {
                int t=nums[i];
                nums[i]=nums[j];
                nums[j]=t;
            }
        }
    }
    int k=0;
    while(k+2<numsSize&&nums[k]-nums[k+1]>=nums[k+2]){
        k++;
    }
    if(k+2<numsSize){
        return nums[k]+nums[k+1]+nums[k+2];
    }
    else 
    return 0;
}

73. 矩阵置零
void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int m=matrixSize;
    int n= matrixColSize[0];
    int t=0;
    int row[n+m],col[n+m];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(matrix[i][j]==0)
            {
                row[t]=i;
                col[t]=j;
                t++;
            }
        }
    }
    for(int i=0;i<t;i++)
    {
        int x=row[i];
        int y=col[i];
        for(int j=0;j<n;j++)
        {
            matrix[x][j]=0;
        }
        for(int k=0;k<m;k++)
        {
            matrix[k][y]=0;
        }
    }
}

234. 回文链表
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool isPalindrome(struct ListNode* head) {
    int m[100000],t=0;
    while(head != NULL)
    {
        m[t++]=head->val;
        head=head->next;
    }
    for(int i=0,j=t-1;i<j;i++,j--)
    {
        if(m[i]!=m[j])
        {
        return false;
        }
    }
    return true;
}
//第一步： 遍历链表并将值复制到数组中，O(n)O(n)O(n)。
第二步：双指针判断是否为回文，执行了 O(n/2)O(n/2)O(n/2) 次的判断，即 O(n)O(n)O(n)。
总的时间复杂度：O(2n)=O(n)O(2n) = O(n)O(2n)=O(n)。

