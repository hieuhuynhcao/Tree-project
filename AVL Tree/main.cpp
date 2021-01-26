#include<iostream> 
using namespace std;

typedef class Node* Ref;
class Node
{
public:
	int key;
	Ref left;
	Ref right;
	int height;
};

int max(int a, int b) {
	return a > b ? a : b;
}

// A utility function to get the 
// height of the tree 
int height(Ref pRoot)
{
	if (pRoot == NULL)
		return 0;
	return pRoot->height;
}

Ref newNode(int key)
{
	Ref node = new Node;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // new node is initially 
					// added at leaf 
	return(node);
}

Ref rightRotate(Ref y)
{
	Ref x = y->left;
	Ref T2 = x->right;

	// Perform rotation 
	x->right = y;
	y->left = T2;

	// Update heights 
	y->height = max(height(y->left),
		height(y->right)) + 1;
	x->height = max(height(x->left),
		height(x->right)) + 1;

	// Return new root 
	return x;
}

Node* leftRotate(Node* x)
{
	Node* y = x->right;
	Node* T2 = y->left;

	// Perform rotation 
	y->left = x;
	x->right = T2;

	// Update heights 
	x->height = max(height(x->left),
		height(x->right)) + 1;
	y->height = max(height(y->left),
		height(y->right)) + 1;

	// Return new root 
	return y;
}

// Get Balance factor of node N 
int getBalance(Node* N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key)
{
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else // Equal keys are not allowed in BST 
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),
		height(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case 
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case 
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case 
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

void preOrder(Node* root)
{
	if (root != NULL)
	{
		cout << root->key << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

int Level(Node* pRoot, Node* p) {
	if (!pRoot)
		return 0;

}

void print2DUtil(Ref root, int space = 0)
{
	// Base case  
	if (root == NULL)
		return;

	// Increase distance between levels  
	space += 10;

	// Process right child first  
	print2DUtil(root->right, space);

	// Print current node after space  
	// count  
	cout << endl;
	for (int i = 10; i < space; i++)
		cout << " ";
	cout << root->key << "\n";

	// Process left child  
	print2DUtil(root->left, space);
}

// Driver Code 
int main()
{
	Node* root = NULL;

	/* Constructing tree given in
	the above figure */
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 25);

	/* The constructed AVL Tree would be
				30
			/ \
			20 40
			/ \ \
		10 25 50
	*/
	cout << "Preorder traversal of the "
		"constructed AVL tree is \n";
	preOrder(root);
	print2DUtil(root);

	return 0;
}

