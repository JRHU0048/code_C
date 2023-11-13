//二叉树的基本运算算法
#include <stdio.h>
#include <malloc.h>
#include<stdlib.h>
#define MaxSize 100

typedef int ElemType;
typedef struct node
{
	ElemType data;			//数据元素
	struct node* lchild;	//指向左孩子节点
	struct node* rchild;	//指向右孩子节点
} BTNode;
void CreateBTree(BTNode*& b, char* str)	//创建二叉树
{
	BTNode* St[MaxSize], * p = NULL;
	int top = -1, k, j = 0;
	int num;
	b = NULL;				//建立的二叉树初始时为空
	num = str[j];
	while (num != '\0')  	//str未扫描完时循环
	{
		switch (num)
		{
		case '(':top++;St[top] = p;k = 1; break;		//为左孩子节点
		case ')':top--;break;
		case ',':k = 2; break;                      		//为孩子节点右节点
		default:p = (BTNode*)malloc(sizeof(BTNode));
			p->data = num,p->lchild = p->rchild = NULL;
			if (b == NULL)                    	 	//*p为二叉树的根节点
				b = p;
			else  								//已建立二叉树根节点
			{
				switch (k)
				{
				case 1:St[top]->lchild = p;break;
				case 2:St[top]->rchild = p;break;
				}
			}
		}
		j++;
		num = str[j];
	}
}
void DestroyBTree(BTNode*& b)
{
	if (b != NULL)
	{
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
BTNode* FindNode(BTNode* b, ElemType x)
{
	BTNode* p;
	if (b == NULL)
		return NULL;
	else if (b->data == x)
	{
		return b;
	}
	else
	{
		p = FindNode(b->lchild, x);
		if (p != NULL)
			return p;
		else
			return FindNode(b->rchild, x);
	}
}
BTNode* LchildNode(BTNode* p)
{
	return p->lchild;
}
BTNode* RchildNode(BTNode* p)
{
	return p->rchild;
}
int BTHeight(BTNode* b)
{
	int lchildh, rchildh;
	if (b == NULL) return(0); 				//空树的高度为0
	else
	{
		lchildh = BTHeight(b->lchild);	//求左子树的高度为lchildh
		rchildh = BTHeight(b->rchild);	//求右子树的高度为rchildh
		return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}
void DispBTree(BTNode* b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");						//有孩子节点时才输出(
			DispBTree(b->lchild);				//递归处理左子树
			if (b->rchild != NULL) printf(",");	//有右孩子节点时才输出,
			DispBTree(b->rchild);				//递归处理右子树
			printf(")");						//有孩子节点时才输出)
		}
	}
}

int PreOrder(BTNode* b,int &n)  		//计算节点个数
{
	if (b != NULL)
	{
		n++;	//访问根结点
		PreOrder(b->lchild,n);	//先序遍历左子树
		PreOrder(b->rchild,n);	//先序遍历右子树
	}
	return n;
}

int DispLeaf(BTNode* b, int& m)   //计算叶子节点数
{
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
			m++;
		DispLeaf(b->lchild,m);
		DispLeaf(b->rchild,m);
	}
	return m;
}


//以下主函数用做调试
void main()
{
	int n = 0;
	int m = 0;
	BTNode *b;
	CreateBTree(b,"9(8(7,6(5,4)),3(2,1)))");
	printf("%d\n",FindNode(b, '7'));  //第一个参数是根节点指针，第二个参数是节点值，函数会返回指向找到的节点的指针
	printf("二叉树高度为：%d\n",BTHeight(b));
	printf("节点个数为：%d\n", PreOrder(b,n));
	printf("叶子节点个数为：%d\n", DispLeaf(b, m));
	DispBTree(b);
	printf("\n");
	system("pause");
}

//day_1113 相同二叉树的判断
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点
struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 创建一个新的二叉树节点
struct TreeNode* newNode(char data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 判断两棵树是否相同
int areTreesEqual(struct TreeNode* root1, struct TreeNode* root2) {
    if (root1 == NULL && root2 == NULL) {
        return 1;
    }
    if (root1 == NULL || root2 == NULL) {
        return 0;
    }
    return (root1->data == root2->data) &&
        areTreesEqual(root1->left, root2->left) &&
        areTreesEqual(root1->right, root2->right);
}

// 判断b1中是否存在与b2相同的子树
int isSubtree(struct TreeNode* b1, struct TreeNode* b2) {
    if (b1 == NULL) {
        return 0;
    }
    if (areTreesEqual(b1, b2)) {
        return 1;
    }
    return isSubtree(b1->left, b2) || isSubtree(b1->right, b2);
}

int main() {
    // 构建二叉树b1
    struct TreeNode* b1 = newNode('A');
    b1->left = newNode('B');
    b1->right = newNode('C');
    b1->left->left = newNode('D');
    b1->left->right = newNode('E');
    b1->right->left = newNode('F');
    b1->right->right = newNode('G');
    b1->right->right->right = newNode('I');
    b1->left->right->left = newNode('H');
    b1->left->right->left->left = newNode('J');
    b1->left->right->left->right = newNode('K');
    b1->left->right->left->right->left = newNode('L');
    b1->left->right->left->right->right = newNode('M');
    b1->left->right->left->right->right->right = newNode('N');

    // 构建正例子树b2(K)
    struct TreeNode* b2_positive1 = newNode('K');
    b2_positive1->left = newNode('L');
    b2_positive1->right = newNode('M');
    b2_positive1->right->right = newNode('N');

    // 构建正例子树b2(G)
    struct TreeNode* b2_positive2 = newNode('G');
    b2_positive2->right = newNode('I');

    //构建反例子树b2(K)
    struct TreeNode* b2_negative = newNode('K');
    b2_positive1->right = newNode('L');
    b2_positive1->left = newNode('M');
    b2_positive1->left->left = newNode('N');

    // 检查b1中是否存在与b2_positive相同的子树
    if (isSubtree(b1, b2_positive1)) {
        printf("b1中存在与b2_positive1相同的子树\n");
    }
    else {
        printf("b1中不存在与b2_positive1相同的子树\n");
    }
    if (isSubtree(b1, b2_positive2)) {
        printf("b1中存在与b2_positive2相同的子树\n");
    }
    else {
        printf("b1中不存在与b2_positive2相同的子树\n");
    }

    // 检查b1中是否存在与b2_negative相同的子树
    if (isSubtree(b1, b2_negative)) {
        printf("b1中存在与b2_negative相同的子树\n");
    }
    else {
        printf("b1中不存在与b2_negative相同的子树\n");
    }
    system("pause");
    return 0;
}
