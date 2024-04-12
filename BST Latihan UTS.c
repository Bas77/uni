#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	struct node *left;
	struct node *right;
	int val;
}node;

node *initNode(int val){
	node *newNode = (node*)malloc(sizeof(node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->val = val;
	return newNode;
}

void insertBST(node **root, int val){
	node *newNode = initNode(val);
	if(*root == NULL){
		*root = newNode;
		return;
	}
	node *curr = *root;
	while(1){
		if(val < curr->val){
			if(curr->left != NULL){
				curr = curr->left;
			} else{
				curr->left = newNode;
				return;
			}
		}
		
		if(val > curr->val){
			if(curr->right != NULL){
				curr = curr->right;
			} else{
				curr->right = newNode;
				return;
			}
		}
	}
}

void insertBSTRec(node **root, int val){
	if(val == (*root)->val) return;
	
	if(val < (*root)->val){
		if((*root)->left == NULL){
			(*root)->left = initNode(val);
			return;
		}
		insertBSTRec(&((*root)->left), val);
	} else{
		if((*root)->right == NULL){
			(*root)->right = initNode(val);
			return;
		}
		insertBSTRec(&((*root)->right),val);
	}
}

node *deleteBST(node *root, int key){
	//If there is no node in the BST
	if(root == NULL) return NULL;
	
	//Search for the node with the value that we want to delete
	if(key < root->val) root->left = deleteBST(root->left, key);
	else if(key > root->val) root->right = deleteBST(root->right, key);
	
	//Found
	else{
		//If there is no children
		if(root->left == NULL && root->right == NULL){
			free(root);
			return NULL;
		}
		
		//If there is one children
		if(root->left != NULL && root->right == NULL){
			node *temp = root->left;
			free(root);
			return temp;
		}
		if(root->left == NULL && root->right != NULL){
			node *temp = root->right;
			free(root);
			return temp;
		}
		
		//If there is two children
			//Find the successor of the right subtree
			node *temp = root->right;
			while(temp->left != NULL){
				temp = temp->left;
			}
		//Change the value and delete successor
		root->val = temp->val;
		root->right = deleteBST(root->right, root->val);
	}
	return root;
}
void preorderBST(node *root){
	if(root == NULL) return;
	printf("|%d|", root->val);
	preorderBST(root->left);
	preorderBST(root->right);
}

bool searchBST(node *root, int key){
	if(root->val == key) return true;
	if(root->left != NULL && key < root->val) return searchBST(root->left, key);
	if(root->right != NULL && key > root->val) return searchBST(root->right, key);
	return false;
}

int main(){
	node *root = NULL;
	insertBST(&root, 1);
	insertBSTRec(&root, 2);
	insertBST(&root, -3);
	insertBSTRec(&root, 0);
	preorderBST(root);
	puts("");
	root = deleteBST(root, 1);
	preorderBST(root);
	printf("%s", searchBST(root, 1)?"True":"False");
}
