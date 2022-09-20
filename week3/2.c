
# include<stdio.h>
# include<stdlib.h>
# define MAX_SIZE 100

typedef struct _insertionHeap
{
	int array[MAX_SIZE];
	int size;
} InsertionHeap;

InsertionHeap *initInsertionHeap()
{
	InsertionHeap *heap;

	heap = (InsertionHeap *)malloc(sizeof(InsertionHeap));
	heap->size = 0; // 초기 사이즈 0으로 초기화

	return heap;
}

void swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int heapSize(InsertionHeap *heap)
{
	return heap->size;
}

int isEmpty(InsertionHeap *heap)
{
	if (heapSize(heap) == 0)
		return 1;
	else
		return 0;
}

int isFull(InsertionHeap *heap)
{
	if (heapSize(heap) == MAX_SIZE)
		return 1;
	else
		return 0;
}

int parentIndex(int index)
{
	return index/2;
}

int leftChildIndex(int index)
{
	return index * 2;
}

int rightChildIndex(int index)
{
	return index * 2 + 1;
}

void downHeap(InsertionHeap *heap, int index)
{
	int left, right;
	int greater;


	left = leftChildIndex(index);
	right = rightChildIndex(index);
	
	if (left > heapSize(heap))
		return ;

	greater = left;
	if (right <= heapSize(heap))
		if (heap->array[right] > heap->array[greater])
			greater = right;

	if (heap->array[index] >= heap->array[greater])
		return;
	
	swap(&(heap->array[index]), &(heap->array[greater]));
	downHeap(heap, greater);
}

void buildHeap(InsertionHeap *heap)
{
	int i;
	
	for (i = heapSize(heap)/2; i >= 1; i--)
		downHeap(heap, i);
}

void rBuildHeap(InsertionHeap *heap, int index)
{
	if (index > heapSize(heap))
		return ;

	rBuildHeap(heap, leftChildIndex(index));
	rBuildHeap(heap, rightChildIndex(index));
	downHeap(heap, index);
}

void printHeap(InsertionHeap *heap)
{
	int i;

	for (i = 1; i <= heap->size; i++)
		printf(" %d", heap->array[i]);
	printf("\n");
}

int main()
{
	InsertionHeap *heap;
	int n, i;

	heap = initInsertionHeap();
	scanf("%d", &n);
	heap->size = n;
    for (i = 1; i <= n; i++)
        scanf("%d", &(heap->array[i]));
    
    // buildHeap(heap);
    rBuildHeap(heap, 1);
    printHeap(heap);
}
