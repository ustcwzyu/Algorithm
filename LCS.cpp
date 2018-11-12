#include <iostream>
using namespace std;
template <class T>
T Min(T* array,int n) { 
T min=array[0];
	for(int i=0;i<n;i++) {if (array[i] < min) min = array[i];}; 
  return min;
}
  int main(){
	double arr[8]={1.2, 2.3, 31.21, 42, 51.5, 6.24, 74.12, 82};
	cout<< Min(arr, 8) ; 
    getchar();
	return 0;
  }