#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

    ofstream file("arrays.csv");

    if (!file){
        cout<<"File could not be opened :/"<<endl;
        return 0;
    }

    srand(time(0));

    for (int a = 0; a < 100; a++){  //100 arrays generate karane hai
        int n = rand()%971 + 30;  //array ka  size

        vector<int> original;
        for (int i =0; i < n; i++){
            original.push_back(rand()%1000);
        }

        for (int j = 0; j < 8; j++){  // 8 shuffled
            vector<int> temp = original;
            random_shuffle(temp.begin(), temp.end());

            file << "S," << n << ",";

            for (int k = 0; k < temp.size(); k++){
                file << temp[k];
                if (k != temp.size() - 1){
                    file << ",";
                }
            }
            file << endl;
        }

        vector<int> sortedArray = original;
        sort(sortedArray.begin(), sortedArray.end());

        file << "A," << n << ",";

        for (int i = 0; i < sortedArray.size(); i++){    //ascending
            file << sortedArray[i];
            if (i != sortedArray.size() - 1){
                file << ",";
            }
        }
        file << endl;

        vector<int> descArray = sortedArray;
        reverse(descArray.begin(), descArray.end());   //descending

        file << "D," << n << ",";

        for (int i = 0; i < descArray.size(); i++) {
        file << descArray[i];
        if (i != descArray.size() - 1) {
            file << ",";
        }
}
    file << endl;
    }

    file.close();

    cout<< "1000 arrays generated successfully :)"<< endl;

    return 0;
}