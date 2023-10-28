#include <stdio.h>
#include <stdbool.h> // 引入标准的stdbool.h头文件
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // 包含unistd.h头文件以使用sleep函数

#define MAX_QUEUE_SIZE 10
typedef unsigned short int uint16_t; 

// 定义队列结构体
typedef struct {
    uint16_t data[MAX_QUEUE_SIZE]; // 存储浮点数数据的数组
    int front;  // 前端索引，用于出队
    int rear;   // 后端索引，用于入队
    
} intQueue;

// 打印队列中的所有数据
void printQueue(const intQueue *queue) {
    if (queue->front == -1) {
        printf("intQueue is empty.\n");
        return;
    }

    int current = queue->front;
    while (current != queue->rear) {
        printf("%u ", queue->data[current]);
        current = (current + 1) % MAX_QUEUE_SIZE;
    }
    printf("%u\n", queue->data[current]);
}

// 初始化队列
void initializeintQueue(intQueue *queue) {
    if (!queue)return;
    
    queue->front = 0;   // 初始化前端索引
    queue->rear = 0;   // 初始化后端索引
}

// 检查队列是否为空
int isintQueueEmpty(intQueue *queue) {
    return (queue->front == queue->rear);
}

// 检查队列是否已满
int isintQueueFull(intQueue *queue) {
    int nextRear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    return (nextRear == queue->front);
}

// 入队操作
void enqueueint(intQueue *queue, uint16_t value) {
    if (((queue->rear + 1) % MAX_QUEUE_SIZE) != queue->front) {
        queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
        queue->data[queue->rear] = value;
    } else {
        printf("intQueue is full. Cannot enqueue.\n");
    }
}

// 出队操作
uint16_t dequeueint(intQueue *queue) {
    if (queue->front != queue->rear) {
        uint16_t value = queue->data[queue->front];
        queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
        return value;
    } else {
        return 0;
    }
}

//队列元素之和
uint16_t calculateSum(const intQueue *queue) {
    if (queue->front == -1) {
        printf("intQueue is empty.\n");
        return 0;
    }

    uint16_t sum = 0;
    int current = queue->front;
    while (current != queue->rear) {
        sum += queue->data[current];
        current = (current + 1) % MAX_QUEUE_SIZE;
    }
    sum += queue->data[current]; // 添加队列尾部的元素
    return sum;
}

// 快速排序算法函数
void quickSort(uint16_t arr[], int low, int high) {
    // 交换两个浮点数的函数
    void swap(int *a, int *b) {
        uint16_t temp = *a;
        *a = *b;
        *b = temp;
    }

    if (low < high) {
        int pivotIndex = low;
        uint16_t pivotValue = arr[high];

        for (int i = low; i < high; i++) {
            if (arr[i] < pivotValue) {
                swap(&arr[i], &arr[pivotIndex]);
                pivotIndex++;
            }
        }

        swap(&arr[pivotIndex], &arr[high]);

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// 获取队列中的最大值
uint16_t getMax(const intQueue *queue) {
    if (queue->front == -1) {
        printf("intQueue is empty.\n");
        return 0; // 或者返回一个特定的值，取决于你的需求
    }

    uint16_t max = queue->data[queue->front];
    int current = queue->front;
    while (current != queue->rear) {
        current = (current + 1) % MAX_QUEUE_SIZE;
        if (queue->data[current] > max) {
            max = queue->data[current];
        }
    }
    return max;
}

// 获取队列中的最小值
uint16_t getMin(const intQueue *queue) {
    if (queue->front == -1) {
        printf("intQueue is empty.\n");
        return 0; // 或者返回一个特定的值，取决于你的需求
    }

    uint16_t min = queue->data[queue->front];
    int current = queue->front;
    while (current != queue->rear) {
        current = (current + 1) % MAX_QUEUE_SIZE;
        if (queue->data[current] < min) {
            min = queue->data[current];
        }
    }
    return min;
}


uint16_t Stable_Judge(uint16_t f)	//f是源源不断的值				
{
    static intQueue myintQueue;
    uint16_t sum,avg;              //数据之和和8数的平均值
    uint16_t maxValue,minValue;          //最大值和最小值
    uint16_t out_que;   //出队数据的值

    static bool init_flag = false; 

    
    if(!isintQueueFull(&myintQueue))    //初始数据入队
    {
        if (init_flag == false)
        {
            initializeintQueue(&myintQueue);    //初始化队列，仅运行一次
            init_flag = true;
        }

        enqueueint(&myintQueue,f);
        return 8;                       //初始10个数据入队时，返回8
    }
    else
    {
        printf("初始的队列数据为:");
        printQueue(&myintQueue);  

        out_que = dequeueint(&myintQueue);    //将一个数据出队
        printf("---%u---出队\n",out_que);

        // minValue = getMin(&myintQueue);    
        // maxValue = getMax(&myintQueue);
        // printf("最大值为:%u  最小值为:%u\n",maxValue,minValue);

        enqueueint(&myintQueue,f);          //一个数据入队
        printf("---%u---入队\n",f);

        minValue = getMin(&myintQueue);    
        maxValue = getMax(&myintQueue);
        printf("最大值为:%u  最小值为:%u\n",maxValue,minValue);

        printf("改变后队列数据为:");
        printQueue(&myintQueue);

        if (f <= minValue || f >= maxValue)
        {
            
            sum=calculateSum(&myintQueue);
            printf("对列之和为:%u\n",sum);
            sum=sum-minValue-maxValue;
            printf("减去最大值和最小值以后，队列数据的和为:%u\n",sum);

            avg=sum/8;
            printf("平均值为:%u\n",avg);

            return avg;
        }
        else
        {
            printf("%u是一个稳定值---不做操作-------------------",f);
            return 8;
        }
        
           
    }  
}


int main()
{
    while (1)
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        srand((unsigned)ts.tv_nsec);

        uint16_t randomValue = 8 + (rand() % 8);
        printf("传感器模拟数为%u\n",randomValue);

        uint16_t a = Stable_Judge(randomValue);
        printf("最终输出值为: %u\n", a);
        printf("\n");

        sleep(1);
    }

    return 0;
}