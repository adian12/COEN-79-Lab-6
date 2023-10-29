// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <iostream>
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	//MY IMPLEMENTATIONS 
    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr)
	{
		// Library facilities used: cassert, cstdlib
		
		//Precondition
		bool inSameList = false;
		node *curr = start_ptr;
		while (curr != NULL)
		{
			if (curr == end_ptr)
			{
				inSameList = true;
				break;
			}
			curr = curr->link();
		}
		assert(inSameList);

		head_ptr = start_ptr;

		if (end_ptr)
		{
			tail_ptr = end_ptr;
			end_ptr = end_ptr->link();
			tail_ptr->set_link(nullptr);
		}else
		{
			tail_ptr = NULL;
		}
	}

    size_t list_occurrences(node* head_ptr, const node::value_type& target)
	{
		// Library facilities used: cstdlib
		int count = 0;

		node *curr = head_ptr;
		while (curr != NULL)
		{
			if (curr->data() == target)
			{
				count++;
			}

			curr = curr->link();
		}
		return count;
	}

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position)
	{
		// Library facilities used: cassert, cstdlib

		//Precondition
		assert(head_ptr != NULL);
		assert(position > 0 && position <= list_length(head_ptr) + 1);

		node *curr;
		//Case for inserting at head
		if (position == 1)
		{
			node *new_node = new node(entry, head_ptr);
			head_ptr = new_node;
		}else
		{
			curr = head_ptr;
			int curr_position = 1;
			while (curr_position < position - 1 && curr->link() != NULL)
			{
				curr = curr->link();
				curr_position++;
			}
		}

		//Making the new node and inserting it at the correct posiiton
		node *new_node = new node(entry, curr->link());
		curr->set_link(new_node);
	}

    node::value_type list_remove_at(node*& head_ptr, size_t position)
	{
		// Library facilities used: cassert, cstdlib

		//Precondition
		assert(head_ptr != NULL);
		assert(position > 0 && position <= list_length(head_ptr) + 1);

		node::value_type erased;
		node *curr;
		node *temp;

		//Case for removing the head_ptr
		if (position == 1)
		{
			assert(head_ptr != NULL);
			temp = head_ptr;
			erased = temp->data();
			head_ptr = head_ptr->link();
			delete temp;
		}else
		{
			curr = head_ptr;
			int curr_position = 1;

			while (curr_position < position - 1 && curr->link() != NULL)
			{
				curr = curr->link();
				curr_position++;
			}

			assert(curr->link() != NULL && "Out of range");

			temp = curr-> link();
			erased = temp->data();
			curr->set_link(temp->link());
			delete temp;
		}
		return erased;
	}

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
	{
		// Library facilities used: cassert, cstdlib

		//Precondition
		assert(head_ptr != NULL);
		assert(start >= 1);
		assert(finish >= start);

		//Making new list
		node *new_head = NULL;
		node *new_tail = NULL;
		int curr_position = 1;

		
		//Finding the start position
		node *curr = head_ptr;
		while (curr_position < start && curr != NULL)
		{
			curr = curr->link();
			curr_position++;
		}

		//Copying the nodes from start to finish
		while (curr_position <= finish && curr != NULL)
		{
			node *new_node = new node(curr->data());

			if (new_tail == NULL)
			{
				new_head = new_node;
				new_tail = new_node;
			}else
			{
				new_tail->set_link(new_node);
				new_tail = new_node;
			}

			curr = curr->link();
			curr_position++;
		}

		return new_head;
	}

    void list_print (const node* head_ptr)
	{
		// Library facilities used: cassert, cstdlib, iostream

		//Precondition
		assert(head_ptr != NULL);

		const node *curr = head_ptr;
		
		while (curr != NULL)
		{
			std::cout << curr->data();
			curr = curr->link();

			if (curr != NULL && curr->data() != head_ptr->data())
			{
				std::cout << " ";
			}
		}
		
		//Spacer
		std::cout << endl;
	}

    void list_remove_dups(node* head_ptr)
	{
		// Library facilities used: cassert, cstdlib, iostream
		
		//Precondition
		assert(head_ptr != NULL);
		

		node *curr = head_ptr;


		while (curr != NULL)
		{
			node *temp = curr;

			while (temp->link() != NULL)
			{
				if (temp->link()->data() == current->data())
				{
					node *dupe = temp->link();
					temp->set_link(dupe->link());
					delete dupe;
				}else
				{
					temp = temp->link();
				}
			}

			//Updating to next node
			curr = curr->link();
		}

		//Printing out 
		curr = head_ptr;

		while (curr != NULL)
		{
			std::cout << curr->data() << " ";
			curr = curr->link();
		}
		
		//Spacer
		std::cout << endl;
	}

    node* list_detect_loop (node* head_ptr)
	{
		// Library facilities used: cassert, cstdlib,
		//Similar to HW problem

		//Precondition
		assert(head_ptr != NULL);

		//Necessary pointers
		node *slow = head_ptr;
		node *fast = head_ptr;

		while (fast != NULL && fast->link() != NULL)
		{
			slow = slow->link();
			fast = fast->link();

			if (slow == fast)
			{
				node *loopStart = head_ptr;

				while (loopStart != slow) 
				{
					loopStart = loopStart->link();
					slow = slow->link();
				}

				return loopStart;
			}
		}
		//If there isn't a loop, just returns NULL
		return NULL;
	}
    
}