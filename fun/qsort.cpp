#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

void myswap(int *a, int i, int j)
{
      int tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;
};

void printAll(int *a)
{
    for(int i = 0; i < 6; i++)
    {
    printf("%d ", a[i]);
    }
    printf("\n");
}

void myQuickSort(int *a, int left, int right)
{   
    printf("myQuickSort: left[%d], right[%d] \n", left, right);
    if( left >= right - 1)
        return;
    int l = left, r = right;
    int pivot = a[r - 1];//枢纽元选择的尾部
    printf("begin %d, right %d, pivot %d\n", left, right, pivot);
    do
    {
        while(l <= r && *(a+l) > pivot )//防止越界
            l++;
        r--;                            
        while(l <= r && *(a+r) < pivot )//防止越界
            r--;
        if(l < r)
        {
            myswap(a,l,r);
            printAll(a);
            l++;
            //r--; 这种解法错误，因为要判断l++之后的元素是否满足和pivot之间的关系。如果两个指针同时调整，可能会直接触发停止条件，由此划分的区间不准确。
        }
        else 
        {
            break;
        }
    } while( l < r );
    
    printf("partitioan left: %d, right: %d\n\n", l, r); // 有两种情况1.l == r;2.l > r
    myQuickSort(a, left, l);
    myQuickSort(a, l, right);
};

int main()
{     

      //int a[11] = {4,4,4,5,6,1,3,5,8,9,0};
      //int a[20] = {0, 16, 5, 6, 11, 7, 9, 1, 8, 4, 19, 17, 3, 18, 10, 14, 12, 15, 13, 2};
      //int a[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
      int a[6] = {3,2,1,5,6,4};
      printAll(a);
      myQuickSort(a, 0, 6);
      printf("finally\n");
      printAll(a);
      return 0;
}
