//Student: Dekus Lam
//Course: CSC 220
// Assignment 3: implementing BFS
//Instructor: Prof. Peter Brass
//NOTE: using STL default queue class; every state should have three moves that create path to lead to another state
 
#include<iostream>
#include<queue>
#include "h_bl_tree.c"
using namespace std;

void BFS(int start, int target)
{
	tree_node_t *searchtree;
	searchtree=create_tree();

	bool found=false;
	queue<int> q;
	int success, state, key, *state_in_tree, *find_ob;

	q.push(start);
	state_in_tree=(int*) malloc(sizeof(int));
	*state_in_tree=start;
	key=start;
	success=insert(searchtree, key, state_in_tree); //now the tree should have just one leaf

	while (!q.empty())
	{
		state=q.front();   // take the starting state to firstly process
		q.pop();
		if (state!=target)
		{
			if ((find_ob=find(searchtree, move1(state)))==NULL)
			{
				q.push(move1(state));
				key=move1(state);
				state_in_tree=(int*) malloc(sizeof(int));
				*state_in_tree=state;// make the key of the node the newly added reached state and the object value the same as the previous reached state
				success=insert(searchtree, key, state_in_tree);
			}
			if (key==target)	// force a break and terminate the searching, go on to printing
			{
				found=true;
				break;
			}
		
			if ((find_ob=find(searchtree, move2(state)))==NULL)
			{
				q.push(move2(state));
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

			if ((find_ob=find(searchtree, move3(state)))==NULL)
			{
				q.push(move3(state));
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
			find_ob=find(searchtree, *find_ob);	// find the previous state of this state, return the previous state of its previous state
			if(*find_ob==start)				// until this state is the starting state
			{
				cout<<*find_ob<<endl;
				break;
			}
			
		}
	}
}