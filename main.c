#include <stdio.h>
#include <stdlib.h>

/*
 * Prof. Roueche - I am describing the program flow as follows:
 * Problem #1 -
 *      1) Insert elements into a list
 *      2) Display the list
 *      3) Run function to remove every other element from the list
 *      4) Display the list again
 *      This is covered by removeEveryOtherItemList function
 *
 * Problem #2 -
 *      1) Insert elements into an array using arrayPush function
 *      2) Display the array
 *      3) Remove the last inserted elements using arrayPop function
 *      4) Display the array again
 *
 * Problem #3 -
 *      1) Insert elements into a list using stackPush function
 *      2) Display the list
 *      3) Remove the last inserted elements using stackPop function
 *      4) Display the list again
 *
 * Problem #4 -
 *      To implement a queue, we are going to use head and tail nodes.
 *      (I had to iterate through the list to get to the tail node!) - could we have added this to the struct ?
 *      The head node is used for dequeue operations while the tail node is used for enqueue operations
 *      The program flow is as follows -
 *      1) Insert new elements into a list using qEnqueue function (enqueue operation)
 *      2) Remove earlier elements from list using qDequeue function (dequeue operation)
 *
 */

// Define Linked list - listNode
typedef struct listNode{
    int value;
    struct listNode* next;
} Node;

// Define the head of the linked list
typedef struct list{
    struct listNode* head;
} List;

// Define Array Stack
typedef struct arrayStack{
    int arrayLength;
    int activeIndex;
    int* arrayItems;
} ArrayStack;

// Function to insert elements into the linked list
void addItemToHeadOfList(List** list, int data);

// Function to print items in the linked list
void printItemsList(List** list);

// Function reverse a linked list
void reverseList(List** list);

// Function to remove every other item from the linked list (Problem #1)
void removeEveryOtherItemList(List** list);

// Function to display an array (Problem #2)
void displayArray(int* array, int maxPosition);

// Function to add items to top of the array (Problem #2)
void arrayPush(ArrayStack** array, int data);

// Function to add items to top of the array (Problem #2)
void arrayPop(ArrayStack** array);

// Function to add items to top of the list element of the linked list (Problem #3)
void stackPush(List** list, int data);

// Function to remove items from top of the linked list (Problem #3)
void stackPop(List** list);

// Function to enqueue new items to bottom of Linked List (Problem #4)
void qEnqueue(List** list, int data);

// Function to dequeue items at the top of Linked List (Problem #4)
void qDequeue(List** list);

