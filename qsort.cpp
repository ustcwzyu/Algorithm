/* 
    Created by 汪振宇 SA18225350 2018/10/31
*/
#include<iostream>
#include<ctime>
using namespace std;

class Qsort{
    public:
        Qsort() {}
        
        void swap(int a[], int p, int q) {
            int temp = a[p];
            a[p] = a[q];
            a[q] = temp;
        }

        int partition(int a[], int low, int high) {
            int pivot = a[high];
            int i = low-1;
            for (int j = low; j < high; j++) {
                if (a[j] <= pivot) {
                    i++;
                    swap(a, i, j);
                }
            }
            swap(a, i+1, high);
            return i+1;
        }

        void  QuickSort(int a[], int l, int h) {
            if (l < h) {
                int q = partition(a, l, h);
                QuickSort(a, l, q-1);
                QuickSort(a, q+1, h);
            }
        }
};

//Optimize the quicksort
class QsortWithInsertionSort{
    public:
        QsortWithInsertionSort() {}
        
        void swap(int a[], int p, int q) {
            int temp = a[p];
            a[p] = a[q];
            a[q] = temp;
        }

        int partition(int a[], int low, int high) {
            int pivot = a[high];
            int i = low-1;
            for (int j = low; j < high; j++) {
                if (a[j] <= pivot) {
                    i++;
                    swap(a, i, j);
                }
            }
            swap(a, i+1, high);
            return i+1;
        }

        void  QuickSort(int a[], int l, int h, int min_length) {
            if (l < h && h-l < min_length) {
                return;
            }
            if (l < h) {
                int q = partition(a, l, h);
                QuickSort(a, l, q-1, min_length);
                QuickSort(a, q+1, h, min_length);
            }
        }

        void InsertionSort(int a[], int n) {
            for (int j = 0; j < n; j++) {
                int key = a[j];
                int i = j-1;
                while(i > 0 && a[i] > key) {
                    a[i+1] = a[i];
                    i--;
                }
                a[i+1] = key;
            }
        }
};

//Generate the random array
class RandomNumberGenerator{
    public:
        void Generator(int n, int *a) {
            srand((unsigned) time(NULL));
            for (int i = 0; i < n; i++) {
                a[i] = rand() * 100+1;
            }
        }
};

int main() {
    int n;
    cin >> n;
    RandomNumberGenerator _r;
    int *a = new int[n];
    Qsort _instance1;
    QsortWithInsertionSort _instance2;
    int times;
    cin >> times;
    while (times > 0) {
        _r.Generator(n, a);
        int k;
        cin >> k;
        times--;
        clock_t start1 = clock();
        _instance1.QuickSort(a, 0 , n-1);
        clock_t end1 = clock();
        _r.Generator(n, a);
        clock_t start2 = clock();
        _instance2.QuickSort(a, 0 , n-1, k);
        _instance2.InsertionSort(a, n-1);
        clock_t end2 = clock();
        cout << "The time of quicksort is " << double(end1-start1)/CLOCKS_PER_SEC << ".\n" ;
        cout <<"The k is " << k << " and the optimized algorithm time is " << double(end2-start2)/CLOCKS_PER_SEC << "." << endl;
    }
    system("pause");
    return 0;
}