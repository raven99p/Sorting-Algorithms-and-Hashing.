#include <fstream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>    
#include <vector>       
#include <utility>
#include <time.h>
#include <math.h>

using namespace std;
// time variables to take performance measurements
clock_t start, end;
double cpu_time_used; 

///////////////////// SORTING ///////////////////////////
vector<int> BubbleSort(vector<int> vec) //OK
{
	int i,j; 	
	int swaps=0;
                                        
	for(i=0;i<vec.size();i++)
	{
		for(j=0;j<vec.size()-1;j++)   
		{
			if(vec[j]>vec[j+1])
			swap(vec[j], vec[j+1]); 
			swaps++;
		}
	}
	
	//cout<<"swaps: "<<swaps<<endl;
	return vec;
}

vector<int> InsertionSort(vector<int> vec)
{
	int i,j,temp;
	int swaps=0;
	
	for(i=1; i<vec.size(); i++)
	{
		temp=vec[i];
		j=i-1;
		while((temp<vec[j]) && (j>=0))
		{
			vec[j+1]=vec[j];
			j=j-1;
			swaps++;
		}
		vec[j+1]=temp;
	}
	return vec;
	
}

vector<int> SelectionSort(vector<int> vec)
{
	int i,j,temp;
	int swaps=0;
	
	for(i=0; i<vec.size(); i++)
	{
		for(j=i+1; j<vec.size(); j++)
		{
			if(vec[i]>vec[j])
			{
				temp=vec[i];
				vec[i]=vec[j];
				vec[j]=temp;
				swaps++;
			}
		}
	}
	//cout<<"Swaps:"<<swaps<<endl;
	return vec;
}
 	
vector<int> QuickSort(vector<int> vec, int left, int right)
{ 
	int pivot,leftArrow,rightArrow,temp;
	leftArrow=left;
	rightArrow=right;
	pivot=vec[(left+right)/2];
	do{
		while(vec[rightArrow] > pivot)
				rightArrow--; 
		while(vec[leftArrow] < pivot)
					leftArrow++;
	
		if (vec[leftArrow] >= vec[rightArrow]){
			
			temp = vec[leftArrow];
			vec[leftArrow]=vec[rightArrow];
			vec[rightArrow]=temp;
			leftArrow++;
			rightArrow--; 
		}
	} while (rightArrow >= leftArrow);
	if (left < rightArrow)
	QuickSort(vec, left, rightArrow);
	if (leftArrow < right)
	QuickSort(vec, leftArrow, right);	
    return vec;  
} 

void merge(vector<int>& vec, int start, int mid, int end) //utility function for MergeSort
{
	// create a temp array
	int temp[end - start + 1];

	// crawlers for both intervals and for temp
	int i = start, j = mid+1, k = 0;

	// traverse both arrays and in each iteration add smaller of both elements in temp 
	while(i <= mid && j <= end) {
		if(vec[i] <= vec[j]) {
			temp[k] = vec[i];
			k += 1; i += 1;
		}
		else {
			temp[k] = vec[j];
			k += 1; j += 1;
		}
	}

	// add elements left in the first interval 
	while(i <= mid) {
		temp[k] = vec[i];
		k += 1; i += 1;
	}

	// add elements left in the second interval 
	while(j <= end) {
		temp[k] = vec[j];
		k += 1; j += 1;
	}

	// copy temp to original interval
	for(i = start; i <= end; i += 1) {
		vec[i] = temp[i - start];
	}
	// start and end are the starting and ending index of current interval of vec
}

vector<int> MergeSort(vector<int> &vec, int left, int right)
{
	
	if(left < right){
		int middle = left + (right-left)/ 2;
		MergeSort(vec, left, middle);
		MergeSort(vec, middle+1, right);
		merge(vec, left, middle, right);
	} 
	return vec;
}

void heapify(vector<int>& vec, int n, int i) //utility function for HeapSort
{
	int temp;
	int largest=i;
	int left = 2*i +1;
	int right = 2*i +2;
	
	if(left<n && vec[left] > vec[largest])
		largest=left;
	if(right < n && vec[right] > vec[largest])
		largest = right;
	if(largest != i){
		temp= vec[i];
		vec[i]=vec[largest];
		vec[largest]=temp;
		heapify(vec,n,largest);
	}
	
	
}

vector<int> HeapSort(vector<int> vec, int n)
{
	int temp;
	for(int i = n/2 - 1; i>=0; i--) //heapifying the left leg of the tree
		heapify(vec,n,i);
	for(int i = n-1; i>=0 ; i--) //heapifying the right 
	{
		temp=vec[0];
		vec[0]=vec[i];
		vec[i]=temp;
		heapify(vec,i,0);
	}
	return vec;
}


