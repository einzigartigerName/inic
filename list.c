#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define ERROR(msg) { fprintf(stderr, "ERROR: %s - %s\n", __func__, (msg)); exit(EXIT_FAILURE); } while(0)

/*
* @return list_t* - pointer to created list
*/
list_t *linit (){
    list_t *li = (list_t*) malloc(sizeof(list_t));
    if (li == NULL)
        ERROR("Can not malloc list.");

    li->first = NULL;
    li->last = NULL;
    li->size = 0;
    
    return li;
}


/*
* @param list_t* - list
* @param void* - data to insert
* @return struct list_elem* - inserted list-element
*/
struct list_elem *linsert (list_t *list, void *data){
    if(list == NULL)
        return NULL;

    // Create list_elem
    struct list_elem *in = (struct list_elem*) malloc(sizeof(struct list_elem));
    if(in == NULL)
        ERROR("Can not malloc list_elem.");
        
    in->data = data;
    in ->next = list->first;

    // list is empty ->'in' as last element
    if(list->first == NULL){
        list->last = in;
    }

    list->first = in; 
    list->size += 1;

    return in;
}


/*
* @param list_t* - list
* @param void* - data to append
* @return struct list_elem* - inserted list-element
*/
struct list_elem *lappend (list_t *list, void *data){
    if(list == NULL)
        return NULL;

     // Create list_elem
    struct list_elem *app = (struct list_elem*) malloc(sizeof(struct list_elem));
    if(app == NULL)
        ERROR("Can not malloc list_elem.");
        
    app->data = data;
    app->next = NULL;

    // list is empty ->'app' is first and last element 
    if(list->first == NULL){
        list->first = app;
    }   else{
        list->last->next = app;
    }

    list->last = app;
    list->size += 1;

    return app;
}

/*
* @param list_t* - destination
* @param list_t* - list to append to destination
*/
void lconcat(list_t *dest, list_t *list){
    if(dest == NULL){
        dest = list;
        return;
    }

    if(list == NULL)
        return;

    dest->last->next = list->first;
    dest->size += list->size;
}


/*
* @param list_t* - list to be copied
* @param cpy_data - method that handles data copy
* @return list_t* - copy of list
*/
list_t *lcpy(list_t *list, cpy_data cpy){
    if(list == NULL)
        return NULL;

    list_t *list_cpy = linit();
    struct list_elem *current = list->first;
    while(current != NULL){
        void *cpydata = cpy(current->data);
        lappend(list_cpy, cpydata);
        current = current->next;
    }

    return list_cpy;
}


/*
* @param list_t* -list
* @param size_t - index
* @return struct list_elem - found element
*/
struct list_elem *lget(list_t *list, size_t index){
    if(list == NULL)
        return NULL;

    if (index > list->size - 1)
        ERROR("Index out of Bounds!");

    if(index == 0)
        return list->first;

    if(index == list->size - 1)
        return list->last;

    struct list_elem *current = list->first;
    for(size_t i = 0; i < index; i++)
        current = current->next;

    return current;
}


/*
* @param list_t* - list
* @param size_t - index
* @param void* - data
*/
void lput(list_t *list, size_t index, void *data){
    if(list == NULL)
        return;

    if (index > list->size - 1)
        ERROR("Index out of Bounds!");

    if(index == 0){
        free(list->first->data);
        list->first->data = data;
    }

    if(index == list->size - 1){
        free(list->last->data);
        list->last->data = data;        
    }

    struct list_elem *current = list->first;
    for(size_t i = 0; i < index; i++)
        current = current->next;
    
    free(current->data);
    current->data = data;
}


/*
* @param list_t* - list
* @param void* - data to find
* @param cmp_elem - methode to compare the data
* @return struct list_elem* - found list-element (NULL if no matching element was found)
*/
struct list_elem *lfind (list_t *list, void *data, cmp_elem cmp){
    if(list == NULL)
        return NULL;

