/*
    冒泡排序
    test list: 8 4 90 3 67 42 9 32 87 32
    list length: 10
*/
#include <cstdio>
#include <vector>

void print_list(const std::vector<int>& my_list)
{
    for(auto& i : my_list) {
        printf("%d ", i);
    }
}

int main()
{
    bool is_finish = false;
    int length = 0;
    int input_buffer = 0;
    int sort_times = 0;
    std::vector<int> my_list;

    scanf("%d", &length);
    for (int i=0; i < length; ++i) {
        scanf("%d", &input_buffer);
        my_list.push_back(input_buffer);
    }

    for (; is_finish != true; ) {
        is_finish = true;
        for (int i=0, temp=0; i < length-1; ++i) {
            if (my_list[i] > my_list[i+1]) {
                temp = my_list[i+1];
                my_list[i+1] = my_list[i];
                my_list[i] = temp;
                is_finish = false;
            }
        }
        sort_times++;
    }

    print_list(my_list);
    printf("\ntimes:%d", sort_times);
    
    return 0;
}