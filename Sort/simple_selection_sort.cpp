/*
    简单选择排序
    test list: 38 10 53 12 45 76 32 8 43 7
    length: 10
*/
#include <cstdio>
#include <vector>

void print_list(const std::vector<int>& my_list)
{
    for (auto& i : my_list) {
        printf("%d ", i);
    }
}

int main()
{
    int length = 0;
    int input_buffer = 0;
    int key_loc = 0;
    std::vector<int> my_list;

    scanf("%d", &length);
    for (int i=0; i < length; ++i) {
        scanf("%d", &input_buffer);
        my_list.push_back(input_buffer);
    }

    for (int i=0, temp=0; i < length; ++i) {    //对n个记录的序列进行n次简单选择排序
        key_loc = i;    //
        for (int j=i; j < length; ++j) {    //进行一趟简单选择排序
            if (my_list[key_loc] > my_list[j])  //选出一趟中最小值
                key_loc = j;    //记录最小值位置
        }
        temp = my_list[i];  //将最小值放置在靠前的位置
        my_list[i] = my_list[key_loc];
        my_list[key_loc] = temp;
    }

    print_list(my_list);

    return 0;
}