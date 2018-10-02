// Sunghoon Ahn 20615061
#include "a1_sequential_list.hpp"

SequentialList::SequentialList(unsigned int cap)
{
	data = new data[cap];
	size = 0;
	capacity = cap;
}

SequentialList::~SequentialList()
{
	delete data[];
	size = NULL;
	capacity = NULL;
}

unsigned int SequentialList::size() const
{
	 return size;
}

unsigned int SequentialList::capacity() const
{
	return capacity;
}

bool SequentialList::empty() const
{
	if(size==0)
	return true;
	else
	return false;
}

bool SequentialList::full() const
{
	if(size==capacity)
	return true;
	else
	return false;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
	if(index<=size)
		return data[index];
	else
		return data[size-1];
}

unsigned int SequentialList::search(DataType val) const
{
	bool notFound = false;

	for(int i=0; i<size; i++)
	{
	if(data[i]==val){
		found = true;
		return i;
		}
	}
	if (notFound){
		return size;
	}
}

void SequentialList::print() const
{
	for(int i=0; i<size; i++)
	{
		cout<<data[i]<<endl;
	}
}

bool SequentialList::insert(DataType val, unsigned int index)
{
	if(index<=size)
	{
		for(int i=size; i>index; i--)
		{
			data[i]==data[i-1];
		}
		data[index]=val;
		size++;
		return true;
	}
	else
		return false;
}

bool SequentialList::insert_front(DataType val)
{
	if(size>0)
	{
		for(int i=size; i>0; i--)
		{
			data[i] = data[i-1];
		}
		data[0]=val;
		size++;
		return true;
	}
	else
	return false;
}

bool SequentialList::insert_back(DataType val)
{
	if(size>0)
	{
		data[size]=val;
		size++;
		return true;
	}
	else
		return false;
}

bool SequentialList::remove(unsigned int index)
{
	if(size>0)
	{
		for(int i=index; i<size; i++)
		{
			data[i]=data[i+1];
		}
		delete data[size];
		size--;
		return true;
	}
	else
		return false;
}

bool SequentialList::remove_front()
{
	if(size>0)
	{
		for(int i=0; i<size; i++)
		{
			data[i]=data[i+1];
		}
		delete data[size];
		size--;
		return true;
	}
	else
		return false;
}

bool SequentialList::remove_back()
{
	if(size>0)
	{
		delete data[size];
		size--;
		return true;
	}
	else
		return false;

}

bool SequentialList::replace(unsigned int index, DataType val)
{
	if(index<=size)
	{
		data[index]=val;
		return true;
	}
	else
		return false;
}

bool SequentialList::is_sorted_asc() const {
	bool sorted = true;
	for(int i= 1; i< size; i++)
	{
	if (data[i-1] >  data[i] || (data[i+1] < data[i])
		sorted= false;
	}
	return sorted;
}

bool SequentialList::is_sorted_desc() const {

	bool sorted = true ;
	for(int i= 1; i< size; i++)
	{
		if (data[i-1] <  data[i] || (data[i+1] > data[i])
			sorted= false;
	}
    return sorted;
}

bool SequentialList::insert_sorted_asc(DataType val) {
 	if(is_sorted_asc)
 	{
	 for (int i=1; i<size; i++)
	 	{
 			if (data[i-1] <= val && val <= data[i])
 			{
 			 	for(int j= size; j>i; j--)
 			 	{
 			 		data[j]=data[j-1];
 			 	}
 			 	data[i]=val;
 			 	return true;
 			 	break;
 			 }
 		}
 	}
 	else
 		return false;
 }

bool SequentialList::insert_sorted_desc(DataType val) {
 	if(is_sorted_desc)
 	{
	 for (int i=1; i<size; i++)
	 	{
 			if (data[i-1] >= val && val >= data[i])
 			{
 			 	for(int j= size ; j > i; j--)
 			 	{
 			 		data[j]=data[j-1];
 			 	}
 			 	data[i]= val;
 			 	return true;
 			 	break;
 			 }
 		}
 	}
 	else
 		return false;
 }
}

void SequentialList::sort_asc()
{
	for(int i=0; i<size; i++)
	{
		for(int j=i+1; j<size; j++)
		{
			if(data[j]<data[i])
			{
				int temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	}
}

void SequentialList::sort_desc()
{
	for(int i=0; i<size; i++)
	{
		for(int j=i+1; j<size; j++)
		{
			if(data[j]>data[i])
			{
				int temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	}
}

int main()
{

}
