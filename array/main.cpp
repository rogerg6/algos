#include <iostream>
using namespace std;

/**
 * @brief 插入元素到数组中, 最后的元素会被挤出array
 *
 * @param arr 数组指针
 * @param n   数组元素个数
 * @param num 要插入的元素
 * @param index 插入的位置
 */
int insert(int *arr, int n, int num, int index) {
    for (int i = n - 1; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = num;
    return 0;
}

/**
 * @brief 删除数组中指定位置的元素, index后面的元素往前移动一位
 * @param arr 数组指针
 * @param n   数组元素个数
 * @param index 要删除的元素位置
 */
void remove(int *arr, int n, int index) {
    for (int i = index; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
}

/**
 * @brief 重新分配数组大小
 * @param arr 数组指针
 * @param n   数组元素个数
 * @param newsize 新的数组大小, 一般newsize > n
 */
bool resize(int **arr, int n, int newsize) {
    int *newarr = new int[newsize];
    if (!newarr) return false;

    for (int i = 0; i < n; i++) newarr[i] = (*arr)[i];
    delete[] * arr;

    *arr = newarr;

    return true;
}

void print(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}



int main(int ac, char *av[]) {
    // allocated on stack
    int a[5]{1, 2, 4, 5, 7};
    int b[10];

    // allocated on heap
    int *c = new int[9];
    int *d = new int[9]{6, 4, 2, 4, 3};

    remove(a, 5, 2);
    print(a, 5);

    insert(d, 9, 9, 2);
    print(d, 9);

    resize(&d, 9, 20);
    print(d, 20);

    // free
    delete[] c;
    delete[] d;

    return 0;
}