////////////////////// SEARCHING ////////////////////////////
int LinearSearch(vector<int> vec, int x) //OK
{
	int i, flag =0;
	
	start=clock(); //beginning of time counting
	
	for(i=0;i<vec.size();i++){
		//cout<<i<<endl;
		if(x==vec[i]){
			flag=1;
			break;
		}
	}
	if(flag==1) 	cout<<x<<" was found at "<<" vec["<<i<<"]"<<endl;
	else if(flag==0)	cout<<x<<" was not found in the vector"<<endl;
	
}
int BinarySearch(vector<int> vec, int x)
{ 
	int bottom=0;
	int top = (vec.size() - 1);
	int middle;

	start=clock(); //beginning of time counting
	
    while (bottom <= top)
	{
		
    	middle = (top + bottom) / 2;
    	if (vec[middle] == x)
		{
		cout<<x<<" was found at "<<"vec["<<middle<<"]"<<endl;
		break;
		}
		
	/*	cout<<"Middle is "<<middle<<endl;
		cout<<"bottom is "<<bottom<<endl;
		cout<<"top is "<<top<<endl;  */ //testing cout
    
    	if (vec[middle] > x)
		{
			top = middle - 1;
		} 
    
    	else bottom = middle + 1; 
	}
    /* We reach here when element is not 
    /  present in array */
    if(bottom > top)
    cout<<"The element was not found in the vector";
    return -1; 
}

int InterpolationSearch(vector<int> vec, int x)
{ 
	start=clock(); //beginning of time counting
	
    // Find indeces of two corners 
    int low = 0, high = (vec.size() - 1); 
  
    // Since array is sorted, an element present 
    // in array must be in range defined by corners
    while (low <= high && x >= vec[low] && x <= vec[high]) 
    { 
        if (low == high) 
        { 
            if (vec[low] == x) cout<<x<<" was found at"<<" vec["<<low<<"]"<<endl;
            return -1; 
        } 
        // Probing the position with keeping 
        // uniform distribution in mind. 
        int position = low + (((double)(high - low) / 
            (vec[high] - vec[low])) * (x - vec[low])); 
   
        if (vec[position] == x) // Condition of target found 
            cout<<x<<" was found at"<<"vec["<<position<<"]"<<endl; 
         
        if (vec[position] < x) // If x is larger, x is in upper part 
            low = position + 1; 
  
        else // If x is smaller, x is in the lower part 
            high = position - 1; 
    } 
    if(low < high)
    {
    	cout<<"The element was not found in the vector\n";
    	return -1; 
	}
}
int BinaryInterpolationSearch(vector<int> vec, int x)
{ 
	int flag=0;
	bool whileFlag = true;
	int left = 0;
	int right = vec.size()-1;
	int size = right - left ;
	int next = ceil(size * (double)(x - vec[left]) / (vec[right] - vec[left]) ); //typcasting to have the division working
	start=clock(); //beginning of time counting

	while ((x != vec[next] || x > vec[next]) && whileFlag)
	{
		int i=0, size = right - left ;
		
		if (size<=3) //if the size is too small, we do Linear Search
		{ 
			for(i=0;i<vec.size();i++)
			{
				if(x==vec[i])
				{
					flag=1;
					break;	
				}
			}
			if(flag==1) 
			{
				cout<<x<<" was found at "<<" vec["<<i<<"]"<<endl;
				whileFlag = false;
			}	
			else if(flag==0) 
			{
				cout<<x<<" was not found in the vector"<<endl;
				whileFlag = false;
			}	
		}		
		
		if (x >= vec[next]){ //if we are higher than x
				while(x > vec[(int)(next + i * sqrt(size) - 1)])
				{
					i++;
					right = next + i * sqrt(size);
					left = next + (i-1) * sqrt(size);
				}
			}
		else if (x < vec[next]){ //if we are lower than x
				while(x < vec[next - i * floor(sqrt(size)) + 1])
				{
					i++;
					right = next - (i - 1) * sqrt(size);
					left = next - i * sqrt(size);
				}
			}
			next = left + ( (right - left + 1) * (((x - vec[left]) )/ (vec[right] - vec[left])));
		}
		if (x == vec[next]) 
		{
			cout<<x<<" was found at "<<" vec["<<next<<"]"<<endl; //if we find x
			whileFlag = false;
		}
		else cout<<"Key not found";
}

//////// UTILITY FUNCTIONS ///////////
void printArray(int arr[], int size)
{ 
    int i; 
    for (i=0; i < size; i++) 
    cout<<arr[i]<<endl; 
}
void printVector(vector<int> vec)
{
	string yesOrNo;
	cout<<endl<<"Do you want to print the sorted vector? Y/N :";
            while(1)
			{
                cin>>yesOrNo;
                if( yesOrNo == "Y" || yesOrNo == "y" || yesOrNo == "N" || yesOrNo == "n") 
                break;
			}
            if (yesOrNo == "Y" || yesOrNo == "y")
			{
				for(int x=0;x<vec.size();x++)
   				cout<<vec[x]<<" ";
			}
	
}
static double diffclock(clock_t clock1,clock_t clock2) //function that calculates the difference between 2 clock_t instances
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

