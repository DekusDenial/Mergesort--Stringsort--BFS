//Student: Dekus Lam
//Course: CSC 220
//Instructor: Prof. Peter Brass
//NOTE:stringsort: sort list of strings, list MUST be NULL-terminated!!

#include<iostream>
using namespace std;

struct listnode
{
	struct listnode* next;
	char* word;
};

struct listnode* stringsort (struct listnode* data, int start_pos)
{
	if (data==NULL || data->next==NULL)  // take care of empty list or a list that is of length one
		return data;

	listnode** arr=new listnode*[256], *iterator=data, *temp;
	int index;

	for (int i=0;i<256;i++)
	{
		arr[i]=NULL;
	}

	while (iterator != NULL)
	{
		index=(int) iterator->word[start_pos]; // find out which position

		if (arr[index]==NULL)   // this must apply at the first time assignment
		{
			arr[index]=iterator;
			iterator=iterator->next;
			arr[index]->next=NULL;   // terminate the pointers with NULL
		}
		else
		{
			temp=arr[index];
			while (temp->next != NULL)	// keep iterating the temp pointer up to the last node which points to NULL
				temp=temp->next;
			temp->next=iterator;		// make that node points to a new node
			iterator=iterator->next;
			temp=temp->next;			// go to the new node, also the last node
			temp->next=NULL;			// terminate the last node with NULL
		}
	}
	// bucket sort now finished, going onto recursive sort on every nonempty bucket except (int) '\0'

	for (int i=0; i<256; i++)
	{
		if (arr[i]!=NULL && i!=(int) '\0')	// finding any nonempty bucket except arr[0]
		{
			arr[i]=stringsort(arr[i], start_pos+1);	// sort the current list
		}
	}

	listnode* sorted=NULL;
	temp=new listnode;
	for (int i=0; i<256; i++)
	{
		if (arr[i]!=NULL)
		{
			temp->next=arr[i];
			while (temp->next!=NULL)
				temp=temp->next;
			if (sorted==NULL)
				sorted=arr[i];
		}
	}
	delete [] arr;
	return sorted;
}