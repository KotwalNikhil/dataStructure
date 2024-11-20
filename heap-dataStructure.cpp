#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

void run() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin); //file input.txt is opened in reading mode i.e "r"
	freopen("output.txt","w",stdout);  //file output.txt is opened in writing mode i.e "w"
	#endif
}

class Heap {

public:
	Heap(int N) {
		capacity = N;
		size = 0;
		arr.reserve(N);
	}

	void insert(int val);

	// This makes the index as int_max and then it comes to top and then we pop which internally calls heapify.
	void deleteKey(int index);

	int pop(); // this always pops the max element in a max heap

	void heapify(int index);


	int parent(int index) {
		return (index - 1)/2;
	}

	void printu(){
		for(int i=0;i<size;i++){cout<<arr[i]<<" ";}
			cout<<endl;
	}

private:
	vector<int>arr;
	int size;
	int capacity;
};

void Heap::insert(int val)
{
	if (size == capacity){
		cout<<"Overflow could not insert key\n";
		return;
	}

	int i = size++;
	arr[i] = val;

	while(i != 0 and arr[i] > arr[parent(i)]) {
		swap(arr[i], arr[parent(i)]);
		i = parent(i);
	}

}

int Heap::pop() {
	if(size == 0 ){cout<<"heap empty\n";return INT_MIN;}
	if(size == 1) {return arr[0];}

	int val = arr[0];
	arr[0] = arr[size - 1];
	size--;

	heapify(0);
	return val;
}

void Heap::heapify(int index) {
	int l = 2*index + 1;
	int h = 2*index + 2;
	int lar = index;

	if(l<size and (arr[l] > arr[index])){
		lar = l;
	}

	if(h < size and (arr[h] > arr[lar])){
		lar = h;
	}

	if(lar != index) {
		swap(arr[lar], arr[index]);
		heapify(lar);
	}

}

void Heap::deleteKey(int i) {
	arr[i] = INT_MAX;
	while(i !=0 and (arr[i] > arr[parent(i)])) {
		swap(arr[i], arr[parent(i)]);
		i = parent(i);
	}
	pop();
}

int main() {
	run();

	Heap* heap = new Heap(7);
	for(int i=0;i<7;i++){
		int x;
		cin>>x;
		heap->insert(x);
	}

	//cout<<heap->pop()<<endl;
	heap->printu();
	heap->deleteKey(2);
	cout<<heap->pop()<<endl;
	cout<<heap->pop();


	return 0;
}