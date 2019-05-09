/*
题目：找出数组中重复的数字
     
	 在一个长度为 n 的数组里的所有数字都在 0 ~ n-1 的范围内。数组中某些数字是重复的，
但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
例如：如果输入长度为 7 的数组{2，3，1，0，2，5，3}，那么对应的输出是重复的数字 2 或 3.

*/

#include <stdio.h>

#if 0    // 方法一
/*
	最简单的方法就是先把输入的数组排序，然后遍历数组，找到重复的数。
	排序一个长度为 n 的数组需要的时间复杂度为 O(nlogn)。
*/

void BubbleSort(int numbers[], int sz)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < sz - 1; i++)
	{
		for (j = 0; j < sz - 1 - i; j++)
		{
			if (numbers[j] > numbers[j + 1])
			{
				int tmp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = tmp;
			}
		}
	}
}

void FindDuplicateNumber(int numbers[], int sz)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < sz; i++)
	{
		if (numbers[i] == numbers[i + 1])
		{
			int count = 2;
			int duplication = numbers[i];
			for (j = i + 2; j < sz; j++)
			{
				if (duplication == numbers[j])
				{
					count++;
				}
				if (duplication != numbers[j])
				{
					i = j - 1;
					j = sz + 1;
				}
			}
			printf("重复数字为：%d , 此重复数字重复次数为：%d \n", duplication, count);
		}
	}
}

void Print(int numbers[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", numbers[i]);
	}
	printf("\n");
}

void test1()
{
	int numbers[] = { 2,3,1,0,2,5,3};
	int sz = sizeof(numbers) / sizeof(numbers[0]);
	BubbleSort(numbers, sz);
	Print(numbers, sz);
	FindDuplicateNumber(numbers, sz);
}

#endif 

#if 1   //方法二
/*
	方法二没有把所有重复的数字都打印出来，就好像方法一，只打印出重复的数字，并没有返回重复值。故此查找函数中只判断是否存在重复值。
	利用哈希表解决。
	首先，有两种情况下一定没有重复的值。
		一：数组为空；
		二：因为数组中的数字都在 0 ~ n-1 之间，如果这个数组中没有重复的数字，那么当数组排序之后数字 i 将出现在下标为 i 的位置。
		    故当有重复数字时，上面是不成立的。
	现在重排这个数组。从头到尾依此扫描这个数组。当 遍历到下标为 i 时，记numbers[i] = m;首先比较 m 是不是等于 i 。--> 
	如果是，说明，这个数字可以排在这儿，接着遍历下一个；如果不是，则拿下标为 m 和第 m 个数比较。-->    
	如果相等，说明找到一个重复的数字（该重复的数字在下标为 i 和 m 的位置出现）；
	如果不相等，就交换位置。 -->  重复此过程。

	返回值表示数组中是否存在重复的数字。当输入的数组中存在重复的数字时，返回 true ; 否则返回 false。
	每个数字最多只要交换两次就能找到属于自己的位置，因此时间复杂度为 O(n)。
	所有的操作不走都是在输入数组上进行的，不许哟啊额外的分配内存，所以空间复杂度为 O(1)。
*/

int FindDuplicateNumber(int numbers[], int sz, int* duplication)
{
	//数组为空
	if (numbers == NULL || sz <= 0)
	{
		return 0;
	}

	//数组元素不在规定范围内
	for (int i = 0; i < sz; ++i)
	{
		if (numbers[i]<0 || numbers[i]>sz - 1)
		{
			return 0;
		}
	}

	for (int i = 0; i < sz; ++i)
	{
		//判断是否存在重复的数字
		while (numbers[i] != i)
		{

			if (numbers[i] == numbers[numbers[i]])
			{
				*duplication = numbers[i];
				return 1;
			}

			//swap numbers[i] and numbers[numbers[i]]
			int temp = numbers[i];
			numbers[i] = numbers[temp];
			numbers[temp] = temp;

		}
	}
	return 0;
} 

void test2()
{
	int number[] = { 2,3,1,0,2,5,3 };
	int sz = sizeof(number) / sizeof(number[0]);
	int duplication = 0;
	if (FindDuplicateNumber(number, sz, &duplication) == 1)
	{
		printf("%d\n", duplication);
	}
	else
	{
		printf("没有重复的数字\n");
	}
}

#endif

int main()
{
    //test1();
	test2();
	return 0;
}