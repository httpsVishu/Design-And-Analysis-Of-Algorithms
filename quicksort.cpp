#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

int partition(vector<int>& arr, int left, int right, long long& comparisons, long long& swaps){
    int pivot = arr[right];
    int i = left -1;
    for (int j = left; j < right; j++){
        comparisons++;
        if (arr[j] <= pivot){
            i++;
            if (i != j){
                swap(arr[i], arr[j]);
                swaps++;
            }
        }
    }
    i++;
    if (i != right){
        swap(arr[i], arr[right]);
        swaps++;
    }
    return i;
}

void quickSort(vector<int>& arr, int left, int right, long long& comparisons, long long& swaps){
    if (left < right){
        int p = partition(arr, left, right, comparisons, swaps);
        quickSort(arr, left, p-1, comparisons, swaps);
        quickSort(arr, p+1, right, comparisons, swaps);
    }
}
void processArray(vector<int> arr, char type, int arrayNum, ofstream &fout, long long &sumCom, long long& sumSwaps, int& batchCount){
    long long comparisons = 0;
    long long swaps = 0;

    quickSort(arr, 0, arr.size()-1, comparisons, swaps);  //array sorted

    fout << arrayNum << "," << type << "," << arr.size() << "," <<
            comparisons << "," << swaps <<endl;

    sumCom += comparisons;
    sumSwaps += swaps;
    batchCount++;

    if (batchCount == 10){
        fout << "AVG,AVG,-,"<<(double)sumCom/10<<(double)sumSwaps/10 <<"\n";

        batchCount = 0;
        sumCom = 0;
        sumSwaps = 0;
    }
}

int main(){
    ifstream fin("arrays.csv");
    ofstream fout("quick_results.csv");

    if (!fin || !fout){
        cout << "file error :/";
        return 0;
    }

    fout << "Array_No,Type,Size,Comparisons,Swaps\n";

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

    cout<<"Quick sort completed :)";
    return 0;
}