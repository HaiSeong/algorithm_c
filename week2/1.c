
# include<stdio.h>
# include<stdlib.h>

typedef struct _list
{
	int *array;
	int maxSize;
	int size;
} list;

list *initList(int n)
{
	list *lst;

	lst = (list *)malloc(sizeof(list));
	lst->array = (int *)malloc(sizeof(int) * n);
	lst->maxSize = n;
	lst->size = 0; // 초기 사이즈 0으로 초기화

	return lst;
}

int listSize(list *lst)
{
	return lst->size;
}

int isEmpty(list *lst)
{
	if (listSize(lst) == 0)
		return 1;
	else
		return 0;
}

int isFull(list *lst)
{
	if (listSize(lst) == lst->maxSize)
		return 1;
	else
		return 0;
}

void insertItem(list *lst, int item)
{
	if (isFull(lst))
		return ;
	
	lst->array[lst->size] = item;
	(lst->size)++;
}

int removeMin(list *lst)
{
	int min;
	int minIdx;
	int i, temp;

	if (isEmpty(lst))
		return -1;
	
	min = lst->array[0];
	minIdx = 0;
	for (i = 1; i < lst->size; i++)
	{
		if (min > lst->array[i])
		{
			min = lst->array[i];
			minIdx = i;
		}
	}
	temp = lst->array[lst->size - 1];
	lst->array[lst->size - 1] = lst->array[minIdx];
	lst->array[minIdx] = temp;
	lst->size--;

	return min;
}

void freeList(list *lst)
{
	free(lst->array);
	free(lst);
}

int main()
{
	list *lst;
	int n;
	int i, temp;

	scanf("%d", &n);
	lst = initList(n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &temp);
		insertItem(lst, temp);
	}
	for (i = 0; i < n; i++)
		printf(" %d", removeMin(lst));
	
	freeList(lst);
}
