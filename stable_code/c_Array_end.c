//最终代码
//数组


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef unsigned short int uint16_t; 

#define MAX_SIZE_ARR 10

void quickSort(uint16_t arr[], int left, int right) 
{
    if (left < right) {
        int pivot, i, j;
        uint16_t temp;
        pivot = left;
        i = left;
        j = right;

        while (i < j) {
            while (arr[i] <= arr[pivot] && i < right)
                i++;
            while (arr[j] > arr[pivot])
                j--;
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;

        quickSort(arr, left, j - 1);
        quickSort(arr, j + 1, right);
    }
}

uint16_t Stable_Judge(uint16_t flowVal_init) 
{
    static uint16_t myShortArray[MAX_SIZE_ARR]; //静态数组
    static int itemCount = 0;                   //定义一个静态值
    uint16_t avg, sum = 0;

    if (itemCount == MAX_SIZE_ARR)              //如果数组不满时
    {
        for (int i = 0; i < MAX_SIZE_ARR; i++)      //数组元素的和
        {
            sum += myShortArray[i];
        }

        quickSort(myShortArray, 0, MAX_SIZE_ARR - 1);   //快速排序
        avg = (sum - myShortArray[0] - myShortArray[MAX_SIZE_ARR - 1]) / (MAX_SIZE_ARR - 2);    


        //将数组清空，为下10个数做准备
        for (int i = 0; i < MAX_SIZE_ARR; i++)  
        {
            myShortArray[i] = 0;
        }
        itemCount = 0;
        return avg;
    }
    else
    {
        myShortArray[itemCount] = flowVal_init;     //元素进入数组，默认返回8
        itemCount++;
        return 8;
    }
}

int main()
{
    while (1)
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        srand((unsigned)ts.tv_nsec);

        int randomValue = 8 + (rand() % 8);     //模拟传感器返回的值    8到15的整数 

        printf("%u\n",randomValue);
        uint16_t a = Stable_Judge(randomValue);
        printf("最终值为: %u\n", a);

        sleep(1);
    }

    return 0;
}
