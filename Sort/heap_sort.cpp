/*
    堆排序
    49 38 65 97 76 13 27 49
    8
*/
#include <unistd.h>
#include <cstdio>
#include <cmath>
#include <vector>

void print_list(std::vector<int>& my_list) 
{
    for (auto& i : my_list) {
        printf("%d ", i);
    }
    printf("\n");
}

//大顶堆中对某个非终端节点调整过程
void big_heap_adjust(std::vector<int>& heap_list, const int& position)
{
    int temp = 0;
    if (heap_list[position] < heap_list[2*position] && heap_list[2*position] >= heap_list[2*position+1] && 2*position < heap_list.size()) { //此处需注意2*position与2*position+1(也就是左右孩子节点)是有可能相等的，容易出bug
        temp = heap_list[position];
        heap_list[position] = heap_list[2*position];
        heap_list[2*position] = temp;
        big_heap_adjust(heap_list, 2*position);
    } else if (heap_list[position] < heap_list[2*position+1] && heap_list[2*position+1] >= heap_list[2*position] && 2*position+1 < heap_list.size()) {
        temp = heap_list[position];
        heap_list[position] = heap_list[2*position+1];
        heap_list[2*position+1] = temp;
        big_heap_adjust(heap_list, 2*position+1);
    }
}

//建立大顶堆过程
void build_big_heap(std::vector<int>& heap_list)
{
    int length = heap_list.size();
    int last_parent_node = floor(static_cast<double>(length / 2));    //向下取整
    // printf("last_parent_node is:%d\n", last_parent_node);

    for (int i=last_parent_node, temp=0; i >= 1; --i) {     //建立大顶堆
        // if (heap_list[2*i] > heap_list[i] && 2*i <= length) {
        //     temp = heap_list[i];
        //     heap_list[i] = heap_list[2*i];
        //     heap_list[2*i] = temp;
        // } else if (heap_list[2*i+1] > heap_list[i] && 2*i+1 <= length) {
        //     temp = heap_list[i];
        //     heap_list[i] = heap_list[2*i+1];
        //     heap_list[2*i+1] = temp;
        // }
        big_heap_adjust(heap_list, i);
    }
}



int main()
{
    int length = 0;
    int input_buffer = 0;
    std::vector<int> my_list;
    std::vector<int> heap_list;

    scanf("%d", &length);
    heap_list.push_back(0);   //使整个列表下标从1开始，0的位置为无效值
    for (int i=1; i <= length; ++i) {
        scanf("%d", &input_buffer);
        heap_list.push_back(input_buffer);
    }

    build_big_heap(heap_list);  //先建立一个大顶堆
    for (; heap_list.size() > 1;) { //堆排序过程
        print_list(heap_list);
        usleep(1000000);

        my_list.push_back(heap_list[1]);    //将完全二叉树的根，也就是一维数组的第一个元素(最大值)弹出
        heap_list[1] = heap_list.back();    //将最后一个数据与第一个数据交换(实际上没必要进行两次赋值操作，一次即可)
        heap_list.pop_back();   //弹出最后一个元素，意味着找到了当前序列的最大值
        big_heap_adjust(heap_list, 1);
    }

    print_list(my_list);

    return 0;
}