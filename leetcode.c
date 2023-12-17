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
