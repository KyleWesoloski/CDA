#include <iostream>

using namespace std;

template <class type>
class CDA {
public:
	int size = 0;
	int capacity = 1;
	bool isSorted;
	int front = 0;
	int end = 0;
	type* arr;
	type error; 
	CDA() {
		isSorted = false;
		capacity = 1;
		arr = new type[capacity];
	}

	CDA(int s) {
		isSorted = false;
		capacity = s;
		size = s;
		arr = new type[capacity];
	}

	CDA(CDA& obj) {
		deepCopy(obj);
	}

	~CDA() {
		delete[] arr;
	}

	type& operator[](int i) {
		if (i > size-1) {
			cout << ("Error, index out of bounds.") << endl;
			
			return error; 
		}
		return arr[abs((i + front) % capacity)];
	}

	CDA& operator=(const CDA& src) {
		if (this != &src) {
			delete[] arr;
			deepCopy(src);
		}
		return *this;
	}

	void deepCopy(const CDA& src) {
		arr = new type[src.capacity];
		size = src.size;
		capacity = src.capacity;
		front = src.front; 
		for (int i = 0; i < size; i++) arr[abs((i+front)%capacity)] = src.arr[abs((i + front) % capacity)];
	
	}

	void AddEnd(type v) {
	
		 if (capacity == size) {	
			type* tempArr = new type[capacity*2];
			
			for (int i = 0; i < size; i++) { tempArr[i] = arr[abs((i + front) % capacity)]; }
			delete[] arr;
			capacity = 2 * capacity;
			arr = new type[capacity];
			for (int i = 0; i < size; i++)  {arr[i] = tempArr[i]; }
			delete[] tempArr; 

			
			front = 0; 
			arr[abs((front+size)%capacity)] = v;
			
			
		}
		else 
		{
			arr[abs((front+size) % capacity)] = v;
			
			//end = end +1;
		
		}
	
		if(isSorted && size>1){if(arr[abs((front+size)%capacity)]<arr[abs((front+size-1)%capacity)]) { isSorted = false;}}
		else if(size == 1) isSorted = true; 
		
			size++;
	}
	
	void AddFront(type v) {
		if (capacity == size) {
			type* tempArr = new type[capacity *2];
			
			for (int i = 0; i < size; i++) { tempArr[i] = arr[abs((i + front) % capacity)]; }
			delete[] arr;
			capacity = 2 * capacity;
			arr = new type[capacity];
			for (int i = 0; i < size; i++) { arr[i+1] = tempArr[i]; }
			
			end = size;
			front = 0;
			arr[0] = v; 
		}
		else{
		if(size == 0) front = 0; 
		else front = front - 1;
	    if (front < 0) front = capacity+front;  
		arr[abs(front%capacity)] = v;
		
		}
		if(isSorted && size>1){  if(arr[abs(front%capacity)]>arr[(abs(front+1)%capacity)]) isSorted = false; }
		else if(size == 1) isSorted = true; 
		
		size++;
	}
	
	void DelEnd() { 
		if(size>0){
		end = end - 1; 
		if(end < 0) end = capacity-1;
		size = size - 1; 
		shrinkArray(); 
		}
		if(isSorted && size>1) {if(arr[(front+size)%capacity]<arr[(abs(front+size-1)%capacity)]) isSorted = false; }
		else if(size == 1) isSorted = true; 
	}

	 void DelFront() { 
		if(size>0){
		front = front + 1; 
		size = size - 1; 
		shrinkArray(); 
		}
		if(isSorted && size>1) {if(arr[front%capacity]>arr[abs((front+1)%capacity)]) isSorted = false; }
		else if(size == 1) isSorted = true; 
	}
	
	void shrinkArray(){
	if (double(size) / double(capacity) <= .25 && capacity > 1) {
			type* tempArr = new type[capacity/2];
			for (int i = 0; i < size; i++) tempArr[i] = arr[abs((i+front) % capacity)];
			capacity = capacity/2;
			delete[] arr;
			arr = new type[capacity];
			for (int i = 0; i < size; i++) arr[i] = tempArr[i];
			end = size;
			front = 0;
			delete[] tempArr;
		}
	}
	
	int Length(){
		return size; 
	}
	
	int Capacity(){
		return capacity; 
	}
	
	void Clear(){
		delete[] arr; 
		capacity = 1; 
		size = 0; 
		arr = new type[capacity]; 
		front = 0; 
		end = front = 0; 	
	}
	
	bool Ordered(){
		return isSorted; 
	}
	
	int SetOrdered(){
	//	if(isSorted) return 1; 
		for (int i = 0; i < size-1; i++)  {if(arr[abs((i+front) % capacity)] > arr[abs((i+1+front) % capacity)]) { return -1; }}
		isSorted = true; 
		return 1; 
	}
	
	type Select(int k){
		if(isSorted) {
			if(k>size-1) return arr[end]; 
			return arr[abs((front+k-1)%capacity)];
		}

		type* tempArr = new type[capacity]; 
		for (int i = 0; i < size; i++) tempArr[i] = arr[abs((i+front) % capacity)];
		if(k>size-1) {
		type max = tempArr[0]; 
		for(int i = 1; i < size; i++) if(tempArr[i]> max) max = tempArr[i]; 
		return max; 
		}
		
		type x = quickSelect(tempArr, 0, size-1, k-1); 
		delete[] tempArr; 
		return x; 
	}
	
