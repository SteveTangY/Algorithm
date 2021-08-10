/*
    直接插入排序
*/
#include <cstdio>
#include <iostream>
#include <vector>

int main()
{
    int length = 0;
    int input_buffer = 0;
    std::vector<int> my_list;
    scanf("%d", &length);
    //std::cin >> length;

    std::cin >> input_buffer;
    my_list.push_back(input_buffer);

    for (int i=1; i < length; ++i) {
        std::cin >> input_buffer;
        if (input_buffer > my_list.back()) {
            my_list.push_back(input_buffer);
        } else {
            for (int j=0; j < my_list.size(); ++j) {
                if (input_buffer < my_list.at(j)) {
                    my_list.insert(my_list.begin()+j, input_buffer);
                    break;
                }
            }
        }
    }

    for (auto& data : my_list) {
        std::cout << data << " ";
    }

    return 0;
}