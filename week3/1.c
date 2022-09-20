
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

void upHeap(InsertionHeap *heap, int index)
{
	int new;

	new = index;
	while (new > 1 && heap->array[new] > heap->array[parentIndex(new)])
	{ // 부모가 자신보다 작으면 바꾸기
		swap(&(heap->array[new]), &(heap->array[parentIndex(new)]));
		new = parentIndex(new);
	}
}

void insertItem(InsertionHeap *heap, int item)
{
	int index;

	if (isFull(heap))
		return ;

	heap->size++;
	index = heapSize(heap);
	heap->array[index] = item;

	upHeap(heap, heapSize(heap));
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

int removeMax(InsertionHeap *heap)
{
	int max;

	if (isEmpty(heap))
		return -1;

	max = heap->array[1];
	swap(&(heap->array[heapSize(heap)]), &(heap->array[1]));
	heap->size--;
	
	downHeap(heap, 1);
	
	return max;
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
	heap = initInsertionHeap();
	char command;
	int item;

	while (1)
	{
		scanf("%c",&command);
		
		switch (command)
		{
			case 'i': // insert
				scanf("%d", &item);
				insertItem(heap, item);
				printf("0\n");
				break;
			case 'd': // delete
				item = removeMax(heap);
				printf("%d\n", item);
				break;
			case 'p': // print
				printHeap(heap);
				break;
			case 'q':
				exit(0);
		}
		getchar();
	}
	
	printf("\n");
}
