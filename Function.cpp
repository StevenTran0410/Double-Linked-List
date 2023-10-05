#include "Header.h"

void DoubleLinkedList::push_back(int data)
{
	Node* temp = new Node(data);
	if (this->head == NULL)
	{
		this->head = temp;
		this->tail = temp;
	}
	else
	{
		this->tail->next = temp;
		temp->prev = this->tail;
		this->tail = temp;
	}
	this->Size++;
}

void DoubleLinkedList::push_front(int data)
{
	Node* temp = new Node(data);
	if (this->head == NULL)
	{
		this->head = temp;
		this->tail = temp;
	}
	else
	{
		temp->next = this->head;
		this->head->prev = temp;
		this->head = temp;
	}
	this->Size++;
}

void DoubleLinkedList::pop_back()
{
	if (this->head == NULL)
	{
		cout << "List is empty" << endl;
		return;
	}
	if (this->head == tail)
	{
		delete head;
		this->head = NULL;
		this->tail = NULL;
	}
	else
	{
		Node* temp = this->tail;
		this->tail = this->tail->prev;
		this->tail->next = NULL;
		delete temp;
	}
	this->Size--;
}

void DoubleLinkedList::pop_front()
{
	if (this->head == NULL)
	{
		cout << "List is empty" << endl;
		return;
	}
	if (this->head == tail)
	{
		delete head;
		this->head = NULL;
		this->tail = NULL;
	}
	else
	{
		Node* temp = this->head;
		this->head = this->head->next;
		this->head->prev = NULL;
		delete temp;
	}
	this->Size--;
}

void DoubleLinkedList::remove_pos(int pos)
{
	--pos;
	if (pos < 0 || pos >= this->Size)
	{
		cout << "Invalid position" << endl;
		return;
	}

	if (pos == 0) pop_front();
	else if (pos == this->Size - 1) pop_back();

	else
	{
		Node* temp = this->head;
		for (int i = 0; i < pos; i++)
		{
			temp = temp->next;
		}
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
	}
	this->Size--;
}

void DoubleLinkedList::deleteList()
{
	Node* temp = this->head;
	while (temp != NULL)
	{
		this->head = this->head->next;
		delete temp;
		temp = head;
	}
	this->Size = 0;
}

void DoubleLinkedList::print() const
{
	Node* temp = this->head;
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

void DoubleLinkedList::sort(int t, bool asc)
{
	string type;

	switch (t)
	{
	case 0:
		type = "Insertion ";
		this->insertionSort(this->head, asc);
		break;
	case 1:
		type = "Merge ";
		this->mergeSort(&this->head, asc);
		break;
	}

	// Construct the message based on sorting type and ascending/descending
	string sortDirection = asc ? "Ascending" : "Descending";
	string message = "Sort by: " + type + sortDirection + " sort";

	cout << message << endl;
} 

void DoubleLinkedList::insertionSort(Node* head, bool asc)
{
	Node* temp = head;
	while (temp != NULL)
	{
		Node* temp2 = temp->next;
		while (temp2 != NULL)
		{
			if (asc)
			{
				if (temp->data > temp2->data)
				{
					int t = temp->data;
					temp->data = temp2->data;
					temp2->data = t;
				}
			}
			else
			{
				if (temp->data < temp2->data)
				{
					int t = temp->data;
					temp->data = temp2->data;
					temp2->data = t;
				}
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}	

void DoubleLinkedList::split(Node* head, Node** front, Node** back)
{
	Node* fast = head->next;
	Node* slow = head;

	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	*front = head;
	*back = slow->next;
	slow->next = NULL;
}

Node* DoubleLinkedList::merge(Node* first, Node* second, bool asc)
{
	if (first == NULL) return second;
	if (second == NULL) return first;

	if (asc)
	{
		if (first->data < second->data)
		{
			first->next = merge(first->next, second, asc);
			first->next->prev = first;
			first->prev = NULL;
			return first;
		}
		else
		{
			second->next = merge(first, second->next, asc);
			second->next->prev = second;
			second->prev = NULL;
			return second;
		}
	}
	else
	{
		if (first->data < second->data)  // Here's the change, from '>' to '<'
		{
			second->next = merge(first, second->next, asc);
			second->next->prev = second;
			second->prev = NULL;
			return second;
		}
		else
		{
			first->next = merge(first->next, second, asc);
			first->next->prev = first;
			first->prev = NULL;
			return first;
		}
	}
}

void DoubleLinkedList::mergeSort(Node** head, bool asc)
{
	if (*head == NULL || (*head)->next == NULL) return;

	Node* first;
	Node* second;

	split(*head, &first, &second);

	mergeSort(&first, asc);
	mergeSort(&second, asc);

	*head = merge(first, second, asc);
}

void DoubleLinkedList::remove_data(int data)
{
	Node* temp = this->head;
	while (temp != NULL)
	{
		Node* nextNode = temp->next;
		if (temp->data == data)
		{
			if(temp->prev)
				temp->prev->next = temp->next;
			else
				this->head = temp->next;
			if(temp->next)
				temp->next->prev = temp->prev;
			else
				this->tail = temp->prev;

			delete temp;
			this->Size--;
		}
		temp = nextNode;
	}
}

void DoubleLinkedList::insert_pos(int pos, int data)
{
	--pos;
	if (pos < 0 || pos >= this->Size)
	{
		cout << "Invalid position" << endl;
		return;
	}

	if (pos == 0) push_front(data);
	else if (pos == this->Size - 1) push_back(data);

	else
	{
		Node* temp = this->head;
		for (int i = 0; i < pos; i++)
		{
			temp = temp->next;
		}
		Node* temp2 = new Node(data);
		temp2->next = temp;
		temp2->prev = temp->prev;
		temp->prev->next = temp2;
		temp->prev = temp2;
		this->Size++;
	}
}

void DoubleLinkedList::reverse()
{
	Node* temp = NULL;
	Node* current = this->head;
	while (current != NULL)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	if (temp != NULL)
		this->head = temp->prev;
}

bool DoubleLinkedList::empty()
{
	return this->head == NULL;
}

void DoubleLinkedList::swap(int pos1, int pos2)
{
	--pos1;
	--pos2;
	if (pos1 < 0 || pos1 >= this->Size || pos2 < 0 || pos2 >= this->Size)
	{
		cout << "Invalid position" << endl;
		return;
	}
	if (pos1 == pos2) return;
	if (pos1 > pos2) std::swap(pos2, pos1);

	Node* temp1 = this->head;
	for (int i = 0; i < pos1; i++)
	{
		temp1 = temp1->next;
	}

	Node* temp2 = this->head;
	for (int i = 0; i < pos2; i++)
	{
		temp2 = temp2->next;
	}

	int t = temp1->data;
	temp1->data = temp2->data;
	temp2->data = t;
}

ostream& operator<<(ostream& os, const DoubleLinkedList& list)
{
	Node* current = list.head;
	os << "[ ";
	while (current) {
		os << list.getData(current) << " ";
		current = list.nextNode(current);
	}
	os << "]";
	return os;
}

ostream& operator<<(ostream& os, const Node& data)
{
	os << data.data;
	return os;
}

Node* DoubleLinkedList::search(int data) const
{
	Node* temp = head;
	while (temp)
	{
		if(temp->data == data)
			return temp;
		temp = temp->next;
	}
}