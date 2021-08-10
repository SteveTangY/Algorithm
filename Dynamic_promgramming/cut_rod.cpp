/*
    钢管切割实例
    书上只给出了求最后结果的方法，没给求切割方案的方法
*/
#include <cstdio>
#include <cstring>
#include <vector>

const int rod_length = 10;
const int price_array[11] = {0,1,5,8,9,10,17,17,20,24,30};

int buttom_to_top()
{
    int result_array[11] = {0};
    int p = -1;

    
    for (int cut_length=1, sub_length=1; sub_length <= rod_length; ++sub_length) {
        p = -1;
        for (cut_length=1; cut_length <= sub_length; ++cut_length) {
            p = (p > price_array[cut_length] + result_array[sub_length - cut_length])? p : price_array[cut_length] + result_array[sub_length - cut_length];
        }
        result_array[sub_length] = p;
    }
    return result_array[rod_length];
}

int top_to_buttom()
{
    return 0;
}

int main()
{
    printf("%d\n", buttom_to_top());
    printf("%d\n", top_to_buttom());
    return 0;
}