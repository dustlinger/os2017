#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#define BUFFER_SIZE 10

typedef struct{
     char type; // 0=fried chicken, 1=French fries
     int amount; // pieces or weight
     char unit; // 0=piece, 1=gram
} item;
item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
    while ((first + 1) % BUFFER_SIZE == last) { 
      // do nothing -- no free buffer item
    }
    memcpy(&buffer[first], i,sizeof(item));
    first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
    item *i = malloc(sizeof(item));
    while (first == last) { 
      // do nothing -- nothing to consume
    }
    memcpy(i, &buffer[last],sizeof(item));
    last = (last + 1) % BUFFER_SIZE;
    return i;
}
void *threadProduceFunction(void *params) {
    printf("- Produce thread.\n");
    printf("- Initial value : First: %d, last: %d\n", first, last );
    item i1;
    i1.type = '2';  
    i1.amount = 4;
    i1.unit = '1';
    item i2;
    i2.type = '2';
    i2.amount = 1;
    i2.unit = '1';
    item i3;
    i3.type = '9';
    i3.amount = 6;
    i3.unit = '9';
    printf("- Produce item 1:\n Type: %c\n Amount: %d\n Unit: %c\n", i1.type,i1.amount,i1.unit );
    produce(&i1);
    printf(" First: %d, last: %d\n", first, last);
    printf("\n- Produce item 2:\n Type: %c\n Amount: %d\n Unit: %c\n", i2.type,i2.amount,i2.unit );
    produce(&i2);
    printf(" First: %d, last: %d\n", first, last);
    printf("\n- Produce item 3:\n Type: %c\n Amount: %d\n Unit: %c\n", i3.type,i3.amount,i3.unit );
    produce(&i3);
    printf(" First: %d, last: %d\n", first, last);
    return 0;
}

void *threadConsumeFunction(void *params) {
    printf("\n - Consume thread\n");
    consume();
    printf("- Consume an item: First: %d, last: %d\n", first, last );
    consume();
    printf("- Consume another item: First: %d, last: %d\n", first, last );
}
int main() {
    pthread_t tid_prod, tid_cons;
    pthread_create(
       &tid_prod,                          // get thread id
       NULL,                               // skip the attributes
       threadProduceFunction,              // thread function name 
       NULL);                              // argument to thread function
    pthread_join(tid_prod, NULL);
    pthread_create(
       &tid_cons,
       NULL,
       threadConsumeFunction,
       NULL);
    pthread_join(tid_cons, NULL);
    return 0;
}
    
