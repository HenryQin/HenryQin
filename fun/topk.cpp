#include<vector>
#include<iostream>
using namespace std;
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int begin = 0, end = nums.size() - 1;
        do
        {
            int pivot = nums[(end + begin) / 2];
            int left = begin, right = end;
            cout<<"1left "<<left<<" right "<<right<<endl;

            while(left < right)
            {   
                while(nums [left] > pivot && left < right) left++;
                while(left < right && nums[right] < pivot) right--;
                
                if(left < right)
                {
                    int tmp = nums[left];
                    nums[left] = nums[right];
                    nums[right] = tmp;
                    left++;
                    right--;
                }
            }
            cout<<"left "<<left<<" right "<<right<<endl;
            for(int i = 0; i < nums.size(); i++)
            {
                cout<<nums[i]<<" ";
            }
            cout<<endl;
            if(right < k - 1 )
            {
                begin = right+1;
            }
            else 
            {
                end = right;
            }
    
        } while(end > begin);

        for(int i = 0; i < nums.size(); i++)
        {
            cout<<nums[i]<<" ";
        }
        cout<<endl;
        printf("k-1:%d, nums[k-1]: %d\n", k-1, nums[k-1]);

        return nums[k - 1];
    }
};

int main()
{
      Solution s;
      int k = 20;
      vector<int> vec = {3,2,3,1,2,4,5,5,6,7,7,8,2,3,1,1,1,10,11,5,6,2,4,7,8,5,6};
      cout<< s.findKthLargest(vec, k)<<endl;
}