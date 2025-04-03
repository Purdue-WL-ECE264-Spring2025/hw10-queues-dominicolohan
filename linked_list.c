#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
    struct list_node *new = malloc(sizeof(struct list_node));
    if(new == NULL){ return NULL;}
    new->value = value;
    new->next = NULL;
    return new; }

void insert_at_head(struct linked_list *list, size_t value) {
    struct list_node *new = new_node(value);
    new->next = list->head;
    list->head = new;
}

void insert_at_tail(struct linked_list *list, size_t value) {
    struct list_node *new = new_node(value);
    if(list->head == NULL){list->head = new; return;}
    struct list_node *old = list->head;
    while(old->next != NULL){ old = old->next;}
    old->next = new; // puts new at the end
}

// should return value contained in the removed node
size_t remove_from_head(struct linked_list *list) {
    if(list->head == NULL) {return 0;}
    struct list_node *old = list->head;
    list->head = old->next;
    size_t val = old->value;
    free(old); 
    return val; }

size_t remove_from_tail(struct linked_list *list) {
    if(list->head == NULL) {return 0;}
    struct list_node *old = list->head;
    size_t val;
    if(old->next == NULL){ //in case there's only one element
        val = old->value;
        free(old);
        list->head = NULL; 
        return val;
    }
    struct list_node *p = NULL;
    while((old->next) != NULL){
       p = old;
       old = old->next;
    }
    p->next = NULL;
    val = old->value;
    free(old);
    return val; }

void free_list(struct linked_list list) {
    struct list_node *destroy = list.head;
    while(destroy!=NULL){
        struct list_node *save = destroy->next;
        free(destroy);
        destroy = save;
    }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
