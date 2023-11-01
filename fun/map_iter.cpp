#include<map>
#include<iostream>
using namespace std;

int main()
{
      std::map<int, int> fm = {{1, 2}, {2, 3}, {4,5}, {6, 7}};
      std::multimap<int, int> mfm = {{1, 2}, {1,3}, {2,3}, {4,5},{4,6}};
      auto iter = fm.find(2);
      auto iter1 = --iter;
      auto iter2 = ++iter;
      iter2 = ++iter;
      cout<<iter1->first<<endl;
      cout<<iter2->first<<endl;
      cout<<(--iter == fm.end())<<endl;

      auto iter3 = mfm.find(4);
      auto iter3_begin = mfm.equal_range(4).first;
      auto iter3_end = mfm.equal_range(4).second;
      for(int i = 0;  i < mfm.count(4); i++, iter3++) {
            cout<<iter3->first<<" "<<iter3->second<<endl;
      }

      for(auto inner_iter = iter3_begin; inner_iter != iter3_end; inner_iter++) {
            cout<<inner_iter->first<<" "<<inner_iter->second<<endl;
      }
      return 0;
}