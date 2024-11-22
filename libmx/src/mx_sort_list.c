#include "libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *a, void *b)) {
    if (lst == NULL || cmp == NULL) {
        return lst;
    }

    bool swapped = true;
    t_list *temp;
    void *data;

    while (swapped) {
        swapped = false;
        temp = lst;

        while (temp->next != NULL) {
            if (cmp(temp->data, temp->next->data)) {
                data = temp->data;
                temp->data = temp->next->data;
                temp->next->data = data;
                swapped = true;
            }
            temp = temp->next;
        }
    }

    return lst;
}
