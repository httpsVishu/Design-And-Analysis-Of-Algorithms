#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std; 

void heapify(vector<int>& arr, int n, int i, long long& comparisons, long long& swaps){
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if (left < n){
        comparisons++;
        if (arr[left] > arr[largest])
            largest = left;
    }
    if (right < n){
        comparisons++;
        if (arr[right] > arr[largest])
            largest = right;
    }

    if (largest != i){
        swap(arr[i], arr[largest]);
        swaps++;
        heapify(arr, n, largest, comparisons, swaps);
    }
}

void buildMaxHeap(vector<int>& arr, int n, long long& comparisons, long long& swaps){
    for (int i = n/2-1; i>=0; i--){
        heapify(arr, n, i, comparisons, swaps);
    }
}

void heapSort(vector<int>& arr, int n, long long& comparisons, long long& swaps){
    buildMaxHeap(arr, n, comparisons, swaps);
    for (int i = n-1; i>0; i--){
        swap(arr[i], arr[0]);
        swaps++;
        heapify(arr, i, 0, comparisons, swaps);
    }
}

void processArray(vector<int> arr, char type, int arrayNum, ofstream &fout, long long &sumCom, long long &sumSwaps,int& batchCount){
        long long comparisons = 0;
        long long swaps = 0;

        heapSort(arr, arr.size(), comparisons, swaps);  //array sorted

        fout << arrayNum << "," << type << "," << arr.size() << ","
            << comparisons << "," << swaps << endl;

        sumCom += comparisons;
        sumSwaps += swaps;
        batchCount++;

        if (batchCount == 10){
            fout << "AVG,AVG,-,"<<
                    (double)sumCom/10 << "," << (double)sumSwaps/10 << "\n";

            batchCount = 0;
            sumCom = 0;
            sumSwaps = 0;
        }
}

int main(){
    ifstream fin("arrays.csv");
    ofstream fout("heap_results.csv");

    if (!fin || !fout){
        cout << "file error :/";
        return 0;
    }

    fout << "Array_No,Type,Size,Comparisons,Swaps\n";   //headers add kiye hai

    int arrayNum =  1;
    int batchCount = 0;

    long long sumCom = 0;
    long long sumSwaps = 0;

    while (true){
        vector<int> arr;
        char type; int size;
        int number;
        char comma;

        if (!(fin >> type >> comma >> size >> comma)) break;

        while (fin>>number){
            arr.push_back(number);
            if (fin.peek() == ','){
                fin.ignore();
            } else{
                break;
            }
        }

        char ch;
        while (fin.get(ch) && ch != '\n');

        processArray(arr, type, arrayNum, fout, sumCom, sumSwaps, batchCount);
        
        arrayNum++;
    }

    fin.close();
    fout.close();
    cout<< "Heap sort completed :)";

    return 0;

}