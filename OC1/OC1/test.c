/* ################################

	�ҳ��������ظ�������
     
	��Ŀһ����һ������Ϊ n ����������������ֶ��� 0 ~ n-1 �ķ�Χ�ڡ�������ĳЩ�������ظ��ģ�
����֪���м��������ظ��ˣ�Ҳ��֪��ÿ�������ظ��˼��Ρ����ҳ�����������һ���ظ������֡�
	���磺������볤��Ϊ 7 ������{2��3��1��0��2��5��3}����ô��Ӧ��������ظ������� 2 �� 3��

################################### */

#include <stdio.h>

#if 0    // ����һ
/*
	��򵥵ķ��������Ȱ��������������Ȼ��������飬�ҵ��ظ�������
	����һ������Ϊ n ��������Ҫ��ʱ�临�Ӷ�Ϊ O(nlogn)��
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
			printf("�ظ�����Ϊ��%d , ���ظ������ظ�����Ϊ��%d \n", duplication, count);
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

#if 1   //������
/* ################################

	������û�а������ظ������ֶ���ӡ�������ͺ��񷽷�һ��ֻ��ӡ���ظ������֣���û�з����ظ�ֵ���ʴ˲��Һ�����ֻ�ж��Ƿ�����ظ�ֵ��
	���ù�ϣ������

	���ȣ������������һ��û���ظ���ֵ��
		һ������Ϊ�գ�
		������Ϊ�����е����ֶ��� 0 ~ n-1 ֮�䣬������������û���ظ������֣���ô����������֮������ i ���������±�Ϊ i ��λ�á�
		    �ʵ����ظ�����ʱ�������ǲ������ġ�

	��������������顣��ͷ��β����ɨ��������顣�� �������±�Ϊ i ʱ����numbers[i] = m;���ȱȽ� m �ǲ��ǵ��� i ��--> 
	����ǣ�˵����������ֿ���������������ű�����һ����������ǣ������±�Ϊ m �͵� m �����Ƚϡ�-->    
	�����ȣ�˵���ҵ�һ���ظ������֣����ظ����������±�Ϊ i �� m ��λ�ó��֣���
	�������ȣ��ͽ���λ�á� -->  �ظ��˹��̡�

	����ֵ��ʾ�������Ƿ�����ظ������֡�������������д����ظ�������ʱ������ true ; ���򷵻� false��
	ÿ���������ֻҪ�������ξ����ҵ������Լ���λ�ã����ʱ�临�Ӷ�Ϊ O(n)��
	���еĲ������߶��������������Ͻ��еģ�����Ӵ������ķ����ڴ棬���Կռ临�Ӷ�Ϊ O(1)��

################################### */

int FindDuplicateNumber(int numbers[], int sz, int* duplication)
{
	//����Ϊ��
	if (numbers == NULL || sz <= 0)
	{
		return 0;
	}

	//����Ԫ�ز��ڹ涨��Χ��
	for (int i = 0; i < sz; ++i)
	{
		if (numbers[i]<0 || numbers[i]>sz - 1)
		{
			return 0;
		}
	}

	for (int i = 0; i < sz; ++i)
	{
		//�ж��Ƿ�����ظ�������
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
		printf("�ظ������֣�%d\n", duplication);
	}
	else
	{
		printf("û���ظ�������\n");
	}
}

#endif

/* ################################

	��Ŀ�������޸������ҵ��ظ������֡�

	��һ������Ϊ n+1 ����������������ֶ��� 1 ~ n �ķ�Χ�ڣ�����������������һ���������ظ��ġ�
���ҳ�����������һ���ظ������֣��������޸���������顣	
    ���磺������볤��Ϊ 8 ������{2��3��5��4��3��2��6��7}����ô��Ӧ��������ظ������� 2 �� 3��

################################### */


/* ################################

	��һ�����������
		��1�������޸����飻
		��2����������ж��ǲ��Ǵ����ظ������֣�����һ�����ڣ��ҵ����ڵ���˭

################################### */


/* ################################

	˼·�����ݵ�һ�⣬���Ǻ����׾Ϳ����뵽���ְ취��һ�����Ǳ������ң�һ���Ǵ���һ�����飬��������������ԭ�������޸ġ�
		���������ְ취����һ��ʱ�临�ӶȽϴ󣬵ڶ�����Ҫ O(n) �ĸ����ռ䡣
		  ��ô������һ�±��⣬���ȸ����������������ݷ�Χ���ɵ�һ�������ظ����֡�ԭ�����ڣ�����û���ظ������֣���ô
		1 ~ n �ķ�Χ�����ֻ���� n �����֣���Ŀǰ�� n+1 �����֣�˵��һ�������ظ������֡�
		  ��ˣ�����������������ֲ����㷨��˼�����롣
	
	���������� 1 ~ n �����ִ��м����� m �ֳ������֣��Ĳ��ֵ�Ԫ�ظ������� m ��˵���ظ����������Ĳ��֡�

	ʱ�临�Ӷȣ�O(nlogn)   �ռ临�Ӷȣ�O(1)

	���㷨�޷��ҳ������ظ������֡�

################################### */

int getDuplication(const int* numbers, int sz)
{
	int start = 1;
	int end = sz - 1;

	//����Ϊ��
	if (numbers == NULL || sz <= 0)
	{
		return -1;
	}

	//����
	while (end >= start)
	{
		int middle = ((end - start) >> 1) + start;
		int count = countRange(numbers, sz, start, middle);   //ͳ�ƶ��ֺ�����Ԫ�ظ���
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

		//�ж��ظ��������ڶ��ֺ���һ����
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

//ͳ������Ԫ�ظ���
int countRange(const int* numbers, int sz, int start, int end)
{
	int count = 0;
	int i = 0;

	//����Ϊ��
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
	printf("�ظ�������Ϊ��%d\n", ret);
}

int main()
{
    //test1();
	//test2();
	Test();
	return 0;
}