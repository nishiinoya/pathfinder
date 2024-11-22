#include "libmx.h"

void mx_pop_back(t_list **list) {
    if (list == NULL || *list == NULL) {
        return;
    }

    t_list *temp = *list;
    t_list *prev = NULL;

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL) {
        free(temp);
        *list = NULL;
    } else {
        prev->next = NULL;
        free(temp);
    }
}
