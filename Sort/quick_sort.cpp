/*
    快速排序
    test list: 49 38 65 97 76 13 27 49
    length: 8
*/
#include <cstdio>
#include <vector>

int partition(std::vector<int>& my_list, const int& low_loc, const int& high_loc)
{
    int privot_key = 0;
    int low=low_loc, high=high_loc;

    for (privot_key=my_list[low]; low < high; ) {   //进行一趟快排，将区间以枢轴量为中心一分为二，一般选取输入区间的第一个记录作为枢轴量
        for (; low < high && privot_key <= my_list[high]; --high) {}
        my_list[low] = my_list[high];
        for (; low < high && privot_key >= my_list[low]; ++low) {}
        my_list[high] = my_list[low];
    }
    my_list[low] = privot_key;   //取消了中间过程对枢轴量的赋值(因为这样做无意义)，仅在最后确定枢轴量位置后才对其赋值，这样可以减少交换一对记录所用的赋值次数
    return low;
}

/* 重点是将区间分为二后怎么对剩下的区间也进行快排，现在这种方式是以递归的方式利用栈进行处理 */
void quick_sort(std::vector<int>& my_list, const int& low_loc, const int& high_loc)
{
    int privot_loc = 0;
    if (low_loc < high_loc) {
        privot_loc = partition(my_list, low_loc, high_loc);//对输入区间进行一趟快排并返回枢轴量位置
        quick_sort(my_list, low_loc, privot_loc-1);//递归对枢轴量左边区间进行快排
        quick_sort(my_list, privot_loc+1, high_loc);//递归对枢轴量右边区间进行快排
    }
}

void print_list(std::vector<int>& my_list)
{
    for (auto& i : my_list) {
        printf("%d ", i);
    }
}

int main()
{
    int length = 0;
    int input_buffer = 0;
    std::vector<int> my_list;

    scanf("%d", &length);
    for (int i; i < length; ++i) {
        scanf("%d", &input_buffer);
        my_list.push_back(input_buffer);
    }

    quick_sort(my_list, 0, my_list.size()-1);

    print_list(my_list);

    return 0;
}