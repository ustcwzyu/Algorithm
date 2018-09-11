#include<iostream>
using namespace std;

void swap(int a[], int p1, int p2) {
    int temp;
    temp = a[p1];
    a[p1] = a[p2];
    a[p2] = temp;
}

int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low-1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a, i, j);
        }
    }
    swap(a, i+1, high);
    return i+1;
}

void quicksort(int a[], int low, int high) {
    if (low < high) {
        int q = partition(a, low, high);
        quicksort(a, low, q-1);
        quicksort(a, q, high);
    }
}

int main() {
    int a[3] = {4, 2, 3};
    quicksort(a, 0, 2);
    cout << a[0] << a[1] << a[2] << endl;
    return 0;
}