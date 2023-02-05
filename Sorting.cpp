#include <iostream>
#include "Sorting.h"
#define SIZE 20

class sort {
public:
	/// <summary>
	/// Bubble sort. Swaps two next-door elements till the array unsorted
	/// </summary>
	/// <typeparam name="T">any type with the comparison operators overloaded</typeparam>
	/// <param name="arr">- array to sort</param>
	/// <param name="size">- size of array</param>
	/// <returns>sorting time taken</returns>
	template<typename T>
	static float bubble(T arr[], int size) {
		clock_t ts = clock();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - i - 1; j++)
			{
				if (arr[j] > arr[j + 1]) {
					sort::Swap(arr[j], arr[j + 1]);
				}
			}
		}
		clock_t te = clock();
		return ((float)(te - ts)) / (float)CLOCKS_PER_SEC;
	}

	template<typename T>
	static float* test(float(* a)(T, int)) {
		int arr_size = 0;
		float* res = new float[10];
		for (int j = 0; j < 10; j++)
		{
			arr_size = 5000 * (j + 1);
			int* arr = new int[arr_size];
			for (int i = 0; i < arr_size; i++)
			{
				arr[i] = rand() % 100;
			}
			res[j] = a((T)arr, arr_size);
			delete[] arr;
		}
		return res;
	}
private:
	template<typename T>
	static void Swap(T& _left, T& _right) {
		T temp = _left;
		_left = _right;
		_right = temp;
	}
};

void printArray(int arr[], int size) {
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;
}

int main()
{
    int arr[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = rand() % 40;
	}
	printArray(arr, SIZE);
	sort::bubble(arr, SIZE);
	printArray(arr, SIZE);

	float (*x)(char* s, int a);
	x = sort::bubble;

	float* r = sort::test(x);
	for (int i = 0; i < 10; i++)
	{
		std::cout << r[i] << "s, ";
	}
	delete[] r;
}
