//Student: Dekus Lam
//Course: CSC 220 M, Spring 2009
//Instructor: Prof. Peter Brass
//NOTE: mergesort: sort list of integers, list MUST be NULL-terminated!!

struct listnode
{
	int value;
	struct listnode* next;
};

struct listnode* mergesort(struct listnode* data)
{
	struct listnode* first, *second, *list_iterator, *temp1, *temp2, *sorted;
	
	if (data==NULL || data->next==NULL)  // take care of empty list or a list that is of length one
		return data;

	list_iterator=data;		//this iterator will walk through the linked list	
	first=list_iterator;	//first will point to the first split list
	second=list_iterator->next;		//second will point to the second split list
	temp1=first;
	temp2=second;
	list_iterator=second->next;		// so this should start at the third node before going on to the while loop

	while ((temp2!=NULL && temp2->next!=NULL))
	{
		temp1->next=list_iterator;
		temp1=temp1->next;
		if (list_iterator==NULL)	//even though this is rude to break the loop, but just in case my way of doing this gives errors
			break;
		temp2->next=list_iterator->next;
		temp2=temp2->next;
		if (list_iterator->next==NULL)		// same here
			break;
		list_iterator=list_iterator->next->next;
	}
	temp1->next=NULL;	// this is needed since the only checking in the loop is for temp2, this is in case of temp1 is not terminated with NULL
	
	// so far we should have the main list split up into two, being pointed by pointers first and second
	// we could break each list into two smaller lists by recursive calls of mergesort()
	first=mergesort(first);
	second=mergesort(second);

	// by this point, we are going to sort two smaller lists, and at the end we will merge them into one
	// i know some of pointers below are not necessary, but i leave them the ways they are just to be safe
	temp1=first;
	temp2=second;
	sorted=new listnode;
	list_iterator=sorted;	//this iterator is reused to to keep linking new nodes from either temp1 or temp2

	while (temp1!=NULL && temp2!=NULL)
	{
		if (temp1->value < temp2->value)
		{
			list_iterator->next=temp1;
			list_iterator=list_iterator->next;
			temp1=temp1->next;
		}
		else
		{
			list_iterator->next=temp2;
			list_iterator=list_iterator->next;
			temp2=temp2->next;
		}
	}
	// now check which one has become empty
	if (temp1==NULL)
		list_iterator->next=temp2;
	else
		list_iterator->next=temp1;

	return sorted->next;	// since sorted is pointing to the node that created from the heap at the creation
}							// sorted->next will point to the first node of the sorted list