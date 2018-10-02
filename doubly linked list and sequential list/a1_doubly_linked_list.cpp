// Sunghoon Ahn 20615061
#include "a1_doubly_linked_list.hpp"
#include <iostream>

using namespace std;
DoublyLinkedList::Node::Node(DataType data)
{
	value = data;
	next = NULL;
	prev = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
	size_= 0;
	head_ = NULL;
	tail_ = NULL;



}

DoublyLinkedList::~DoublyLinkedList() // Create node space to store the head and delete from very beginning to end sequentially
{
	Node*temp = head_;
	Node*space;
	for(int i=0; i<size_; i++)
	{
 		space = temp->next;
		delete temp;
		temp = space;
	}
}

unsigned int DoublyLinkedList::size() const
{
 	return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
	return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
	if (size_ == 0)
		return true;
	else
		return false;
}

bool DoublyLinkedList::full() const
{
	if (size_== CAPACITY)
		return true;
	else
		return false;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const // Use for loop to reach the given index and return the value in that index
{
	Node*newhead = head_;
	if(index < size_)
	{

		for(int i=0; i<index; i++)
		{
			newhead = newhead -> next;
		}
		return newhead -> value;

	}
	else
		 return tail_-> value;
}

unsigned int DoublyLinkedList::search(DataType value) const // Keep looping until it finds the given value and return i which is the index of given value
{
	Node * newhead = head_;
	for( int i=0; i< size_; i++)
	{
		if (newhead->value ==  value)
		{
		return	i;
		}
		newhead = newhead -> next;
	}
	return size_;

}

void DoublyLinkedList::print() const //Use for loop to print all the values in the list
{
	Node * newhead = head_;
	for(int i= 0; i< size_; i ++){
		cout<< newhead-> value << endl;
		newhead = newhead ->next;
	}
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const // Use for loop to reach the given index and return the pointer of the given index
{
	if (index < size_){
		Node * newhead = head_;
		for(int i=0; i< index; i++){
			newhead = newhead -> next;
		}
		return newhead;
	}
	else
	 return NULL;


}

bool DoublyLinkedList::insert(DataType value, unsigned int index) // The way to put the value in the list should be different according to the position of the index
{
	Node*newhead = head_;
	Node*insertVal = new Node(value);
	Node*temp;

	if (index<=size_)
	{
		if(index==0)
		{
			insert_front(value);
			return true;
		}
		if(index==size_)
		{
			insert_back(value);
		}
		else
		{
			for(int i=0; i<index; i++)
			{
				temp = newhead;
				newhead = newhead -> next;
			}

			temp->next = insertVal;
			newhead->prev = insertVal;
			insertVal->prev = temp;
			insertVal->next = newhead;
			size_++;
			return true;

		}
	}
	else
		return false;

}

bool DoublyLinkedList::insert_front(DataType value) // If the head is null, head and tail should point the value. If not, head and the next value of head should point the value
{
	Node*insertFront = new Node(value);
	if(head_!=NULL)
	{
		insertFront->next = head_;
		head_->prev = insertFront;
		head_ = insertFront;
		size_++;
		return true;
	}
	if(head_==NULL)
	{
		head_ = insertFront;
		tail_ = insertFront;
		size_++;
		return true;
	}
	else
		return false;


}

bool DoublyLinkedList::insert_back(DataType value) // same as insert_front
{
	Node*insertBack = new Node(value);
	if(tail_==NULL)
	{
		tail_ = insertBack;
		head_ = insertBack;
		size_++;
		return true;
	}
	if(tail_!=NULL)
	{
		Node*last = tail_;
		last->next = insertBack;
		insertBack->prev = last;
		tail_ = insertBack;
		size_++;
		return true;
	}
	else
	return false;
}

bool DoublyLinkedList::remove(unsigned int index) // According to the position of the index, three different ways to remove the value of the given index were used
{
	Node* temp = head_;
			if(size_ == 0)
			return false;

			if(index==0)
			{
				remove_front();

			}
			if(index==size_-1)
			{
				remove_back();
				return true;

			}
			if(index<size_)
			{
				for (int i = 0; i < index; i++)
				{
				temp = temp -> next;
				}
				Node*prevVal = temp -> prev;
				Node*nextVal = temp -> next;

				prevVal -> next = nextVal;
				nextVal -> prev = prevVal;
				return true;
			}

	else
		return false;


}

bool DoublyLinkedList::remove_front() //If size is 1, head and tail should point null and delete the value. If not, head should first point the next value of the value you want to delete and then delete
{
	Node*newhead = head_;
	if(size_==0)
	{
		return false;
	}
	if(size_ == 1)
	{
		head_=NULL;
		tail_=NULL;
		delete newhead;
		size_--;
		return true;

	}
	else
	{
		head_ = newhead->next;
		delete newhead;
		newhead = NULL;
		head_ -> prev = NULL;
		size_--;
		return true;

	}


}

bool DoublyLinkedList::remove_back() // same as remove_front
{
	Node*newtail = tail_;

	if(size_ ==1)
	{
		tail_ = NULL;
		head_ = NULL;
		delete newtail;
		size_--;
		return true;
	}
	if (size_>1)
	{
		tail_ = newtail->prev;
		delete newtail;
		newtail = NULL;
		tail_-> next = NULL;
		size_--;
		return true;
	}
	else
		return false;

}

bool DoublyLinkedList::replace(unsigned int index, DataType value) // Simply, find the value of given index using for loop and replace it
{
	Node* temp = head_;
	if (index < size_ )
	{
		for(int i = 0; i < index; i++)
		{
			temp= temp->next;
		}
		temp-> value = value;
		return true;
	}
	else
		return false;

}

bool DoublyLinkedList::is_sorted_asc() const // Everytime the while statement is satisfied, the count will increase by one and if the count is equal to size-1, it returns true
{
	Node*temp = head_;

	int count=0;
	if(size_==0 || size_==1)
		return true;
	else
	{
		while(temp->next!=NULL&&temp->value<=temp->next->value)
		{
			temp = temp->next;
			count++;
		}
		if(count==size_-1)
			return true;
		else
			return false;
	}
}

bool DoublyLinkedList::is_sorted_desc() const // same as is_sorted,asc
{
	Node*temp = head_;
	int count=0;
	if(size_==0 || size_==1)
		return true;
	else
	while(temp->next!=NULL&&temp->value>=temp->next->value)
	{
		temp = temp->next;
		count++;
	}
	if(count==size_-1)
		return true;
	else
		return false;
}

bool DoublyLinkedList::insert_sorted_asc(DataType val) // Check whether the list is ascending order or not using is_sorted_asc function and use insert functions according the position of value
{
	Node*temp = head_;
	Node*insertVal = new Node(val);
	Node*tempNext;
	int count=0;


	if(is_sorted_asc())
	{
		if(empty())
		{
			insert_front(val);
			return true;
		}
		else
		while(count<size_&&temp->value <= val)
		{
			if(temp->next!=NULL)
				temp=temp->next;
			count++;
		}
		if(count==0)
		{
			insert_front(val);
			return true;
		}
		if(count==size_)
		{
			insert_back(val);
			return true;
		}
		else
		{
			insert(val,count);
			return true;

		}
	}
	else
		return false;

}

bool DoublyLinkedList::insert_sorted_desc(DataType val) // same as insert_sorted_desc
{
	Node*temp = head_;
	Node*insertVal = new Node(val);
	Node*tempNext;
	int count=0;


	if(is_sorted_desc())
	{
		if(empty())
		{
			insert_front(val);
			return true;
		}
		else
		while(count<size_&&temp->value >= val)
		{
			if(temp->next!=NULL)
				temp=temp->next;
			count++;
		}
		if(count==0)
		{
			insert_front(val);
			return true;
		}
		if(count==size_)
		{
			insert_back(val);
			return true;
		}
		else
		{
			insert(val,count);
			return true;

		}
	}
	else
		return false;

}

void DoublyLinkedList::sort_asc() // This function will keep checking whether the value is less than the next value. If the value is greater than the next value, they will swap the values each other
{
	Node*temp = head_;
	Node*temp1 = temp->next;
	int space = 0;
	for(int i=0; i<size_-1; i++)
	{
		for(int j=i+1;j<size_;j++)
		{

			if(temp->value > temp1->value)
			{
				space = temp->value;
				temp->value = temp1->value;
				temp1->value = space;
			}
			if(temp1->next!=NULL)
				temp1 = temp1->next;

		}



			temp = temp->next;
			temp1 = temp->next;


	}
}

void DoublyLinkedList::sort_desc() // same as sort_asc
{
	Node*temp = head_;
	Node*temp1 = temp->next;
	int space = 0;
	for(int i=0; i<size_-1; i++)
	{
		for(int j=i+1;j<size_;j++)
		{

			if(temp->value < temp1->value)
			{
				space = temp->value;
				temp->value = temp1->value;
				temp1->value = space;
			}
			if(temp1->next!=NULL)
				temp1 = temp1->next;

		}



			temp = temp->next;
			temp1 = temp->next;


	}
}
