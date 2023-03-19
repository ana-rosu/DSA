#include <bits/stdc++.h>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <chrono>
using namespace std;
using namespace chrono;

int arr[100000001], numere[100000001], fr[100000001];

ifstream f("file.in");

// RADIX SORT 
void radixSort(int arr[], int n, int base){
  //gasim maximul = nr cu cele mai multe cifre din array
	int m = arr[0];
	for(int i = 1; i < n; i++)
		if(arr[i] > m) 
			m = arr[i];

	int aux[n], exp = 1;
	while(m){
    int nr[base] = {0};
		//la prima iteratie stim cate nr au ultima cifra i, la a 2 a iteratie cate au penultima cifra i etc.
		for(int i = 0; i < n; i++)
			nr[ (arr[i]/exp)%base ]++;
    
		//counter personalizat - calculam pe ce pozitii sa punem elementele care se termina (in cazul primei iteratii) in i, stiind cate s-au terminat in i-1
		for(int i = 1; i < base; i++)
			nr[i] += nr[i-1];

    //formez aux "partial sortat"
		for(int i = n - 1; i >=0; i--){
			aux[ nr[(arr[i]/exp)%base] - 1 ] = arr[i];
			nr[(arr[i]/exp)%base]--;
		}

    for(int i = 0; i < n; i++)
      arr[i] = aux[i];

		m/=exp;
		exp*=base;
	}
}

