struct LinkedList* createEmptyList(void);
struct Node* createNode(int value);
void insertNode(struct LinkedList *list, int value);
void removeNode(struct LinkedList *list, int value);
void printList(struct LinkedList *list);
void destroyList(struct LinkedList *list);
