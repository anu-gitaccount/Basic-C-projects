
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct book_lib {
	char title[64];
	int pages;
	struct book_lib *next;
};

typedef struct book_lib  Book;

//global var that is pointing to first element in list
Book *first = NULL;
//total num of books
int total_books = 0;


void add_book(char *title , int pages) {
	
	//struct book_lib *p
	Book *p , *new_node ;

	//base condition
	//check if its the first book
	if (!first) {
		p = malloc(sizeof(Book));

		if (!p) {
			printf("Memory Allocation failed\n");
			return;
		}


		//asigining it to zero
	  memset(p , 0, sizeof(Book));
	  	
		strncpy(p->title ,title , 63);
		p->pages = pages;
		p->next = NULL;
		//not the first node pointing to the second node
		first = p;

		total_books++;
		return;
	}

	for (p = first; p->next != NULL; p = p->next) {

		new_node = malloc(sizeof(Book));

	}

		memset(new_node , 0 , sizeof(Book));

		strncpy(new_node->title , title , 63);
		new_node->pages = pages;
		new_node->next = NULL;

		p->next = new_node;

		total_books++;
			
		
}

void print_books() {
	Book *p = first;

	while (p) {
		printf("Title : %s , pages: %d\n", p->title, p->pages);
		p = p->next;

	}
}


int main() {
	
	first = 0;
	total_books = 0;

	add_book("habits" , 204);

	//printf("%s\n", first->title);
	//printf("%d\n", first->pages);


	add_book("Data" , 190);
	add_book("Rich Dad and Poor Dad" , 2300); 

	//printf("%s\n" , first->next->title);
	//printf("%d\n" , first->next->pages);

	printf("%d\n",total_books);

	
	print_books();

	return 0;
}
