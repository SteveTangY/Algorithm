/*
    希尔排序
    test list: 49 38 65 97 76 13 27 49 55 04
    test list length: 10
*/
#include <unistd.h>
#include <cstdio>
#include <vector>

const int dk_list[] = {5, 3, 1};

void simple_insert_sort(std::vector<int>& temp_list, const int& data)
{   
    if (temp_list.size() == 0) {
        temp_list.push_back(data);
        return ;
    }else if(data > temp_list.back()) {
        temp_list.push_back(data);
        return ;
    }
    int i = 0;

    for (; temp_list[i] < data; ++i) {}

    temp_list.insert(temp_list.begin()+i, data);

    return ;
}

void print_list(std::vector<int>& my_list)
{
    for (int& i : my_list) {
        printf("%d ", i);
    }
    printf("\n");

    return;
}

int main()
{
    int length = 0;
    int input_buf = 0;
    std::vector<int> my_list;
    std::vector<int> temp_list;

    scanf("%d", &length);
    for (int i=0; i < length; ++i) {
        scanf("%d", &input_buf);
        my_list.push_back(input_buf);
        printf("num=%d\n", input_buf);
    }

    for (const int& dk : dk_list) {    //对每个增量进行一次迭代
        for (int count=0, i=0; count < length; ++i) {   //对某个增量进行数趟直接插入排序，同时要保证几趟跑完后所有关键字都进行过排序
            for (int j=0; (i + j*dk) < length; ++j) {   //某趟的直接排序，使用额外的存储空间来存储
                simple_insert_sort(temp_list, my_list[i + j*dk]);
                ++count;
            }
            for (int j=0; (i + j*dk) < length; ++j) {   //将已经排序好的临时列表按顺序将原列表中相应位置的数进行替换
                my_list[i + j*dk] = temp_list[j];
            }
            temp_list.clear();  //清空临时列表
        }
    }

    print_list(my_list);

    return 0;
}