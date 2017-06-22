        typedef int ElementType;

/* START: fig4_35.txt */
        #ifndef _AvlTree_H
        #define _AvlTree_H

        typedef struct AvlNode
        {
            struct AvlNode *Left;
            struct AvlNode *Right;
            ElementType Element;
            int Height;
        } AvlNode;

//      struct AvlNode;
        typedef struct AvlNode *Position;
        typedef struct AvlNode *AvlTree;

        AvlTree MakeEmpty( AvlTree T );
        Position Find( ElementType X, AvlTree T );
        Position FindMin( AvlTree T );
        Position FindMax( AvlTree T );
        AvlTree Insert( ElementType X, AvlTree T );
        AvlTree Delete( ElementType X, AvlTree T );
        ElementType Retrieve( Position P );

char *Node2Str(void *T);

        #endif  /* _AvlTree_H */
/* END */
