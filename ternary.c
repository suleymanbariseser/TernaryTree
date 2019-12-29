//Süleyman Barýþ Eser	150116055

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
	int data;
	struct node *left;
	struct node *right;
	struct node *mid;
};

struct node* insert(struct node *root, int data); 
void print_inorder(struct node * tree);
struct node* newNode(int var);
struct node* deletion( struct node *root,struct node *header , int var );
struct node * maxValueNode(struct node* temp);
struct node * minValueNode(struct node* temp);
int find(struct node * head , int var);
void re_build(struct node *root,struct node *curr);

int main(){
	struct node *head;
	head = NULL;	
	struct node *root = head;
	FILE *f;
	int num;
	int var = 1 , a , choice;
	
	f = fopen("veri.txt" , "r");
	
	while(!feof(f)){
		fscanf(f , "%d" , &num);
		
		head = insert(head , num);
		root = head;
		
	}
	fclose(f);
	print_inorder(head);

	
	printf("\n'0 to exit'\n");
	printf("1->delete\n2->search\nEnter your choice: ");
	scanf("%d" , &choice);
	while(choice != 0){
		switch(choice){
			case 1:
				printf("enter a number for deletion: ");
				scanf("%d" , &var);
					
				a = find(head , var);
				head = deletion(root , head , var);
				root = head;
				printf("\n");
			
				if(!root){
					printf("\n\n\tTREE IS NULL\n\t'exit'");
					return 0;
				}
				print_inorder(head);
				
			break;
		
			case 2:
				printf("enter a value for search: ");
				scanf("%d" , &var);
				find(head , var);
				break;

			default:
				printf("please enter 1 or 2\n");
				break;	
		
		}
		printf("\n1->delete\n2->search\nEnter your choice: ");
		scanf("%d" , &choice);
		
		if(choice == 0 ){
			printf("\nEXIT");
			exit(0);
		}
	
	}
	if(choice == 0 ){
		printf("\nEXIT");
		exit(0);
	}
	
	
	return 0;
}

struct node* insert(struct node *head , int data){
	if(!head)
		return newNode(data);
	
	if(data < head->data)
		head->left = insert(head->left,data);
		
	else if(data > head->data && data <= pow(head->data , 2) )
		head->mid = insert(head->mid , data);
				
	else if(data > pow(head->data , 2 ))
		head->right = insert(head->right , data);
	
	
	return head;
}

struct node* deletion( struct node *root,struct node *header , int var ){
	if(!header)
		return header;
	
	if(var < header->data )
		header->left = deletion(root,header->left , var);
			
	else if(var > header->data && var <= pow(header->data , 2) )
		header->mid = deletion(root , header->mid , var);
	
	else if(var > pow(header->data , 2 ))
		header->right = deletion(root,header->right , var);
	
	//if the var equals to header->data
	else{
		/* 		O
			   /
			  O			*/
			  
		if(header->left && !header->mid && !header->right){
			struct node* temp = header->left;	
			free(header);
			return temp;
		}
		
		/* 		O
			    |
			    O			*/
			    
		else if(header->mid && !header->left && !header->right){
			struct node* temp = header->mid;	
			free(header);
			return temp;		
		}
		
		/* 		O
			     \
			 	  O			*/
			 	  
		else if(header->right && !header->left && !header->mid){
			struct node* temp = header->right;
			free(header);
			return temp;		
		}
		
		/* 		O
			    |\
			    O O			*/
		else if(header->mid && header->right && !header->left){
			struct node *temp = minValueNode(header->mid);
			header->data = temp->data;
			header->mid = deletion(root , header->mid , temp->data);
			//saðý daðýt
			struct node *temp2 = header->right;
			header->right = NULL;
			re_build(root,temp2);
			free(temp2);		
		}
	
		/*		 O
		 		/ \
			   O   O*/
		else if(header->left && header->right && !header->mid){
			struct node *temp = maxValueNode(header->left);
			header->data = temp->data;
			header->left = deletion(root , header->left, temp->data);
		}
		
		/*		 O				O
		  	    /|		OR	   /|\  
	           O O	 		  O	O O		*/
	           
		else if(header->left && header->mid){
			struct node *temp = maxValueNode(header->left);
			header->data = temp->data;
			header->left = deletion(root,header->left, temp->data);
			//mid'i tekrar daðýt
			//.....//
			struct node *temp2 = header->mid;
			header->mid = NULL;
			re_build(root , temp2);
			free(temp2);	
		}

		
		//if right,left and mid is NULL
		else{
			header = NULL;
		}
	
		
	}
	
	return header;
}

int find(struct node * head , int data){
	
	if(head){
	if(data < head->data){
		printf("%d--left-->" , head->data);
		find(head->left,data);
	}
		
		
	else if(data > head->data && data <= pow(head->data , 2) ){
		printf("%d--middle-->" , head->data);
		find(head->mid , data);
	}
	
				
	else if(data > pow(head->data , 2 )){
		printf("%d--right-->" , head->data);
		find(head->right , data);
	}
	
	else if(data == head->data){
		printf("%d\n",head->data);
		}
	}
	else{
		printf("\nERROR\nDOES NOT EXITS\n");
	}
}


//re-build
void re_build(struct node *root,struct node *curr){
	if(curr){
		re_build(root , curr->left);
		insert(root , curr->data);
		re_build(root , curr->mid);
		re_build(root , curr->right);
	}
}

//finding max value
struct node * maxValueNode(struct node* temp){
	struct node* current = temp;
	
	while(current->right || current->mid){
		if(current->right){
			current = current->right;
		}
		else{
			current = current->mid;
		}
	}
	return current;
}

//finding min value
struct node * minValueNode(struct node* temp){
	struct node* current = temp;
	
	while(current->left){
		if(current->left){
			current = current->left;
		}
		
	}
	return current;
}

//creating new Node
struct node* newNode(int var){
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = var;
	newNode->left = newNode->mid = newNode->right = NULL;
	
	return newNode;
}


void print_inorder(struct node * tree)
{
    if (tree)
    {
        print_inorder(tree->left);
        printf("%d\n",tree->data);
        print_inorder(tree->mid);
        print_inorder(tree->right);
    }
}



