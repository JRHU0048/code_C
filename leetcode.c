T100 相同的树
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSameTree(struct TreeNode* p, struct TreeNode* q) { 
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

