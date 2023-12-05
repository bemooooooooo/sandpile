#pragma once
#include <iostream>

struct MeshData {
	uint16_t x;
	uint16_t y;
	

	MeshData() {
		x = NULL;
		y = NULL;
	}
	MeshData(uint16_t x_new, uint16_t y_new){
		x = x_new;
		y = y_new;
	}
};

//QEQUE
struct node
{
	MeshData data;
	node* next;
	node(MeshData data) {
		this->next = nullptr;
		this->data = data;
	}
};

class myQeque
{
public:
	node* tail;
	node*top;
	int capacity;

	myQeque() {
		tail = nullptr;
		top = nullptr;
		capacity = 0;
	}

	~myQeque() {}

	bool isEmpty() {
		return tail == nullptr;
	}

	void pushMyQueue(MeshData value) {
		if (tail == nullptr) {
			tail = top = new node(value);
		} else {
			top = top->next = new node(value);
		}
		++capacity;
	}
	MeshData popMyQueue() {
		if (isEmpty()) {
			//error hendler
			exit(-1);
		}
		node* temp = tail;
		tail = tail->next;
		if (tail == nullptr)
		{
			top = nullptr;
		}
		--capacity;
		return temp->data;
	}
};