int main() {
    // Problem #1 - removing every other element from the list
    // let's set the first header value to be null
    List* inputList=NULL;
    // let's now insert some values
    addItemToHeadOfList(&inputList, 10);
    addItemToHeadOfList(&inputList, 20);
    addItemToHeadOfList(&inputList, 30);
    addItemToHeadOfList(&inputList, 40);
    addItemToHeadOfList(&inputList, 50);
    printf("\nPrinting linked list...");
    printItemsList(&inputList);

    removeEveryOtherItemList(&inputList);
    printf("\nAfter removing every other element in the list...");
    printItemsList(&inputList);

    // Problem#3 - Stack implementation using linked list
    printf("\n=====================Stack Implementation using Linked List============================================");
    List* stackExampleUsingList = NULL;
    printf("\nPushing 1st item to an empty stack...");
    stackPush(&stackExampleUsingList,1);
    printf("\nPrinting stack after 1st item...");
    printItemsList(&stackExampleUsingList);
    printf("\nPushing 2nd item into stack....");
    stackPush(&stackExampleUsingList,3);
    printf("\nPrinting stack after 2nd item...");
    printItemsList(&stackExampleUsingList);
    printf("\nPushing 3rd item into stack...");
    stackPush(&stackExampleUsingList,5);
    printf("\nPrinting stack after 3rd item...");
    printItemsList(&stackExampleUsingList);
    printf("\nPushing 4th item into stack...");
    stackPush(&stackExampleUsingList,7);
    printf("\nPrinting stack after 4th item...");
    printItemsList(&stackExampleUsingList);
    printf("\nPopping actions...");
    stackPop(&stackExampleUsingList);
    printf("\nPopped 4th item and this is how the stack looks...");
    printItemsList(&stackExampleUsingList);
    stackPop(&stackExampleUsingList);
    printf("\nPopped 3rd item and this is how the stack looks...");
    printItemsList(&stackExampleUsingList);
    stackPop(&stackExampleUsingList);
    printf("\nPopped 2nd item and this is how the stack looks...");
    printItemsList(&stackExampleUsingList);

    // Problem4 - Queue implementation using Linked list
    printf("\n=====================Queue Implementation using Linked List============================================");
    List* queueExampleUsingList = NULL;
    qEnqueue(&queueExampleUsingList, 2);
    printItemsList(&queueExampleUsingList);
    qEnqueue(&queueExampleUsingList, 4);
    printItemsList(&queueExampleUsingList);
    qEnqueue(&queueExampleUsingList, 6);
    printItemsList(&queueExampleUsingList);
    qEnqueue(&queueExampleUsingList, 8);
    printItemsList(&queueExampleUsingList);

    // remove 1st item
    qDequeue(&queueExampleUsingList);
    printItemsList(&queueExampleUsingList);
    // remove 2nd item
    qDequeue(&queueExampleUsingList);
    printItemsList(&queueExampleUsingList);
    // remove 3rd item
    qDequeue(&queueExampleUsingList);
    printItemsList(&queueExampleUsingList);

    // Problem 2 - Stack implementation using Array
    // We declare the data structure arrayStackExample using malloc and associate it with ArrayStack user defined struct
    ArrayStack* arrayStackExample = (ArrayStack*)malloc(sizeof(ArrayStack));
    arrayStackExample->activeIndex=-1; // this is so that we can start "pushing" from index 0
    arrayStackExample->arrayLength=10;
    arrayStackExample->arrayItems = (int*)malloc(sizeof(int) * 10);
    arrayPush(&arrayStackExample,10);
    displayArray(arrayStackExample->arrayItems, arrayStackExample->activeIndex);
    arrayPush(&arrayStackExample,20);
    displayArray(arrayStackExample->arrayItems, arrayStackExample->activeIndex);
    arrayPush(&arrayStackExample,30);
    displayArray(arrayStackExample->arrayItems, arrayStackExample->activeIndex);
    printf("\nPopping arrays...");
    arrayPop(&arrayStackExample);
    displayArray(arrayStackExample->arrayItems, arrayStackExample->activeIndex);
    arrayPop(&arrayStackExample);
    displayArray(arrayStackExample->arrayItems, arrayStackExample->activeIndex);
    arrayPop(&arrayStackExample);
    displayArray(arrayStackExample->arrayItems, arrayStackExample->activeIndex);

    return 0;
}


void addItemToHeadOfList(List** list, int data){
    /*
     * This function is used to insert items to head of a (Singly) Linked List
     * Params:
     *  1) List* list : This is the pointer of the list struct that we are would like to insert elements to
     *  2) int data: An integer datapoint
     * Return: None
     */
    // Declaring a node data structure within the heap;
    Node* node = malloc(sizeof(Node));
    // Assigning the supplied data to the value
    node->value = data;
    // Set the "next" pointer of the newly created node to existing head pointer value
    node->next = (Node *)(*list); // Original was : node->next = list->head; // saw conversion warnings in the IDE!
    // Now change the original list's header to point to the newly created node
    (*list) = (List *) node; //Original was: list->head = node; // saw conversion warnings in the IDE!

}

void printItemsList(List** list){
    /*
     * This function is used to print items of a Linked list
     * Params:
     *  1) List* list : This is the pointer of the list struct that we would like to print
     * Return:
     *  None
     */
    // First we declare a listNode in heap and follow this up by assigning its address to the original List's header
    Node* currentNode = (Node *) *list;
    puts("\n======================================================================================================");
    while (currentNode!= NULL){
        // this is to not have the arrow for the last element
        if (currentNode->next == NULL){
            printf("%d", currentNode->value);
        } else {
            // lets print out the value
            printf("%d->", currentNode->value);
        }
        // Change the position of node's address to pointer of next item on the linked list
        currentNode = currentNode->next;
    }
    puts("\n======================================================================================================");
}

void reverseList(List** list){
    if((*list)->head == NULL){
        return;
    }
    Node* prev = NULL;
    Node* ptr = (*list)->head;
    while(ptr!=NULL){
        Node* temp = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = temp;
    }
    (*list)->head = prev;
}


void removeEveryOtherItemList(List** list){
    Node* currentNode = (Node *) *list;
    Node* tempNode = NULL;
    while(currentNode->next!=NULL){
        //printf("\nStartingCurrentValue%d",currentNode->value); debug
        // let's use that tempNode to assign to odd element's address
        tempNode = currentNode->next;
        //printf("\nTempValue%d",tempNode->value); debug
        // assign the currentNode to tempNode(odd element's) next address - which is the even element
        currentNode->next = tempNode->next;
        // Move the currentNode pointer to next node in the chain - this is where the actual jump happens!
        currentNode = currentNode->next;
        //printf("\nCurrentValue%d",currentNode->value); debug
        //use free to remove the tempNode
        free(tempNode);
    }
}

