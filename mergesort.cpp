#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std; 

void merge(vector<int>& arr, int left, int mid, int right, long long& comparisons){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    int i = left, j = mid +1, k = left;
    while (i <= n1 && j <= n2){
        comparisons++;
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = L[i];
        i++, k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++, k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right, long long& comparisons){
    if (left < right){
        int mid = left + (right-left)/2;
        mergeSort(arr, left, mid, comparisons);
        mergeSort(arr, mid+1, right, comparisons);
        merge(arr, left, mid, right, comparisons);
    }
}

void processArray(vector<int> arr, char type, int arrayNum, ofstream &fout, long long &sumCom, int& batchCount){
    long long comparisons = 0;

    mergeSort(arr, 0, arr.size()-1, comparisons);  //array sorted

    fout << arrayNum << "," << type << "," << arr.size() << "," <<
            comparisons << endl;

    sumCom += comparisons;
    batchCount++;

    if (batchCount == 10){
        fout << "AVG,AVG,-,"<<(double)sumCom/10 <<"\n";

        batchCount = 0;
        sumCom = 0;
    }
}

int main(){
    ifstream fin("arrays.csv");
    ofstream fout("merge_results.csv");

    if (!fin || !fout){
        cout << "file error :/";
        return 0;
    }

    fout << "Array_No,Type,Size,Comparisons\n";

    int arrayNum =  1;
    int batchCount = 0;

    long long sumCom = 0;

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

        processArray(arr, type, arrayNum, fout, sumCom, batchCount);
        arrayNum++;
    }

    fin.close();
    fout.close();

    cout<<"Merge sort completed :)";
    return 0;
}