// SHELL SORT 
void shellSort(int arr[], int n){
  for (int p = n/2; p >= 1; p /= 2)
    for (int i = p; i < n; i += 1){
      int aux = arr[i];
      int j;
      for (j = i; j >= p && arr[j - p] > aux; j -= p)
          arr[j] = arr[j - p];
      arr[j] = aux;
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
// Quicksort cu pivot ultimul element
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
void quickSort(int arr[], int left, int right)
{
	if (left < right) {
		int p = partitie(arr, left, right);

		quickSort(arr, left, p - 1);
		quickSort(arr, p + 1, right);
	}
}
// Quicksort cu pivot random
int partitiePivotRandom(int arr[], int left, int right){
  srand ( time(NULL) );
  int randomIndex = left + rand() % (right-left+1);
	swap(arr[randomIndex], arr[right]);
	return partitie(arr, left, right);
}
void quickSortR(int arr[], int left, int right)
{
	if (left < right) {
		int p = partitiePivotRandom(arr, left, right);

		quickSortR(arr, left, p - 1);
		quickSortR(arr, p + 1, right);
	}
}


// COUNTING SORT
void countingSort(int arr[], int n){
	long aux[n], cnt=0, maxi=-1, mini=99999999;
	for(int i = 0; i < n; i++){
		fr[arr[i]]++;
		if(arr[i] > maxi) maxi = arr[i];
		if(arr[i] < mini) mini = arr[i];
	}
	for(int i = mini; i<= maxi; i++)
		while(fr[i]!=0){
			aux[cnt++] = i;
			fr[i]--;
		}
	for(int i = 0; i < n; i++)
		arr[i] = aux[i];
}

// Generare numere
void random(int arr[], int n, int m){
	srand(time(NULL));
	for(int i = 0; i < n; i++){
		arr[i] = rand() % m;
	}
}
void sorted(int arr[], int n){
	for(int i = 0 ; i < n; i++)
		arr[i] = i;
}
void reverse(int arr[], int n){
	for(int i = n; i >= 0; i--)
		arr[i] = n-i;
}
void constant(int arr[], int n){
	for(int i = 0 ; i < n; i++)
		arr[i] = 1;
}
// Copia unui array
void copie(int arr1[], int arr2[], int n){
	for(int i=0; i < n; i++)
		arr1[i] = arr2[i];
}
// Afisare array
void afisare(int arr[], int n){
	for(int i = 0; i < n; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}
// Testare sortari
bool testSort(int arr[], int n){
	int aux[n];
	copie(aux, numere, n);
	sort(aux, aux+n);
  for(int i=0; i<n; i++)
    if(arr[i] != aux[i])
      return false;
  return true;
}


// Testare tip de input
void testare(int n){
	cout<<"Timpii de sortare folosind: \n";

	copie(arr, numere, n);
	auto start = high_resolution_clock::now();
	sort(arr, arr+n);
	auto end = high_resolution_clock::now();
	duration<double> total_seconds = end - start;
	cout<<"Algoritmului de sortare nativ C++: "<<total_seconds.count()<<" secunde "<<endl;

	copie(arr, numere, n);
	start = high_resolution_clock::now();
	radixSort(arr, n, 10);
	end = high_resolution_clock::now();
	total_seconds = end - start;
	cout<<"Radix Sort baza 10: "<<total_seconds.count()<<" secunde ";
	testSort(arr, n) ? cout<<"OK"<<endl : cout<<"FAIL"<<endl;

	copie(arr, numere, n);
	start = high_resolution_clock::now();
	radixSort(arr, n, 1024);
	end = high_resolution_clock::now();
	total_seconds = end - start;
	cout<<"Radix Sort baza 2**16: "<<total_seconds.count()<<" secunde ";
	testSort(arr, n) ? cout<<"OK"<<endl : cout<<"FAIL"<<endl;

	copie(arr, numere, n);
	start = high_resolution_clock::now();
	mergeSort(arr, 0, n-1);
	end = high_resolution_clock::now();
	total_seconds = end - start;
	cout<<"Merge Sort: "<<total_seconds.count()<<" secunde ";
	testSort(arr, n) ? cout<<"OK"<<endl : cout<<"FAIL"<<endl;

	copie(arr, numere, n);
	start = high_resolution_clock::now();
	shellSort(arr, n);
	end = high_resolution_clock::now();
	total_seconds = end - start;
	cout<<"Shell Sort: "<<total_seconds.count()<<" secunde ";
	testSort(arr, n) ? cout<<"OK"<<endl : cout<<"FAIL"<<endl;

	copie(arr, numere, n);
	start = high_resolution_clock::now();
	quickSortR(arr, 0, n-1);
	end = high_resolution_clock::now();
	total_seconds = end - start;
	cout<<"Quick Sort cu pivot random: "<<total_seconds.count()<<" secunde ";
	testSort(arr, n) ? cout<<"OK"<<endl : cout<<"FAIL"<<endl;

	copie(arr, numere, n);
	start = high_resolution_clock::now();
	quickSort(arr, 0, n-1);
	end = high_resolution_clock::now();
	total_seconds = end - start;
	cout<<"Quick Sort cu pivot ultimul element: "<<total_seconds.count()<<" secunde ";
	testSort(arr, n) ? cout<<"OK"<<endl : cout<<"FAIL"<<endl;

	copie(arr, numere, n);
	start = high_resolution_clock::now();
	countingSort(arr, n);
	end = high_resolution_clock::now();
	total_seconds = end - start;
	cout<<"Counting sort: "<<total_seconds.count()<<" secunde ";
	testSort(arr, n) ? cout<<"OK"<<endl : cout<<"FAIL"<<endl;

}
int main(){
	int teste, n, m;
	f>>teste;
	for(int test = 0; test < teste; test++){
		cout<<"--------------------------------------------------\n";
		cout<<"TEST "<<test+1<<endl;
		f>>n>>m;
		cout<<n<<" numere cuprinse intre 1 si "<<m<<"\n";

		cout<<endl;
		cout<<"Test "<<test+1<<".1: numere random\n";
		random(numere, n, m);
		testare(n);

		cout<<endl;

		cout<<"Test "<<test+1<<".2: numere sortate\n";
		sorted(numere, n);
		testare(n);

		cout<<endl;

		cout<<"Test "<<test+1<<".3: numere sortate invers\n";
		reverse(numere, n);
		testare(n);
		
		cout<<endl;

		cout<<"Test "<<test+1<<".4: numerele identice\n";
		constant(numere, n);
		testare(n);
	cout<<"--------------------------------------------------\n\n";

	}
  return 0;
}