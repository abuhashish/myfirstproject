#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Original code provided by the author Mark Allen Wiess.
//Modified by Dr. Radi Jarrar
int i=0;
typedef struct AVLnode *AVLNode;

struct AVLnode
{
    char word[50];
    char meaning[50][50];
    char synonym[50];
    char antonym[50];
    AVLNode Left;
    AVLNode Right;
    int Height; //Balance information
};
typedef struct node {

    char delete[20];
    struct node* next;
}arr;
typedef struct hash *hashptr;

struct hash {
    char word[50];
    char meaning[50][50];
    char synonym[50];
    char antonym[50];
    char name[30];
};
struct hash Hash_Table[];

AVLNode MakeEmpty(AVLNode T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

AVLNode Find( char X[], AVLNode t )
{
    int choice,meannum;
    if( t == NULL ) {
        return NULL;
    }
    if( strcmp(X , t->word)>0 ) {
        printf("%s",t->Left->word);
        return Find(X, t->Left);
    }
    else if( strcmp(X , t->word)<0 ) {
        return Find(X, t->Right);

    }
    else{
        printf("The word has been found !!!.\n");
        printf("do you want to update the information in this word?\n");
        printf("1.yes\2.no\n");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("please choose what u want to update... \n1.meaning\n2.synonym\n3.antonym\n");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("enter how many words you wanna enter for meaning\no");
                scanf("%d", &meannum);
                while (meannum != 0) {
                    scanf("%s", t->meaning[meannum]);
                }
            } else if (choice == 2) {
                printf("enter the new synonym\n");
                scanf("%s", t->synonym);
            } else if (choice == 3) {
                printf("enter the new antynom\n");
                scanf("%s", t->antonym);
            } else {
                printf("Wrong input\n");
            }
        }

        }
}

AVLNode FindMin( AVLNode T )
{
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}

AVLNode FindMax( AVLNode T )
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}

int Height( AVLNode P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}

int Max( int Lhs, int Rhs )
{
    return Lhs > Rhs ? Lhs : Rhs;
}
AVLNode SingleRotateWithLeft( AVLNode K2 )
{
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}
AVLNode SingleRotateWithRight( AVLNode K1 )
{
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}
AVLNode DoubleRotateWithLeft( AVLNode K3 )
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}

