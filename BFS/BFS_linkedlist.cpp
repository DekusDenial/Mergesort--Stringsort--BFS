//Student: Dekus Lam
//Course: CSC 220
// Assignment 3: implementing BFS
//Instructor: Prof. Peter Brass
//NOTE: queue uses linked list; every state should have three moves that create path to lead to another state

#include<iostream>
#include "h_bl_tree.c"
using namespace std;

void BFS(int start, int target)
{
	tree_node_t *searchtree;
	searchtree=create_tree();

	struct queue_linkedlist
	{
		struct queue_linkedlist* next;
		int state;
	};

	bool found=false;
	queue_linkedlist *q, *temp, *iterator;
	q= (queue_linkedlist*) malloc(sizeof(queue_linkedlist) );
	iterator= (queue_linkedlist*) malloc(sizeof(queue_linkedlist) );
	int success, state, key, *state_in_tree, *find_ob;

	q->state=start;
	q->next=NULL;
	iterator->next=NULL;
	state_in_tree=(int*) malloc(sizeof(int));
	*state_in_tree=start;
	key=start;
	success=insert(searchtree, key, state_in_tree); //now the tree should have just one leaf

	while (q!=NULL)
	{
		state=q->state;   // take the starting state to firstly process
		q=q->next;
		if (state!=target)
		{
			if ((find_ob=find(searchtree, move1(state)))==NULL)
			{
				temp=q;
				if (temp==NULL)
				{
					iterator= (queue_linkedlist*) malloc(sizeof(queue_linkedlist) );
					iterator->state=move1(state);
					iterator->next=NULL;
					temp=iterator;
					q=temp;
					key=move1(state);
					state_in_tree=(int*) malloc(sizeof(int));
					*state_in_tree=state;    // make the key of the node the newly added reached state and the object value the same as the previous reached state
					success=insert(searchtree, key, state_in_tree);
				}
				else
				{
					while (temp!= NULL)  // in case of not empty, iterate to the last entry
					{
						if (temp->next==NULL)
							break;
						else
							temp=temp->next;
					}
					iterator= (queue_linkedlist*) malloc(sizeof(queue_linkedlist) );
					iterator->state=move1(state);
					iterator->next=NULL;
					temp->next=iterator;
					key=move1(state);
					state_in_tree=(int*) malloc(sizeof(int));
					*state_in_tree=state;
					success=insert(searchtree, key, state_in_tree);
				}
				if (key==target)    // force a break and terminate the searching, go on to printing
				{
					found=true;
					break;
				}
			}
			if ((find_ob=find(searchtree, move2(state)))==NULL)
			{
	     		temp=q;
				if (temp==NULL)
				{
					iterator= (queue_linkedlist*) malloc(sizeof(queue_linkedlist) );
					iterator->state=move2(state);
					iterator->next=NULL;
					temp=iterator;
					q=temp;
					key=move2(state);
					state_in_tree=(int*) malloc(sizeof(int));
					*state_in_tree=state;
					success=insert(searchtree, key, state_in_tree);
				}
				else
				{
					while (temp!= NULL)
					{
						if (temp->next==NULL)
							break;
						else
							temp=temp->next;
					}
					iterator= (queue_linkedlist*) malloc(sizeof(queue_linkedlist) );
					iterator->state=move2(state);
					iterator->next=NULL;
					temp->next=iterator;
					key=move2(state);
					state_in_tree=(int*) malloc(sizeof(int));
					*state_in_tree=state;
					success=insert(searchtree, key, state_in_tree);
				}
				if (key==target)
				{
					found=true;
					break;
				}
			}
			if ((find_ob=find(searchtree, move3(state)))==NULL)
			{
				temp=q;
				if (temp==NULL)
				{
					iterator= (queue_linkedlist*) malloc(sizeof(queue_linkedlist) );
					iterator->state=move3(state);
					iterator->next=NULL;
					temp=iterator;
					q=temp;
					key=move3(state);
					state_in_tree=(int*) malloc(sizeof(int));
					*state_in_tree=state;
					success=insert(searchtree, key, state_in_tree);
				}
				else
				{
					while (temp!= NULL)
					{
						if (temp->next==NULL)
							break;
						else
							temp=temp->next;
					}
					iterator= (queue_linkedlist*) malloc(sizeof(queue_linkedlist) );
					iterator->state=move3(state);
					iterator->next=NULL;
					temp->next=iterator;
					key=move3(state);
					state_in_tree=(int*) malloc(sizeof(int));
					*state_in_tree=state;
					success=insert(searchtree, key, state_in_tree);
				}
				if (key==target)
				{
					found=true;
					break;
				}
			}
		}

	}
	// right now, either the target state is found, or there is no target state in the graph
	// then do the printing
	if(!found)
		cout<<"The target state cannot be reached!\n"<<endl;
	else
	{
		cout<<target<<" <- ";
		find_ob=find(searchtree, target);
		while (*find_ob!=start)
		{
			cout<<*find_ob<<" <- ";
			find_ob=find(searchtree, *find_ob);   // find the previous state of this state, return the previous state of its previous state
			if(*find_ob==start)              // until this state is the starting state
			{
				cout<<*find_ob<<endl;
				break;
			}
			
		}
	}
}