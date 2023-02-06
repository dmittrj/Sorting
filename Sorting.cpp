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

	/// <summary>
	/// Insertion sort. Moves every element into correct place into the left (sorted) side
	/// </summary>
	/// <typeparam name="T">any type with the comparison operators overloaded</typeparam>
	/// <param name="arr">- array to sort</param>
	/// <param name="size">- size of array</param>
	/// <returns>sorting time taken</returns>
	template<typename T>
	static float insertion(T arr[], int size) {
		clock_t ts = clock();
		for (int i = 0; i < size - 1; i++)
		{
			if (arr[i] > arr[i + 1]) {
				for (int j = i; j >= 0; j--)
				{
					if (arr[j] > arr[j + 1]) {
						sort::Swap(arr[j], arr[j + 1]);
					}
					else {
						break;
					}
				}
			}
		}
		clock_t te = clock();
		return ((float)(te - ts)) / (float)CLOCKS_PER_SEC;
	}

	/// <summary>
	/// Bogo sort. Swaps two random elements till array unsorted
	/// </summary>
	/// <typeparam name="T">any type with the comparison operators overloaded</typeparam>
	/// <param name="arr">- array to sort</param>
	/// <param name="size">- size of array</param>
	/// <returns>sorting time taken</returns>
	template<typename T>
	static float bogo(T arr[], int size) {
		clock_t ts = clock();
		srand(size);
		bool unsorted = true;
		while (unsorted)
		{
			unsorted = false;
			sort::Swap(arr[rand() % size], arr[rand() % size]);
			for (int i = 0; i < size - 1; i++)
			{
				if (arr[i] > arr[i + 1]) {
					unsorted = true;
					break;
				}
			}
		}
		clock_t te = clock();
		return ((float)(te - ts)) / (float)CLOCKS_PER_SEC;
	}

	/// <summary>
	/// Cocktail shaker sort. Goes back and forth and swaps two next-door elements till the array unsorted
	/// </summary>
	/// <typeparam name="T">any type with the comparison operators overloaded</typeparam>
	/// <param name="arr">- array to sort</param>
	/// <param name="size">- size of array</param>
	/// <returns>sorting time taken</returns>
	template<typename T>
	static float cocktail_shaker(T arr[], int size) {
		clock_t ts = clock();
		bool swapped = false;
		do
		{
			swapped = false;
			for (int i = 0; i < size - 1; i++)
			{
				if (arr[i] > arr[i + 1]) {
					sort::Swap(arr[i], arr[i + 1]);
					swapped = true;
				}
			}
			for (int i = size - 2; i >= 0; i--)
			{
				if (arr[i] > arr[i + 1]) {
					sort::Swap(arr[i], arr[i + 1]);
					swapped = true;
				}
			}
		} while (swapped);
		clock_t te = clock();
		return ((float)(te - ts)) / (float)CLOCKS_PER_SEC;
	}

	/// <summary>
	/// Quick sort. Divides the array into several parts and sorts them individually
	/// </summary>
	/// <typeparam name="T">any type with the comparison operators overloaded</typeparam>
	/// <param name="arr">- array to sort</param>
	/// <param name="size">- size of array</param>
	/// <returns>sorting time taken</returns>
	template<typename T>
	static float quick(T arr[], int size) {
		return sort::quick(arr, size, 0);
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

	template<typename T>
	static float quick(T arr[], int size, int call) {
		if (size <= 1) return 0;
		if (call > 1000 || size < 5000) {
			return sort::insertion(arr, size);
		}
		clock_t ts = clock();
		int pivot = arr[size - 1];
		int wall = -1;
		for (int i = 0; i < size; i++)
		{
			if (arr[i] <= pivot) {
				sort::Swap(arr[++wall], arr[i]);
			}
		}
		sort::quick(arr, wall, call + 1);
		sort::quick(arr + wall + 1, size - wall - 1, call + 1);

		clock_t te = clock();
		return ((float)(te - ts)) / (float)CLOCKS_PER_SEC;
	}
};

void printArray(int arr[], int size) {
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;
}

int main()
{
    int arr[SIZE];
	float (*x)(char* s, int a);
	float* r;



	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = rand() % 40;
	}
	std::cout << "Bubble sort:" << std::endl;
	printArray(arr, SIZE);
	sort::bubble(arr, SIZE);
	printArray(arr, SIZE);
	x = sort::bubble;
	r = sort::test(x);
	for (int i = 0; i < 10; i++)
	{
		std::cout << r[i] << "s, ";
	}
	delete[] r;


	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = rand() % 40;
	}
	std::cout << "\n\nInsertion sort:" << std::endl;
	printArray(arr, SIZE);
	sort::insertion(arr, SIZE);
	printArray(arr, SIZE);
	x = sort::insertion;
	r = sort::test(x);
	for (int i = 0; i < 10; i++)
	{
		std::cout << r[i] << "s, ";
	}
	delete[] r;


	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = rand() % 40;
	}
	std::cout << "\n\nCocktail shaker sort:" << std::endl;
	printArray(arr, SIZE);
	sort::cocktail_shaker(arr, SIZE);
	printArray(arr, SIZE);
	x = sort::cocktail_shaker;
	r = sort::test(x);
	for (int i = 0; i < 10; i++)
	{
		std::cout << r[i] << "s, ";
	}
	delete[] r;


	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = rand() % 40;
	}
	std::cout << "\n\nQuick sort:" << std::endl;
	printArray(arr, SIZE);
	sort::quick(arr, SIZE);
	printArray(arr, SIZE);
	x = sort::quick;
	r = sort::test(x);
	for (int i = 0; i < 10; i++)
	{
		std::cout << r[i] << "s, ";
	}
	delete[] r;






	int arrbogo[10];
	for (int i = 0; i < 10; i++)
	{
		arrbogo[i] = rand() % 40;
	}
	std::cout << "\n\nBogo sort:" << std::endl;
	printArray(arrbogo, 10);
	std::cout << "Time taken: " << sort::bogo(arrbogo, 10) << std::endl;
	printArray(arrbogo, 10);
}
