#include <cstdio>
#include <cstdlib>

#include "sort.h"
#include <iostream>


int ivector_length(int* v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];


  return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int** A, int n, int l, int r)
{
  int i;
  int* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n))){
		  A[i+1] = A[i];
		  i = i - 1;
      }

      A[i+1] = key;
    }
}

/*
*   TO IMPLEMENT: Improved Insertion Sort for problem 1.
*/
void insertion_sort_im(int** A, int n, int l, int r)
{
	int i;
	int* key;
	int* Akey;
	int vLength;
	int* vs[r+1];

	//Calculate the length of each vector and store them in the vs array
	for(int a = 0; a <= r; a++)
	{
		vLength = ivector_length(A[a], n);
		vs[a] = new int(vLength);
	}

	//Compare the sums in the vs array and sort both the vs and A arrays simultaneously
	for (int j = l+1; j <= r; j++)
	{
		key = vs[j];
		Akey = A[j];
		i = j - 1;

		while ((i >= l) && (*vs[i] > *key)){
			vs[i+1] = vs[i];
			A[i+1] = A[i];
			i = i - 1;
		}

		vs[i+1] = key;
		A[i+1] = Akey;
	}
}

/*
*   TO IMPLEMENT: Improved Merge Sort for problem 2.
*/

void merge(int** A, int n, int p, int q, int r)
{
	//Array of sum of vectors
	int* vs[r+1];
	for(int a = 0; a <= r; a++)
	{
		vs[a] = new int(ivector_length(A[a], n));
	}

	//Left and right sub-arrays
	int n1 = q - p + 1;
	int n2 = r - q;
	int* L[n1];
	int* vsL[n1];
	int* R[n2];
	int* vsR[n2];
	for(int i = 0; i < n1; i++)
	{
		L[i] = A[p+i];
		vsL[i] = vs[p+i];
	}
	for(int j = 0; j < n2; j++)
	{
		R[j] = A[q+1+j];
		vsR[j] = vs[q+1+j];
	}

	//Index of sub-arrays and main array
	int i = 0;
	int j = 0;
	int k = p;

	//Sort sub-arrays
	while(i < n1 && j < n2)
	{
		if(*vsL[i] <= *vsR[j])
		{
			A[k] = L[i];
			i++;
		} else
		{
			A[k] = R[j];
			j++;
		}
		k++;
	}

	//Place remaining elements in main array
	while(i < n1)
	{
		A[k] = L[i];
		i++;
		k++;
	}
	while(j < n2)
	{
		A[k] = R[j];
		j++;
		k++;
	}

	//Deallocate memory for vsL and vsR arrays
	for(int i = 0; i < n1; i++)
	{
		delete[] vsL[i];
	}
	for(int j = 0; j < n2; j++)
	{
		delete[] vsR[j];
	}
}
void merge_sort(int** A, int n, int p, int r)
{
	if(p < r)
	{
		int m = (p + r) / 2;
		merge_sort(A, n, p, m);
		merge_sort(A, n, m+1, r);
		merge(A, n, p, m, r);
	}
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}

