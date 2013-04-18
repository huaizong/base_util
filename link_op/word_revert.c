#include <string.h>
#include <stdlib.h>

char *revert_string_word(char *word)
{
    if(word == NULL) {
        return workd;
    }
    size_t len = strlen(word);
    char *head = word;
    char *tail = word + len;
    int len_head = 0; 
    int len_tail = 0; 
    while(head < tail) {
        while(*head && isalpha(*head)){
            len_head++;
            head++;
        }
        while(tail > head && isalpha(*tail)){
            tail--;
            len_tail++;
        }
        if(head < tail) {
            
