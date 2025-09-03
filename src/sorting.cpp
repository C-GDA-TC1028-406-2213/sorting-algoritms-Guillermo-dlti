#include "sorting.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace SortingAlgorithms
{

    void bubbleSort(int arr[], int n)
    {
        for (int j = 0; j < n - 1; j++)
        {
            for (int i = 0; i < n - 1 - j; i++)
            {
                if (arr[i] > arr[i + 1])
                {
                    swap(&arr[i], &arr[i + 1]);
                }
            }
        }
    }

    void selectionSort(int arr[], int n)
    {
        for (int p = 0; p < n - 1; p++)
        {
            int max = arr[0];
            int positionMax = 0;
            for (int i = 1; i < n - p; i++)
            {
                if (arr[i] > max)
                {
                    max = arr[i];
                    positionMax = i;
                }
            }
            swap(&arr[n - p - 1], &arr[positionMax]);
        }
    }

    void insertionSort(int arr[], int n)
    {
        for (int i = 1; i < n; i++)
        {
            int firstVal = arr[i];
            int m = i - 1;
            while (m >= 0 && arr[m] > firstVal)
            {
                arr[m + 1] = arr[m];
                m--;
            }
            arr[m + 1] = firstVal;
        }
    }

    void merge(int arr[], int left, int mid, int right)
    {
        int n = right - left + 1;
        int *result = new int[n];

        int l = left;
        int r = mid + 1;
        int idx = 0;

        while (l <= mid && r <= right)
        {
            if (arr[l] < arr[r])
            {
                result[idx++] = arr[l++];
            }
            else
            {
                result[idx++] = arr[r++];
            }
        }
        while (l <= mid)
        {
            result[idx++] = arr[l++];
        }
        while (r <= right)
        {
            result[idx++] = arr[r++];
        }

        for (int t = 0; t < n; ++t)
        {
            arr[left + t] = result[t];
        }

        delete[] result;
    }

    void mergeSort(int arr[], int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);

        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }

    void swap(int *x, int *y)
    {
        int temp = *x;
        *x = *y;
        *y = temp;
    }

    int partition(int arr[], int low, int high)
    {
        int pivot = arr[low];
        int i = low + 1;
        int j = high;

        while (true)
        {
            while (i <= j && arr[i] <= pivot)
            {
                i++;
            }
            while (arr[j] >= pivot && j >= i)
            {
                j--;
            }
            if (j < i)
            {
                break;
            }
            else
            {
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[low], &arr[j]);
        return j;
    }

    void quickSort(int arr[], int low, int high)
    {
        if (low < high)
        {
            int p = partition(arr, low, high);
            quickSort(arr, low, p - 1);
            quickSort(arr, p + 1, high);
        }
    }

    void heapify(int arr[], int n, int i)
    {
    }

    void heapSort(int arr[], int n)
    {
    }

    void printArray(int arr[], int n)
    {
        if (n == 0)
        {
            std::cout << "[]" << std::endl;
            return;
        }

        std::cout << "[";
        for (int i = 0; i < n; i++)
        {
            std::cout << arr[i];
            if (i < n - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    void copyArray(int source[], int dest[], int n)
    {
        for (int i = 0; i < n; i++)
        {
            dest[i] = source[i];
        }
    }

    bool isSorted(int arr[], int n)
    {
        for (int i = 1; i < n; i++)
        {
            if (arr[i] < arr[i - 1])
            {
                return false;
            }
        }
        return true;
    }

    void SortingTimer::start()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void SortingTimer::stop()
    {
        end_time = std::chrono::high_resolution_clock::now();
    }

    double SortingTimer::getElapsedMilliseconds() const
    {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return duration.count() / 1000.0;
    }

    std::string SortingTimer::getElapsedTime() const
    {
        double ms = getElapsedMilliseconds();
        std::stringstream ss;

        if (ms < 1.0)
        {
            ss << std::fixed << std::setprecision(3) << (ms * 1000) << " microseconds";
        }
        else if (ms < 1000.0)
        {
            ss << std::fixed << std::setprecision(3) << ms << " ms";
        }
        else
        {
            ss << std::fixed << std::setprecision(3) << (ms / 1000.0) << " seconds";
        }

        return ss.str();
    }

    std::vector<int> generateRandomArray(int size, int minVal, int maxVal)
    {
        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minVal, maxVal);

        for (int i = 0; i < size; i++)
        {
            arr[i] = dis(gen);
        }

        return arr;
    }

    std::vector<int> generateSortedArray(int size)
    {
        std::vector<int> arr(size);
        for (int i = 0; i < size; i++)
        {
            arr[i] = i;
        }
        return arr;
    }

    std::vector<int> generateReverseSortedArray(int size)
    {
        std::vector<int> arr(size);
        for (int i = 0; i < size; i++)
        {
            arr[i] = size - i - 1;
        }
        return arr;
    }

    std::vector<int> generateNearlySortedArray(int size, int swaps)
    {
        std::vector<int> arr = generateSortedArray(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, size - 1);

        for (int i = 0; i < swaps && i < size / 2; i++)
        {
            int idx1 = dis(gen);
            int idx2 = dis(gen);
            std::swap(arr[idx1], arr[idx2]);
        }

        return arr;
    }

}