int main()
{
	ifstream myFile;                
	vector<int> new_vec;
	vector<int> vec;
	int count=0, x=0, c, i, key;
	clock_t time1, time2;
	double elapsed_time;
	bool askAgain = true;
	myFile.open("integers.txt");
	
	 if (!myFile) //if the file cannot be opened
	{ 
		cout<<"unable to open file ";
		exit(1);	
	}
	while (myFile >> x) //while we still read from the file, put the numbers in the vector
	{
        vec.push_back(x);
    }   
	myFile.close();	//close the file
	
	/////// SORTING ////////
	while(askAgain)
	{
		cout
		<<" Sort the values"<<endl
		<<" ----------------------------- "<<endl
		<<" 1. Bubble Sort"<<endl
		<<" 2. Insertion Sort"<<endl
		<<" 3. Selection Sort"<<endl
		<<" 4. Quick Sort"<<endl
		<<" 5. Merge Sort"<<endl
		<<" 6. Heap Sort"<<endl
		<<" 7. Exit sorting menu"<<endl
		<<"Choose your sorting method: ";
		cin>>c;
	
		switch(c){
	
			case 1 : { 	
						time1 = clock();
						
						new_vec=BubbleSort(vec); 
						 
			
						time2 = clock();
						
						printVector(new_vec);	
						
						elapsed_time = diffclock(time2, time1);
						
						cout<<endl<<"The cpu time used is : "<<elapsed_time<<" milliseconds"<<endl; //needs fix of accuracy
				break;
			}	
			case 2 : {
						time1 = clock();
						
						new_vec=InsertionSort(vec); 
						
						printVector(new_vec);	 
			
						time2 = clock();
						elapsed_time = diffclock(time2, time1);
						
						cout<<endl<<"The cpu time used is : "<<elapsed_time<<" milliseconds"<<endl; //needs fix of accuracy
				break;
			}
			case 3 : {
						time1 = clock();
						
						new_vec=SelectionSort(vec);
						
						printVector(new_vec);	 
			
						time2 = clock();
						elapsed_time = diffclock(time2, time1);
						
						cout<<endl<<"The cpu time used is : "<<elapsed_time<<" milliseconds"<<endl; //needs fix of accuracy
				break;
			}
			case 4 : {
						time1 = clock();
						
						new_vec=QuickSort(vec, 0, vec.size()-1);
						
						printVector(new_vec);	 
			
						time2 = clock();
						elapsed_time = diffclock(time2, time1);
						
						cout<<endl<<"The cpu time used is : "<<elapsed_time<<" milliseconds"<<endl; //needs fix of accuracy
				break;
			}
			case 5 : {
						time1 = clock();
						
						new_vec=MergeSort(vec,0,vec.size()-1);
						
						printVector(new_vec);	 
			
						time2 = clock();
						elapsed_time = diffclock(time2, time1);
						
						cout<<endl<<"The cpu time used is : "<<elapsed_time<<" milliseconds"<<endl; //needs fix of accuracy
				break;
			}
			case 6 : {
						time1 = clock();
						
						new_vec=HeapSort(vec, vec.size());
							 
						time2 = clock();
						
						printVector(new_vec);
						
						elapsed_time = diffclock(time2, time1);
						
						cout<<endl<<"The cpu time used is : "<<elapsed_time<<" milliseconds"<<endl; //needs fix of accuracy
				break;
			}
			case 7 : askAgain = false;
		} //end of switch
	} //end of while
	
	//// SEARCHING ////
	askAgain = true;
	while(1){
		
		cout
		<<" Search for a number"<<endl
		<<" ----------------------------- "<<endl
		<<" 8.  Linear Search"<<endl
		<<" 9.  Binary Search"<<endl
		<<" 10. Interpolation Search"<<endl
		<<" 11. Binary/Interpolation Search"<<endl
		<<" 12. Exit searching menu and programm"<<endl
		<<" Choose your searching method: ";
		cin>>c;
		cout<<endl<<"Input search value: ";
		cin>>key;
		
			switch(c)
			{
				
				case 8 : {	

					LinearSearch(new_vec,key);
					end = clock();
					
					cpu_time_used = ((double)(end-start)/((CLOCKS_PER_SEC)/1000));
					cout<<endl<<"The cpu time used is : "<<elapsed_time<<" milliseconds"<<endl;
					break;
				}
				case 9 : {
					
						BinarySearch(new_vec,key);
						end=clock();
						
						cpu_time_used = ((double)(end-start)/((CLOCKS_PER_SEC)/1000));
						cout<<endl<<"The cpu time used is : "<<elapsed_time<<" milliseconds"<<endl;
					break;
				}
				case 10 : {
					
						InterpolationSearch(new_vec,key);
						end=clock();
						
						cpu_time_used = ((double)(end-start)/((CLOCKS_PER_SEC)/1000));
						cout<<endl<<"The cpu time used is : "<<elapsed_time<<" milliseconds"<<endl;
					break;
				}
				case 11 : {
					
						BinaryInterpolationSearch(new_vec,key);
						end=clock();
						
						cpu_time_used = ((double)(end-start)/((CLOCKS_PER_SEC)/1000));
						cout<<endl<<"The cpu time used is : "<<elapsed_time<<" milliseconds"<<endl;
					break;
				}
				case 12 : { askAgain = false; }
			}//end of switch
	}//end of while
	
	return 0;
}
	
