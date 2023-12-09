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

T94. 二叉树的中序遍历
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