    struct list_elem *current = list->first;

    while(current != NULL){
        if(cmp(current->data, data) == 0)
            return current;

        current = current->next;
    }

    return NULL;
}


/*
* @param list_t* - list
* @param list_elem
* @return int: success -> 0; failure -> -1
*/
int lrm (list_t *list, struct list_elem *elem){
    if(list == NULL)
        return -1;

    // list is empty
    if (list->first == NULL)
        ERROR("List empty. Nothing to remove.");

    // element is NULL
    if (elem == NULL)
        ERROR("Element to be removed mustn't be NULL.");

    struct list_elem *current = list->first;

    // check first element
    if(list->first == elem){
        lrmf(list);
        return 0;
    }

    // check last element
    if(list->last == elem){
        lrml(list);
        return 0;
    }

    // Check in rest of list
    while(current->next != NULL){
        if(current->next == elem){
            current->next = elem->next;
            free(elem->data);
            free(elem);
            list->size -= 1;
            return 0;
        }
        current = current->next;
    }

    return -1;
}


/*
* @param list_t* - list
*/
void lrmf (list_t *list){
    if(list == NULL)
        return;

    // list is empty
    if (list->first == NULL)
        ERROR("List empty. Nothing to remove.");

    // just one element in list
    if (list->size == 1){
        // clear list
        struct list_elem *elem = list->first;
        list->first = NULL;
        list->last = NULL;
        list->size = 0;

        // free data and element
        free(elem->data);
        free(elem);

        return;
    }

    // rm first element
    struct list_elem *first = list->first;
    list->first = first->next;
    list->size -= 1;

    // free element and data
    free(first->data);
    free(first);
}


/*
* @param list_t* - list
*/
void lrml (list_t *list){
    if(list == NULL)
        return;

    // list is empty
    if (list->first == NULL)
        ERROR("List empty. Nothing to remove.");

    // just one element in list
    if (list->size == 1){
        // clear list
        struct list_elem *elem = list->first;
        list->first = NULL;
        list->last = NULL;
        list->size = 0;

        // free data and element
        free(elem->data);
        free(elem);

        return;
    }

    struct list_elem *last = list->last;
    struct list_elem *current = list->first;

    while(current->next != last)
        current = current->next;

    // rm last element
    current->next = NULL;

    // free element and data
    free(last->data);
    free(last);
}


/*
* @param list_t* - list
*/
void lrev(list_t *list){
    if(list == NULL)
        return;

    // zero or One Element
    if (list->first == NULL || list->first == list->last)
        return;

    struct list_elem *current = list->first;
    struct list_elem *prev = NULL;
    struct list_elem *next = NULL;

    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->first = prev;
}


/*
* @param list_t* - list
* @param print_elem - methode to print data in list
*/
void lprint (list_t *list, print_elem print){
    if(list == NULL)
        return;

    struct list_elem *current = list->first;
    while(current != NULL){
        print(current->data);
        current = current->next;
    }
}


/*
* @param list_t * - list
* @param void ** - array for pointers to be stored
*/
void ltoa(list_t *list, void *array[]){
    if(list == NULL){
        printf("ERROR: list is NULL\n");
        return;
    }

    if(array == NULL){
        printf("ERROR: array is NULL\n");
        return;
    }

    struct list_elem *current = list->first;
    for(size_t i = 0; i < list->size; i++){
        array[i] = current->data;
        current = current->next;
    }
}


/*
* @param list_t* - list
* @param int - free data or not
*/
void lfinit (list_t *list, int fdata){
    if(list == NULL)
        return;

    if(list->first == NULL){
        free(list);
        return;
    }

    struct list_elem *current = NULL;
    while (list->first != list->last) {
        current = list->first;
        list->first = current->next;

        if(fdata)
            free(current->data);

        free(current);
    }

    if(fdata)
        free(list->first->data);

    free(list->first);
    free(list);
}