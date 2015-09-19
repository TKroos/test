#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
template <typename T>
class MaxHeap
{
public:
	// Constructor: vector as parameter
	MaxHeap(int cur_size, vector<T> data)
	{
		cur_size_ = cur_size;
		max_size_ = 2 * cur_size_;
		heap_.reserve(max_size_+1);
		heap_.assign(data.begin(), data.end());
	}
	// Constructor: array as parameter
	MaxHeap(int cur_size, T data[])
	{
		cur_size_ = cur_size;
		max_size_ = 2 * cur_size_;
		heap_.reserve(max_size_ + 1);
		heap_.assign(data, data + cur_size_);
	}
	void MaxHeapify(int i)
	{
		int l = left(i);
		int r = right(i);
		int largest = i;

		if (l <= cur_size_ - 1 && heap_[l] > heap_[largest])
			largest = l;

		if (r <= cur_size_ - 1 && heap_[r] > heap_[largest])
			largest = r;

		if (largest != i)
		{
			swap(heap_[largest], heap_[i]);
			MaxHeapify(largest);
		}
	}
	void BuildMaxHeap()
	{
		for (int i = cur_size_ / 2; i >= 0; i--)
		{
			MaxHeapify(i);
		}
	}
	// Retrieve at the largest element
	T Peek()
	{
		return heap_[0];
	}
	// Simultaneously retrieve and delete the largest element
	T Dequeue()
	{
		if (cur_size_ <= 1)
			throw logic_error("No element in max heap!");

		T max = heap_[0];
		heap_[0] = heap_[cur_size_ - 1];
		cur_size_--;
		MaxHeapify(0);

		return max;
	}
	// Insert an element
	void Insert(T key)
	{
		if (max_size_ <= cur_size_)
			throw logic_error("The heap is out of size, can't insert!");

		cur_size_++;
		heap_.push_back( T(-0xFFFF));
		int i = cur_size_ - 1;
		if (key < heap_[i])
			throw logic_error("the new key is smaller than current key!");

		heap_[i] = key;
		while (i > 0 && heap_[parent(i)] < heap_[i])
		{
			swap(heap_[parent(i)], heap_[i]);
			i = parent(i);
		}
	}
	void Output(){
		cout << heap_[0];
		for (int i = 1; i <= cur_size_ - 1; i++){
			cout << " " << heap_[i];
		}
		cout << endl;
	}
	// Report its size
	int Size(){ 
		return cur_size_;
	}

private:
	int parent(int i) { return (i + 1) / 2 - 1; }
	int left(int i)   { return (i + 1) * 2 - 1; }
	int right(int i)  { return (i + 1) * 2; }

private:
	int cur_size_;
	int max_size_;
	vector<T> heap_;
};

int main()
{
	vector<int> data;
	for (int i = 1; i <= 10; i++){
		data.push_back(i);
	}
	int count = data.size();
	/*int data[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	int count = sizeof(data) / sizeof(int);*/
	MaxHeap<int> mh(count, data); // count = the size of the array or vector, data = the array or vector to be MaxHeapified!
	cout << "Before build: ";
	mh.Output();

	cout << "Size of Max Heap: " << mh.Size() << endl;

	mh.BuildMaxHeap();
	cout << "After build: ";
	mh.Output();

	cout << "Largest element: " << mh.Peek() << endl;

	mh.Dequeue();
	cout << "After dequeue the largest element: ";
	mh.Output();
	cout << "Size of Max Heap: " << mh.Size() << endl;

	mh.Insert(26);
	cout << "After insert: ";
	mh.Output();

	cout << "Size of Max Heap: " << mh.Size() << endl;

	return getchar();
}