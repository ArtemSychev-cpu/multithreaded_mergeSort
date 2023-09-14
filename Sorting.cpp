#include <iostream>
#include <future>

#define SIZE 2000000

bool make_threads = false;

void merge(int* arr, int l, int m, int r)
{
    int nl = m - l + 1;
    int nr = r - m;

    int* left = new int[nl];
    int* right = new int[nr];


    for (int i = 0; i < nl; i++)
        left[i] = arr[l + i];

    for (int j = 0; j < nr; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0;
    int k = l;

    while (i < nl && j < nr) {

        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < nl) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < nr) {
        arr[k] = right[j];
        j++;
        k++;
    }

    delete[] left;
    delete[] right;
}

void mergeSort(int* arr, int l, int r)
{
    if (l >= r)
    {
        return;
    }

    int m = (l + r - 1) / 2;
    if (make_threads && (m - l) > 10000)
    {
        std::future<void> f = std::async(std::launch::async, [&]() {mergeSort(arr, l, m); });
        mergeSort(arr, m + 1, r);

        try
        {
            f.get();
        }
        catch (...)
        {
            std::cout << "an exception is occured..." << std::endl;
        }
    }
    else
    {
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
    }
    merge(arr, l, m, r);
}

int main()
{
    using::std::endl;
    using::std::cout;
    
    int* arr = new int[SIZE];
   
    for (long i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 500;
    }

    make_threads = true;
    cout << "multiply threads sorting for array dimension arr = " << SIZE << " elements" << endl;
    mergeSort(arr, 0, SIZE - 1);

    return 0;
}
  



   
