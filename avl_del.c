#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;

/* START: fig4_35.txt */
#ifndef _AvlTree_H

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

AvlTree MakeEmpty( AvlTree T );
Position Find( ElementType X, AvlTree T );
Position FindMin( AvlTree T );
Position FindMax( AvlTree T );
AvlTree Insert( ElementType X, AvlTree T );
AvlTree Delete( ElementType X, AvlTree T );
ElementType Retrieve( Position P );

#endif  /* _AvlTree_H */
/* END */




FatalError(char *a)
{
    printf("%s\n", a);
}

struct AvlNode
{
    ElementType Element;
    AvlTree  Left;
    AvlTree  Right;
    int      Height;
};

AvlTree
MakeEmpty( AvlTree T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

Position
Find( ElementType X, AvlTree T )
{
    if( T == NULL )
        return NULL;
    if( X < T->Element )
        return Find( X, T->Left );
    else
        if( X > T->Element )
            return Find( X, T->Right );
        else
            return T;
}

Position
FindMin( AvlTree T )
{
    if( T == NULL )
        return NULL;
    else
        if( T->Left == NULL )
            return T;
        else
            return FindMin( T->Left );
}

Position
FindMax( AvlTree T )
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}

/* START: fig4_36.txt */
static int
Height( Position P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}
/* END */

static int
Max( int Lhs, int Rhs )
{
    return Lhs > Rhs ? Lhs : Rhs;
}

/* START: fig4_39.txt */
/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */

static Position
SingleRotateWithLeft( Position K2 )
{
    Position K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}
/* END */

/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */

static Position
SingleRotateWithRight( Position K1 )
{
    Position K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}

/* START: fig4_41.txt */
/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */

static Position
DoubleRotateWithLeft( Position K3 )
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}
/* END */

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */

static Position
DoubleRotateWithRight( Position K1 )
{
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft( K1->Right );

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );
}


/* START: fig4_37.txt */
AvlTree
Insert( ElementType X, AvlTree T )
{
    if( T == NULL )
    {
        /* Create and return a one-node tree */
        T = malloc( sizeof( struct AvlNode ) );
        if( T == NULL )
            FatalError( "Out of space!!!" );
        else
        {
            T->Element = X; T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else
        if( X < T->Element )
        {
            T->Left = Insert( X, T->Left );
            if( Height( T->Left ) - Height( T->Right ) == 2 )
                if( X < T->Left->Element )
                    T = SingleRotateWithLeft( T );
                else
                    T = DoubleRotateWithLeft( T );
        }
        else
            if( X > T->Element )
            {
                T->Right = Insert( X, T->Right );
                if( Height( T->Right ) - Height( T->Left ) == 2 )
                    if( X > T->Right->Element )
                        T = SingleRotateWithRight( T );
                    else
                        T = DoubleRotateWithRight( T );
            }
    /* Else X is in the tree already; we'll do nothing */

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}
/* END */

void PrintTree(AvlTree root) {
    if(root!=NULL)
    {
        PrintTree(root->Left);
        printf("%d ", root->Element);
        PrintTree(root->Right);
    }
}

AvlTree
Delete( ElementType X, AvlTree T )
{
    if(T==NULL){
        printf("no such value %d\n", X);
    }
    
    ElementType val = T->Element;
    if(X==T->Element)
    {
        AvlTree tmp = NULL;
        
        if(T->Right==NULL && T->Left==NULL)
        {            
            free(T);
            return NULL;
        }

        if(T->Right!=NULL)
            tmp = FindMin(T->Right);
        else if(T->Left!=NULL)
            tmp = FindMax(T->Left);

         val=tmp->Element;
         printf("change element val : %d and element %d\n", val, T->Element);
         X=val;
    }
    if(X<T->Element)
    {
        T->Element=val;
        printf("L Before crash X=%d and  T->Element=%d and T->Height=%d\n",
               X, T->Element, T->Height);
        T->Left = Delete(X, T->Left);        
        if(Height(T->Right)-Height(T->Left)==2)
            if(Height(T->Right->Right)>=Height(T->Right->Left))
                T=SingleRotateWithRight(T);
            else
                T=DoubleRotateWithRight(T);
    }    
    else if(X>T->Element)
    {
        T->Element=val;
        printf("R Before crash X=%d and  T->Element=%d and T->Height=%d\n",
               X, T->Element, T->Height);               
        T->Right = Delete(X, T->Right);
        if(Height(T->Left)-Height(T->Right)==2)
            if(Height(T->Left->Left)>=Height(T->Left->Right))
                T=SingleRotateWithLeft(T);
            else
                T=DoubleRotateWithLeft(T);
    }
    T->Height = (Height(T->Left)>Height(T->Right))?Height(T->Left):Height(T->Right);
    T->Height+=1;

    printf("T value %d & val %d\n", T->Element, val);
    
 
    return T;
}

ElementType
Retrieve( Position P )
{
    return P->Element;
}

int main()
{
    int i;
    AvlTree root = NULL;
    root = Insert(1, root);
    
    for(i=2;i<=100;i++){
        root =Insert(i, root);        
    }

    for(i=2;i<=100;++i)
    {
        //printf("i=%d and %d\n",i, Find(i,root)->Height);
        //printf("root =%d\n", root->Element);
        printf("Root %d &&&&& Delete %d:\n", root->Element, i);
        root = Delete(i, root);
        PrintTree(root);
        printf("\nHeigiht=%d\n", Height(root));
    }
    return 0;
}
