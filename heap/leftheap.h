        #ifndef _LeftHeap_H
        #define _LeftHeap_H

        typedef int ElementType;

/* START: fig6_25.txt */

        struct TreeNode
        {
            ElementType   Element;
            struct TreeNode *Left;
            struct TreeNode *Right;
            int           Npl;
        };
        typedef struct TreeNode *PriorityQueue;

        /* Minimal set of priority queue operations */
        /* Note that nodes will be shared among several */
        /* leftist heaps after a merge; the user must */
        /* make sure to not use the old leftist heaps */

        PriorityQueue Initialize( void );
        ElementType FindMin( PriorityQueue H );
        int IsEmpty( PriorityQueue H );
        PriorityQueue Merge( PriorityQueue H1, PriorityQueue H2 );

        PriorityQueue Insert1( ElementType X, PriorityQueue H );
        PriorityQueue DeleteMin1( PriorityQueue H );

        #define Insert( X, H ) ( H = Insert1( ( X ), H ) )
        /* DeleteMin macro is left as an exercise */

void PrintTree(PriorityQueue T, int depth);
        #endif

/* END */
