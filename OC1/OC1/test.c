/* ################################

	找出数组中重复的数字
     
	题目一：在一个长度为 n 的数组里的所有数字都在 0 ~ n-1 的范围内。数组中某些数字是重复的，
但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
	例如：如果输入长度为 7 的数组{2，3，1，0，2，5，3}，那么对应的输出是重复的数字 2 或 3。

################################### */

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
/* ################################

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

################################### */

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
		printf("重复的数字：%d\n", duplication);
	}
	else
	{
		printf("没有重复的数字\n");
	}
}

#endif

/* ################################

	题目二：不修改数组找到重复的数字。

	在一个长度为 n+1 的数组里的所有数字都在 1 ~ n 的范围内，所有数组中至少有一个数字是重复的。
请找出数组中任意一个重复的数字，但不能修改输入的数组。	
    例如：如果输入长度为 8 的数组{2，3，5，4，3，2，6，7}，那么对应的输出是重复的数字 2 或 3。

################################### */


/* ################################

	题一与题二的区别：
		（1）不能修改数组；
		（2）题二不用判断是不是存在重复的数字，而是一定存在，找到存在的是谁

################################### */


/* ################################

	思路：根据第一题，我们很容易就可以想到两种办法，一个就是遍历查找；一个是创建一个数组，用来代替我们在原数组上修改。
		但是这两种办法，第一个时间复杂度较大，第二个需要 O(n) 的辅助空间。
		  那么，分析一下本题，首先根据这道题数组的数据范围，可得一定存在重复数字。原因在于：假如没有重复的数字，那么
		1 ~ n 的范围内最多只能有 n 个数字，而目前有 n+1 个数字，说明一定存在重复的数字。
		  因此，我们这道题可以向二分查找算法的思想上想。
	
	方法：将从 1 ~ n 的数字从中间数字 m 分成两部分，哪部分的元素个数大于 m ，说明重复的数字在哪部分。

	时间复杂度：O(nlogn)   空间复杂度：O(1)

	此算法无法找出所有重复的数字。

################################### */

int getDuplication(const int* numbers, int sz)
{
	int start = 1;
	int end = sz - 1;

	//数组为空
	if (numbers == NULL || sz <= 0)
	{
		return -1;
	}

	//二分
	while (end >= start)
	{
		int middle = ((end - start) >> 1) + start;
		int count = countRange(numbers, sz, start, middle);   //统计二分后区域元素个数
		if (end == start)
		{
			if (count > 1)
			{
				return start;
			}
			else
			{
				break;
			}
		}

		//判断重复的数字在二分后哪一部分
		if (count > (middle - start + 1))
		{
			end = middle;
		}
		else
		{
			start = middle + 1;
		}
	}
	return -1;
}

//统计区域元素个数
int countRange(const int* numbers, int sz, int start, int end)
{
	int count = 0;
	int i = 0;

	//数组为空
	if (numbers == NULL)
	{
		return 0;
	}

	for (i = 0; i < sz; i++)
	{
		if (numbers[i] >= start && numbers[i] <= end)
		{
			++count;
		}
	}

	return count;
}

void Test()
{
	const int numbers[] = { 2,3,5,4,3,2,6,7 };
	int sz = sizeof(numbers) / sizeof(numbers[0]);
	int ret = getDuplication(numbers, sz);
	printf("重复的数字为：%d\n", ret);
}

int main()
{
    //test1();
	//test2();
	Test();
	return 0;
}