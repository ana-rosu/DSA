#include <bits/stdc++.h>
#include <fstream>
#include <time.h>
#include <chrono>
using namespace std;
using namespace chrono;

int arr[100000001];
ifstream f("file.in");
	// int a[] = {12,4,12,77,9,1,0,33,2,12};
// RADIX SORT - nu e final
void radixSort(int arr[], int n, int base){
	int m = arr[0];
	for(int i = 1; i < n; i++)
		if(arr[i] > m) 
			m = arr[i];

	int aux[n], nr[base] = {0}, exp = 1;
	while(m){
		//pentru primul pas
		//stim cate nr au ultima cifra i
		for(int i = 0; i < n; i++)
			nr[ (arr[i]/exp)%10 ]++;
		//counter personalizat - calculam pe ce pozitii sa punem elementele care se termina in i, stiind cate s-au terminat in i-1
		//(am avt 2 nr care se termina cu 0 deci pe cele care se termina in 1 le mut peste 2 pozitii)
		for(int i = 1; i < base; i++)
			nr[i] += nr[i-1];

		for(int i = n - 1; i >=0; i--){
			aux[ nr[(arr[i]/exp)%10] - 1 ] = arr[i];
			nr[(arr[i]/exp)%10]--;
		}
		for(int i = 0; i < n; i++)
			arr[i] = aux[i];
		m/=exp;
		exp*=base;
	}
}
// SHELL SORT - nu e final
void shellSort(long long arr[], long long n)
{
    for (long long p = n/2; p > 0; p /= 2)
    {
        for (int i = p; i < n; i += 1)
        {
            long long aux = arr[i];
            long long j;
            for (int j = i; j >= p && arr[j - p] > aux; j -= p)
                arr[j] = arr[j - p];
            arr[j] = aux;
        }
    }
}
// MERGE SORT
void merge(int arr[], int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int arr1[n1], arr2[n2];

	for (int i = 0; i < n1; i++)
		arr1[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		arr2[j] = arr[mid + 1 + j];

	int index1 = 0, index2 = 0; 
	int index3 = left; 

	while (index1 < n1 && index2 < n2) {
		if (arr1[index1] <= arr2[index2]) 
			arr[index3] = arr1[index1++];
		else 
			arr[index3] = arr2[index2++];
		index3++;
	}

	while (index1 < n1) {
		arr[index3] = arr1[index1++];
		index3++;
	}
	while (index2 < n2) {
		arr[index3] = arr2[index2++];
		index3++;
	}
}
void mergeSort(int arr[], int left, int right){
	if (left < right){ 
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}
// QUICK SORT
// Folosesc partitionarea Lomuto
int partitie(int arr[], int left, int right){
    int pivot = arr[right];
    int i = left;
 
    for (int j = left; j <= right - 1; j++)
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    
    swap(arr[i], arr[right]);
    return i; 
}
int partitiePivotRandom(int arr[], int left, int right){
  srand ( time(NULL) );
  int randomIndex = left + rand() % (right-left+1);
	swap(arr[randomIndex], arr[right]);
	return partitie(arr, left, right);
}
void quickSort(int arr[], int left, int right)
{
	if (left < right) {
		int p = partitiePivotRandom(arr, left, right);

		quickSort(arr, left, p - 1);
		quickSort(arr, p + 1, right);
	}
}
// COUNTING SORT - nu e final
void countingSort(int arr[], int n){
	long long fr[1000000] = {0}, aux[n], cnt=0, maxi=-1, mini=9999999999;
	for(int i = 0; i < n; i++){
		fr[arr[i]]++;
		if(arr[i] > maxi) maxi = arr[i];
		if(arr[i] < mini) mini = arr[i];
	}
	for(int i = mini; i< maxi; i++)
		while(fr[arr[i]]!=0){
			aux[cnt++] = i;
			fr[arr[i]]--;
		}
	for(int i = 0; i < n; i++)
		arr[i] = aux[i];
}
// HEAP SORT - nu e final
void heapify(int arr[], int N, int i){
    // Initialize largest as root
    int largest = i;
  
    // left = 2*i + 1
    int l = 2 * i + 1;
  
    // right = 2*i + 2
    int r = 2 * i + 2;
  
    // If left child is larger than root
    if (l < N && arr[l] > arr[largest])
        largest = l;
  
    // If right child is larger than largest
    // so far
    if (r < N && arr[r] > arr[largest])
        largest = r;
  
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
  
        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
    }
}
void heapSort(int arr[], int N){
    // Build heap (rearrange array)
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);
  
    // One by one extract an element
    // from heap
    for (int i = N - 1; i > 0; i--) {
  
        // Move current root to end
        swap(arr[0], arr[i]);
  
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
// BUBBLE SORT
void bubbleSort(int arr[], int n){
  bool swapped;
  for(int i=0; i < n - 1; ++i){
    swapped = false;
    for(int j=0; j < n - i - 1; ++j)
      if(arr[j]>arr[j+1]){
        swap(arr[j], arr[j+1]);
        swapped = true;
    }
    if(swapped==false)
      break;
  }
}
// INSERTION SORT
void insertionSort(int arr[], int n)
{ int j, aux;
	for (int i = 1; i < n; i++)
	{ aux = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > aux)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = aux;
	}
}
// SELECTION SORT
void selectionSort(int arr[], int n)
{
	int  min_idx;
	for (int i = 0; i < n-1; i++)
	{
		min_idx = i;
		for (int j = i+1; j < n; j++)
		{
		if (arr[j] < arr[min_idx])
			min_idx = j;
		}
		if (min_idx!=i)
			swap(arr[min_idx], arr[i]);
	}
}

// Generare numere
void random(int arr[], int n, int m){
	srand(time(NULL));
	for(int i = 0; i < n; i++){
		arr[i] = rand() % m;
	}
}
void sorted(int arr[], int n, int m){
	for(int i = 0 ; i < n; i++)
		arr[i] = i;
}
void reverse(int arr[], int n, int m){
	for(int i = m; i >= 0; i--)
		arr[i] = i;
}

// Testare sortari
bool testSort(int arr[], int n){
  if(n==0 || n == 1)
    return true;
  for(int i=1; i<n; i++)
    if(arr[i-1] > arr[i])
      return false;
  return true;
}

int main(){
	int a[] = {12,4,12,77,9,1,0,33,2,12};
	radixSort(a, 10, 10);
	for(int i = 0; i < 10; i++)
		cout<<a[i]<<" ";
	// int teste, n, m;
	// f>>teste;
	// for(int test = 0; test < teste; test++){
	// 	cout<<"--------------------------------------------------\n";
	// 	cout<<"TEST "<<test+1<<endl;
	// 	f>>n>>m;
	// 	cout<<n<<" numere cuprinse intre 1 si "<<m<<"\n";

	// 	cout<<"Test"<<test+1<<".1: numere random\n";
	// 	cout<<"Timpii de sortare folosind: \n";
	// 	random(arr, n, m);
	// 	auto start = high_resolution_clock::now();
	// 	quickSort(arr, 0, n-1);
	//   auto end = high_resolution_clock::now();
	// 	duration<double> total_seconds = end - start;
	// 	cout<<"Quick Sort: "<<total_seconds.count()<<" secunde ";
	//   if(testSort(arr, n))
	// 		cout<<"OK"<<endl;
	// 	else
	// 		cout<<"FAIL"<<endl;


	// 	random(arr, n, m);
	// 	start = high_resolution_clock::now();
	// 	mergeSort(arr, 0, n-1);
	//   end = high_resolution_clock::now();
	// 	total_seconds = end - start;
	// 	cout<<"Merge Sort: "<<total_seconds.count()<<" secunde ";
	//   if(testSort(arr, n))
	// 		cout<<"OK"<<endl;
	// 	else
	// 		cout<<"FAIL"<<endl;

	// 	random(arr, n, m);
	// 	start = high_resolution_clock::now();
	// 	mergeSort(arr, 0, n-1);
	//   end = high_resolution_clock::now();
	// 	total_seconds = end - start;
	// 	cout<<"Shell Sort: "<<total_seconds.count()<<" secunde ";
	//   if(testSort(arr, n))
	// 		cout<<"OK"<<endl;
	// 	else
	// 		cout<<"FAIL"<<endl;
	// 	cout<<"--------------------------------------------------\n\n";

	// }
  return 0;
}