AVLNode DoubleRotateWithRight( AVLNode K1 )
{
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft( K1->Right );

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );
}
AVLNode rightRotate(AVLNode y)
{
    AVLNode x = y->Left;
    AVLNode T2 = x->Right;

    // Perform rotation
    x->Right = y;
    y->Left = T2;

    // Update heights
    y->Height = Max(Height(y->Left),
                    Height(y->Right)) + 1;
    x->Height = Max(Height(x->Left),
                    Height(x->Right)) + 1;

    // Return new root
    return x;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
AVLNode leftRotate(AVLNode x)
{
   AVLNode y = x->Right;
    AVLNode T2 = y->Left;

    // Perform rotation
    y->Left = x;
    x->Right = T2;

    // Update heights
    x->Height = Max(Height(x->Left),
                    Height(x->Right)) + 1;
    y->Height = Max(Height(y->Left),
                    Height(y->Right)) + 1;

    // Return new root
    return y;
}


AVLNode Insert( char word[],char meaning[50][50],char antonym[],char synonym[], AVLNode T )
{
    if( T == NULL )
    {
        /* Create and return a one-node tree */
        T = malloc( sizeof( struct AVLnode ) );
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            strcpy(T->word,word ) ;
            strcpy((char *) T->meaning, (const char *) meaning) ;
            strcpy(T->antonym,antonym) ;
            strcpy(T->synonym,synonym) ;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if( strcmp(word , T->word) >0)
    {
        T->Left = Insert( word,meaning,antonym,synonym, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if( strcmp(word, T->Left->word)<0 )
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
    }
    else if( strcmp(word , T->word) <0)
    {
        T->Right = Insert( word,meaning,antonym,synonym, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
            if( strcmp(word , T->Right->word)>0 )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }
    /* Else X is in the tree already; we'll do nothing */

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}
int getBalance(AVLNode N)
{
    if (N == NULL)
        return 0;
    return Height(N->Left) -
           Height(N->Right);
}

int calculatemeanings(char item[]){
    int c=0;
    for(int i=0;i<strlen(item);i++){
        if(item[i]==',')
            c++;
    }
    if (c<1){
        printf("there is error in input");
        return(0);
    }

  return(c);
}
long int find_prime(long int c)
{
    long int s=2*c+1;
    int flag,i;
    for (i=2;i<=sqrt(s);++i)
    {
        if ((s%i)==0)
            s=find_prime(++c);
    }
    return s;
}
AVLNode readfromfile(AVLNode t) {
    //Declaring the variables that will be stored
    AVLNode T;
    T=MakeEmpty(NULL);
    char item[100];
    char word[50], meaning[50][50], synonym[50],antonym[50];
    // printf("please enter file name");
    //scanf("%s",path);
    FILE *read = fopen("amro.txt", "r");
    if(read == NULL)
    {
        printf("File doesn't exist in the directory!!\n\n");
        return 0;
    }

    //Keep reading from the file as long as the file doesn't end
    while(fgets(item, 200, read) != NULL)
    {
        int c=calculatemeanings(item);
        c=c+3;
        int i=0,g=0;
        //This will separate each line into 5 pieces
        char* piece = strtok(item, ":,/*");
        for(i; i <= c&& piece != NULL; i++)
        {
            if (i == 0)
                strcpy(word, piece);

            if(i<c-1&&i>0) {
                strcpy(meaning[g],piece);
                g++;
            }
            else if(i==c-1)
                strcpy(synonym, piece);
            else if(i==c)
                strcpy(antonym,piece);


            piece = strtok(NULL, ":/,*");
        }

       t=Insert(word,meaning,synonym,antonym,t);

    }

    fclose(read);
    
    printf("********* SUCCSESSFUL*********\n");
    return t;
}
void save(AVLNode t) {

}
AVLNode deleteFromTree(AVLNode T,char x[]){
    if (T == NULL)                              // if the tree has no nodes to delete, return NULL
        return NULL;

    if (strcmp(x, T -> word) > 0)                    // if the value we want to delete is less than the node we are standing at, go left
        T -> Left = deleteFromTree(T -> Left, x);

    else if (strcmp(x, T -> word) < 0)               // if the value we want to delete is less than the node we are standing at, go right
        T -> Right = deleteFromTree(T -> Right, x);

    else if (T -> Left && T -> Right){                  // if we reached the node that we want and it has two children
        AVLNode min = FindMin(T -> Right);                  // find the minimum in the right subtree
        strcpy(T -> word, min -> word);                 // move the data in min to the node we want to delete
        T -> Right = deleteFromTree(T -> Right, min ->word);   // delete min from the tree
    }
    else{                   // if we reached the node that we want and it has one or zero children
        AVLNode child;

        if (T -> Left == NULL)      // if the left is NULL, then the child is the right one (even if it is also NULL)
            child = T -> Right;

        else if (T -> Right == NULL)    // if the right is NULL, then the child is the left one (even if it is also NULL)
            child = T -> Left;


        return child;
    }


}

AVLNode balancetree(AVLNode t){
    if (!t) return t;
    int balance = getBalance(t);
    if (balance > 1 && getBalance(t->Left) >= 0)   /* rotateReight */
        return SingleRotateWithRight(t);
    if (balance < -1 && getBalance(t->Right) <= 0) /* rotateLeft */
        return SingleRotateWithLeft(t);
    if (balance > 1 && getBalance(t->Left) < 0)    /* rotateLeftReight */
    {
        t->Left = SingleRotateWithLeft(t->Left);
        return SingleRotateWithRight(t);
    }
    if (balance < -1 && getBalance(t->Right) > 0)  /* rotateReightLeft */
    {
        t->Right = SingleRotateWithRight(t->Right);
        return SingleRotateWithLeft(t);
    }
    return t;
}
void DeleteList(struct node* L){
    struct node* P;
    struct node* temp;
    P = L->next;
    L->next = NULL;
    while(P != NULL){
        temp = P->next;
        free(P);
        P=temp;
    }
}
struct node* nodeMakeEmpty(struct node* L){
    if(L != NULL)
        DeleteList( L );
    L = (struct node*)malloc(sizeof(struct node));
    if(L == NULL)
        printf("Out of memory!\n");
    L->next = NULL;
    return L;
}
void add(char name[],arr* L,arr* P){
    arr* temp;
    temp = (arr*)malloc(sizeof(arr));
    strcpy(temp->delete,name);
    temp->next = P->next;
    P->next = temp;
}
void deletealla(AVLNode t,char x,struct node *l1) {
    if( t != NULL)
    {
        deletealla(t->Right,x,l1);
        if(t->word[0]==x) {
            add(t->word,l1,l1);
            //printf("%s\n", t->word);
        }
        deletealla(t->Left,x,l1 );
    }
}

AVLNode deletewords(AVLNode t) {
    int choice;
    char word[50];
    char letter;
    struct node *l1;
    l1=nodeMakeEmpty(NULL);
    printf("**************************************\n");
printf("1.delete 1 word you choose\n");
printf("2.delete all words that starts with a specefic charecter.\n");
scanf("%d",&choice);
    switch (choice  ) {
        case 1:printf("please enter the word you want to delete?\n");
               scanf("%s",word);
               t=deleteFromTree(t,word);
               t=balancetree(t);
            break;

        case 2:printf("please enter a charecter\n");
        scanf(" %c",&letter);
        deletealla(t,letter,l1);
        l1=l1->next;
        while(l1!=NULL){
            t=deleteFromTree(t,l1->delete);
            t=balancetree(t);
            l1=l1->next;
        }
            break;

    }
    return t;
}



void listall(AVLNode t,char word[]) {
    if( t != NULL)
    {
        listall( t->Right,word);
        if(strcmp(t->word,word)==0)
        printf("the synonym   is %s and the antonym is  %s\n", t->synonym,t->antonym);
        listall( t->Left ,word);
    }

}

void listalla(AVLNode t,char x) {
    if( t != NULL)
    {
        listalla(t->Right,x);
        if(t->word[0]==x) {
            printf("%s\n", t->word);
        }
        listalla(t->Left,x );
    }

}

void listlexi( AVLNode t)
{
    if( t != NULL)
    {
        listlexi( t->Right );
        printf("%s\n", t->word);
        listlexi( t->Left );
    }

}
void listwords(AVLNode t) {
    int choice;
    char ch;
    char word[50];
    printf("**************************************\n");
    printf("1.list words in lexicographic order\n");
    printf("2.list all synonym and antonyms of a given word\n");
    printf("3.list all words that starts with the same letter\n");
    scanf("%d",&choice);
    switch (choice) {
        case 1:listlexi(t);

            break;
        case 2:printf("please enter the word you want \n");
            scanf("%s",&word);
            listall(t,word);
            break;
        case 3: printf("enter the charecter you want\n");
            scanf(" %c",&ch);
            listalla(t,ch);
            break;

    }
}

AVLNode insertnew(AVLNode t) {
    char word[50], meaning[50][50], synonym[50],antonym[50];
    int num;
    printf("please enter the word\n");
    scanf("%s",&word);
    printf("please enter how many meanings you wanna insert for this word\n");
    scanf("%d",&num);
    while(num!=0){
       scanf("%s",meaning[num]);
       num--;
    }
    printf("please enter a synonym for this word\n");
    scanf("%s",synonym);
    printf("please enter antonym\n");
    scanf("%s",antonym);
   t= Insert(word,meaning,synonym,antonym,t);
   return t;
}



void savetable() {

}

void deletetable() {

}

void searchtable() {

}

void inserttable() {

}

void printtablesize() {

}

void printhasttable() {

}
void hash() {
    int choice;
    printf("**************************************");
    printf("1.Print Hast Table\n");
    printf("2.Print out table size\n");
    printf("3.Insert a new record into hast table\n");
    printf("4.Search for a specific word\n");
    printf("5.Delete a specific record\n");
    printf("6.Save hast table back to file\n");
    scanf("%d",&choice);
    switch (choice) {
        case 1:printhasttable();
            break;
        case 2:printtablesize();
            break;
        case 3:inserttable();
            break;
        case 4:searchtable();
            break;
        case 5:deletetable();
            break;
        case 6:savetable();
            break;

    }
}
int main()
{
    char x[50];
    AVLNode t;
    t = MakeEmpty(NULL);
    int choice;
    do {
        printf("***************************\nDictionary \n******************************\n");
        printf("1.Read Data from file\n");
        printf("2.Insert new word\n");
        printf("3.Find a word\n");
        printf("4.List function\n");
        printf("5.Delete function\n");
        printf("6.Save\n");
        printf("7.Hash-Table\n");
        printf("8.Exit\n");

        scanf("%d",&choice);
        switch (choice) {
            case 1:t=readfromfile(t);
                break;
            case 2:t=insertnew(t);
                break;
            case 3:
                printf("please enter the word you are looking for.\n");
                scanf("%s",x);
                Find(x,t);
                break;
            case 4:listwords(t);
                break;
            case 5:t=deletewords(t);
                break;
            case 6:save(t);
                break;
            case 7:hash();
                break;
            default:
                printf("please enter a number between 1 and 8");
        }
    }while(choice!=8);

    return 0;
}