void displayArray(int* set, int maxPosition){
    printf("\n");
    putchar('[');
    for(int i=0; i <= maxPosition; i++){
        if(i == maxPosition){
            printf("%d",set[i]);
        } else {
            printf("%d,",set[i]);
        }
    }
    putchar(']');
}

void arrayPush(ArrayStack** array, int data){
    // Declare data structure within the heap
    ArrayStack* tempObj = (ArrayStack*) *array;
    // Check if the array is full before proceeding to add new elements...
    if ((tempObj->arrayLength)-1 == (tempObj->activeIndex)){
        printf("\nArray is full!");
    } else{
        // Add element to index
        tempObj->arrayItems[(tempObj->activeIndex)+1] = data;
        // increment the activeIndex
        tempObj->activeIndex = (tempObj->activeIndex)+1;
    }
}

void arrayPop(ArrayStack** array){
    // Declare data structure within the heap!
    ArrayStack* tempObj = (ArrayStack*) *array;
    // Removing the item
    printf("\nRemoving %d",tempObj->arrayItems[(tempObj->activeIndex)]);
    tempObj->arrayItems[(tempObj->activeIndex)--]; // Pointer arithmetic on (tempObj->activeIndex)--
}

void stackPush(List** list, int data){
    // This is similar to addItemtoHeadofList
    // Declare a new node data structure within the heap
    Node* node = malloc(sizeof(Node));
    // Update the value to supplied data
    node->value = data;
    // declaring headElement based on List (which contains head)
    Node* headElement = (Node*) *list;
    // Let's check if the list is empty or not
    if(headElement==NULL){
        // if its empty then set to NULL as there will be only 1 item in the list
        node->next = NULL;
    } else {
        // if not empty, we will set the next pointer to point to new header
        node->next = (Node*)(*list);
    }
    // We have to update the header to point to the latest element in the Stack (LIFO!)
    *list = (List*) node;
}

void stackPop(List** list){
    // Declare a node element of struct list
    Node* node = (Node*) *list;
    // Check if the list's header is null
    if(node->next == NULL){
        printf("\nNothing to pop!");
    } else{
        // Print out the item that we will be removing - debug
        printf("\nPopping %d", node->value);
        // Change the header position of list to next item
        (*list) = (List *) node->next;
    }
    // let's free memory
    free(node);
}

void qEnqueue(List** list, int data){
    // Declare a new node data structure within the heap
    Node* newNode = malloc(sizeof(Node));
    // Update the value to supplied data
    newNode->value = data;
    printf("\nQueuing %d", data);
    newNode->next = NULL; // we will change this later depending on the head and tail

    // declaring headElement based on List (which contains head)
    Node* headElement = (Node*) *list;

    if(headElement==NULL) {
        headElement = newNode;
        Node *tailElement = newNode;
        printf("\nNULL path - HeadNode value is %d", headElement->value);
        printf("\nNULL path - TailNode value is %d", tailElement->value);
        // this is to update the original list pointer
        *list = (List*) headElement;
    } else {
        Node* tmpNode = (Node *) *list;
        while(tmpNode->next!=NULL){
            tmpNode = tmpNode->next;
        }
        Node* tailElement = tmpNode;
        printf("\nNORMAL path - Currently HeadNode value is %d", headElement->value);
        printf("\nNORMAL path - Currently TailNode value is %d", tailElement->value);

        //Change the pointer on the last element to point to the newly created node
        tailElement->next= newNode;
        //Update the tail element so that newNode will be the new tail element for the next call
        //Technically this is a misnomer as we are iterating using a while loop (231-235), this would have been useful
        //if we were using a pointer function variable which we could update for later!
        tailElement=newNode;
        printf("\nNORMAL path - After changing Tail pointer, TailNode value is %d", tailElement->value);
    }
}

void qDequeue(List** list){
    // Declare a head element
    Node* headElement = (Node*) *list;
    // Check if the list's header is null
    if(headElement->next == NULL){
        printf("\nNothing to dequeue!");
    } else {
        // print out item that we are trying to dequeue - debug
        printf("\nDe-queuing %d", headElement->value);
        // Change the header position of list to next item
        (*list) = (List *)headElement->next;
    }
}