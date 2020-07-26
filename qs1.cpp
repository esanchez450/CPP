#include <iostream>
#include <vector>
#include <chrono> // used to time code
using namespace std;

/**
 * Write a function:
 *    int solution(vector<int> &A);
 * that, given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.
 * 
 * For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.
 *    Given A = [1, 2, 3], the function should return 4.
 *    Given A = [−1, −3], the function should return 1.
 * 
 * Write an efficient algorithm for the following assumptions:
 *    N is an integer within the range [1..100,000];
 *    each element of array A is an integer within the range [−1,000,000..1,000,000].
**/

void print(vector<int> &A) { // was too lazy to keep writing for loops for testing lol
    for (int i = 0; i < A.size()-1; i++) {
        cout << A.at(i) << ","; // << endl;
    }   cout << A.at(A.size()-1) << endl;
}

int partition(vector<int> &v, int s, int e) {
    int pivot = v.at(e);
    int pIndex = s;
    for ( int i = s; i < e; i++ ) {
        if ( v.at(i) <= pivot ) {
            int temp;
            temp = v.at(i);
            v.at(i) = v.at(pIndex);
            v.at(pIndex) = temp;
            pIndex++;            
        }
    }
    int temp;
    temp = v.at(e);
    v.at(e) = v.at(pIndex);
    v.at(pIndex) = temp;
    return pIndex;
}

void quicksort(vector<int> &v, int s, int e){
    if (s < e) {
        int p = partition(v, s, e);
        quicksort(v, s, (p-1));
        quicksort(v, (p+1), e);
    }
}

int solution(vector<int> &A) {
    int temp, sol, duration;

    // create new vector to modify order, in the case we do not want to modify original vector A, 
    // so that the vector can be sorted, although more resource is used
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    vector<int> B;
    for ( int i = 0; i < A.size(); i++) {
        B.push_back(A.at(i));
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "duration of copying to new vector: " << duration  << " milliseconds" << endl;

    // sort from min to max, easier to sort, not the fastest in time and efficiency
    // O(n^2) (super duper ooper sssssllllllooooooowwwwww)
    // start = chrono::steady_clock::now();
    // for (int j = 0; j < B.size(); j++) {
    //     for(int i = 0; i < B.size() - 1 - j ; i++) {
    //         if (B.at(i) > B.at(i+1)) {
    //             temp = B.at(i+1);
    //             B.at(i+1) = B.at(i);
    //             B.at(i) = temp;
    //         }
    //     }
    // }
    //  end = chrono::steady_clock::now();
    // duration = chrono::duration_cast<chrono::seconds>(end - start).count();
    // cout << "duration of sorting: " << duration  << " seconds" << endl;

    // quicksort algorithm , O(n log n) extremely quick
    start = chrono::steady_clock::now();
    quicksort(B, 0, B.size()-1);
    end = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "duration of sorting: " << duration  << " milliseconds" << endl;

    // finding the smallest positive integer (greater than 0) that does not occur in vector
    // breaks out the loop if sol is found
    start = chrono::steady_clock::now();
    sol = B.at(B.size()-1)+1;  // add 1 to the last element in the sequence
    for(int i = 0; i < B.size()-1; i++) {  // O(n) Linear Search
        if(B.at(i) < B.at(i+1) && B.at(i)+1 != B.at(i+1)) { 
            sol = B.at(i)+1; break;
        }
    }
    end = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "duration of finding smallest int not found in vector: " << duration  << " milliseconds" << endl;

    // if solution not found with negative numbers in the sequence, solution = 1
    if (sol <= 0) sol = 1;

    // not needed, just to view the modified vector B
    start = chrono::steady_clock::now();
    A.clear();
    for ( int i = 0; i < B.size(); i++) {
        A.push_back(B.at(i));
    }
    end = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "duration of repopulating vector: " << duration  << " milliseconds" << endl;

    cout << "solution int: " << sol << endl; // displays solution
    return sol;
}


int main() {
    srand(time(NULL));
    vector<int> vec;
    
    // populate vector
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) 
        vec.push_back(rand() % 2000000);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "duration of populating vectors: " << duration  << " milliseconds" << endl;

    // print(vec);     // before
    solution(vec);  // solution
    // print(vec);     // after

    /////////// test values for edge cases ///////////

    // if all numbers are positive and no solution found
    cout << endl;
    vector<int> v;
    v.push_back(3); v.push_back(1); v.push_back(2);
    print(v);
    solution(v);
    print(v);

    // if all numbers are negative and no solution found
    cout << endl;
    vector<int> v1;
    v1.push_back(-1); v1.push_back(-3);
    print(v1);
    solution(v1);
    print(v1);

    // if solution is 1
    cout << endl;
    int arr[] = {-1,7,-2,0,4,3,-3,5,2,-3};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    vector<int> v2;
    for (int i = 0; i < arrSize; i++) {
        v2.push_back(arr[i]);
    }
    // v2.push_back(-1); v2.push_back(7); v2.push_back(-2); v2.push_back(0); v2.push_back(4);
    // v2.push_back(3); v2.push_back(-3); v2.push_back(5); v2.push_back(2); v2.push_back(-3);
    print(v2);
    solution(v2);
    print(v2);

    return 0;
}