	type quickSelect(type* tempArr, int left, int right, int k){
		
		 if(left == right) return tempArr[left]; 
		 int pivot = partition(tempArr, left, right);
		 if (k == pivot) return tempArr[pivot];
		 if (k < pivot) return quickSelect(tempArr, left, pivot-1, k);
		 else return quickSelect(tempArr, pivot+1, right, k);
}
	 

int partition(type* tempArr, int l, int r) 
{ 	
    int p = l+ rand() % (r-l+1);
    type pivot = tempArr[p]; 
	swap(tempArr[p], tempArr[r]); 
	int piv = l; 
    for (int i = l; i < r; i++) { 
        if (tempArr[i] <= pivot) { 
            swap(tempArr[i], tempArr[piv]); 
			piv++;    
        } 
    } 
   swap(tempArr[piv], tempArr[r]); 
    return (piv); 
} 

void InsertionSort(){
	int k;
	type j; 
	type* temp = new type[capacity]; 
	for(int i = 0; i < size; i++) temp[i] = arr[abs((i+front)%capacity)]; 
	
	for(int i = 0; i <= size-1; i++){
		j = temp[i]; 
		k = i - 1; 
		while(k>= 0 && temp[k] >j){
			temp[k+1] = temp[k]; 
			k--; 
		}
	temp[k+1] = j; 
	
}
	delete[] arr; 
	arr = new type[capacity]; 
	for(int i = 0; i < size; i++) arr[i] = temp[i]; 
	front = 0;  
	isSorted = true; 
}


void QuickSort(){
	quickSortRecursion(0, size-1); 
	isSorted = true; 
//	front = 0; 
}

void quickSortRecursion(int low, int high){
	
	if(low <= high){
		int pivot = partitionQuickSort(low, high); 
		quickSortRecursion(low, pivot-1);
		quickSortRecursion(pivot+1, high); 
	}	
}

int partitionQuickSort(int l, int r) 
{ 	
	int mid = (l+r)/2; 
	
	if((arr[abs((l+front)%capacity)]>=arr[abs((mid+front)%capacity)] 
	&& arr[abs((l+front)%capacity)]<=arr[abs((r+front)%capacity)])||
	(arr[abs((l+front)%capacity)]<=arr[abs((mid+front)%capacity)] 
	&& arr[abs((l+front)%capacity)]>=arr[abs((r+front)%capacity)])){ swap(arr[(abs(l+front)%capacity)],arr[abs((r+front)%capacity)]);  }
	
	else if ((arr[abs((mid+front)%capacity)]>=arr[abs((l+front)%capacity)]) 
	&& (arr[abs((mid+front)%capacity)]<=arr[abs((r+front)%capacity)])||
	((arr[abs((mid+front)%capacity)]<=arr[abs((l+front)%capacity)]) 
	&& arr[abs((mid+front)%capacity)]>=arr[abs((r+front)%capacity)])){ swap(arr[abs((mid+front)%capacity)],arr[abs((r+front)%capacity)]);  }
	
	type pivot = arr[abs((r+front)%capacity)];
	
	int j = l; 
    for (int i = l; i <r; i++) { 
        if (arr[abs((i+front)%capacity)] < pivot) { 
            swap(arr[abs((j+front)%capacity)], arr[abs((i+front)%capacity)]); 
			j++;    
        } 
    } 
    swap(arr[abs((j+front)%capacity)], arr[abs((r+front)%capacity)]); 
    return (j); 
}

void CountingSort(int m){
	int count[m+1]; 
	type sorted[size+1]; 
    
	for(int i = 0; i<= m; i++) count[i] = 0;
	for(int i = 0; i<size; i++) count[arr[abs((i+front)%capacity)]]++; 
	for(int i = 1; i<=m; i++) count[i] = count[i] + count[i-1]; 
	for(int i = size-1; i >=0; i--){
		sorted[count[arr[abs((i+front)%capacity)]]-1] = arr[abs((i+front)%capacity)]; 
		count[arr[abs((i+front)%capacity)]]--;
	}
	for(int i = 0; i < size; i++) {arr[abs((i+front)%capacity)] = sorted[i]; }
	isSorted = true; 
	
	//front = 0; 
}


int Search(type e){
	if(isSorted) return binarySearch(0, size-1, e);
	else return linearSearch(e); 
}

int binarySearch(int left, int right, type e){
	if(right-left+1>=1){
		int mid = left + (right-left)/2;
		if(e == arr[abs((mid+front)%capacity)]) return mid; 
		else if(e > arr[abs((mid+front)%capacity)]) return binarySearch(mid+1, right, e); 
		else return binarySearch(left, mid-1, e); 
	}
	else return -1; 
}

int linearSearch(type e){
	for(int i = 0; i < size; i++) if(arr[abs((i+front)%capacity)] == e) return i;
	return -1; 
}
};
