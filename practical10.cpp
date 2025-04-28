#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void findMinMaxMarks(vector<int> &marks)
{
    priority_queue<int> maxHeap(marks.begin(), marks.end());
    priority_queue<int, vector<int>, greater<int>> minHeap(marks.begin(), marks.end());
    cout << "Maximum Marks: " << maxHeap.top() << endl;
    cout << "Minimum Marks: " << minHeap.top() << endl;
}
void analyzeAlgorithm()
{
    cout << "\nAlgorithm Analysis:\n";
    cout << "1. Time Complexity:\n";
    cout << " - Building the heap: O(n)\n";
    cout << " - Finding maximum/minimum: O(1)\n";
    cout << " - Overall: O(n)\n";
    cout << "\n2. Space Complexity:\n";
    cout << " - O(n) for storing the heap\n";
    cout << "\n3. Advantages:\n";
    cout << " - Efficient for finding both maximum and minimum simultaneously\n";
    cout << " - Heap operations are efficient (logarithmic time)\n";
    cout << " - Can be extended easily for other operations like finding k-th largest /smallest\n ";
    cout<< "\n4. Disadvantages:\n";
    cout << " - Requires additional space for heap storage\n";
    cout << " - Not as efficient as linear scan for just finding min/max\n";
}
int main()
{
    vector<int> marks;
    int n, mark;

    cout << "Enter number of students: ";
    cin >> n;

    cout << "Enter marks of " << n << " students:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> mark;
        marks.push_back(mark);
    }
    cout << "\nResults:\n";
    findMinMaxMarks(marks);

    analyzeAlgorithm();

 return 0;
}