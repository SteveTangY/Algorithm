/*
    折半插入排序
*/
#include <unistd.h>
#include <cstdio>
#include <vector>

void print_list(std::vector<int>& list)
{
    for (auto& i : list) {
        printf("%d ", i);
    }
    printf("\n");

    return;
}

int main()
{
    int length = 0;
    int low = 0, high = 0, mid = 0;
    int input_buffer = 0;
    std::vector<int> my_list;

    scanf("%d", &length);
    // printf("length is:%d\n", length);
    scanf("%d", &input_buffer);
    // printf("input_buffer is:%d", input_buffer);
    my_list.push_back(input_buffer);
    for (int i=1; i < length; ++i) {
        scanf("%d", &input_buffer);
        if (input_buffer > my_list.back()) {
                my_list.push_back(input_buffer);
                continue;
        }
        
        low = 0;
        high = my_list.size() - 1;
#if 1
        for (; low <= high; ) {
            // printf("|%d %d %d|", low, high, mid);
            mid = (low + high) / 2;
            if (input_buffer > my_list[mid]) {
                low = mid + 1;
            } else {
                high = mid - 1;
             }
            // usleep(1000);
        }
#else        
        /* 这种迭代方式会有即使low>high时仍会改变mid值的bug而导致排序错误 */
        mid = (low + high) / 2;
        for (; low <= high; ) {
            // printf("|%d %d %d|", low, high, mid);
            if (input_buffer > my_list[mid]) {
                low = mid + 1;
                mid = (low + high) / 2;
            } else {
                high = mid - 1;
                mid = (low + high) / 2;
             }
            // usleep(1000);
        }
#endif
        // printf("break");
        my_list.insert(my_list.begin()+mid, input_buffer);
        print_list(my_list);
    }

    print_list(my_list);

    return 0;
}