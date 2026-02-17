#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std; 

void bubbleSort(vector<int> &arr, long long& passes, long long& comparisons, long long& shifts){
    int n = arr.size();
    for (int i = 0; i < n-1; i++){
        passes++;
        for (int j = 0; j < n-i-1; j++){
            comparisons++;
            if (arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                shifts++;
            }
        }
    }
}

void processArray(vector<int> arr, char type, int arrayNum, ofstream &fout, long long &sumPass, long long &sumCom, long long &sumShifts,int  batchCount){
        long long passes = 0;
        long long comparisons = 0;
        long long shifts = 0;

        bubbleSort(arr, passes, comparisons, shifts);  //array sorted

        fout << arrayNum << "," << type << "," << arr.size() << "," << 
                passes << "," << comparisons << "," << shifts << endl;

        sumPass += passes;
        sumCom += comparisons;
        sumShifts += shifts;
        batchCount++;

        if (batchCount == 10){
            fout << "AVG,AVG,-,"<< 
                    (double)sumPass/10 << "," <<
                    (double)sumCom/10 << "," << (double)sumShifts/10 << "\n";

            batchCount = 0;
            sumPass =  0;
            sumCom = 0;
            sumShifts = 0;
        }
}

int main(){
    ifstream fin("arrays.csv");
    ofstream fout("bubble_results.csv");

    if (!fin || !fout){
        cout << "file error :/";
        return 0;
    }

    fout << "Array_No,Type,Size,Passes,Comparisons,Shifts\n";   //headers add kiye hai

    int arrayNum =  1;
    int batchCount = 0;

    long long sumPass = 0;
    long long sumCom = 0;
    long long sumShifts = 0;

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

        processArray(arr, type, arrayNum, fout, sumPass, sumCom, sumShifts, batchCount);
        
        arrayNum++;
    }

    fin.close();
    fout.close();
    cout<< "Bubble sort completed :)";

    return 0;

}