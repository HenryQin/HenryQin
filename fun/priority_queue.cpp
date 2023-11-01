#include<iostream>
#include<queue>
#include<unordered_map>

using namespace std;

struct ComparePair {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    }
};

int main() 
{     
      std::unordered_map<int, int> umap = {
            {1,2},
            {2,3}
      };


      auto cmp =  [&](const std::pair<int, int>& p1, const std::pair<int, int>& p2)-> bool {
            return p1.second < p2.second;
      };
      
      std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, ComparePair> mque;
      for(auto& pair : umap) {
            mque.push(pair);
      }

      while(!mque.empty()) {
            std::cout<<mque.top().first<<" "<<mque.top().second<<endl;
            mque.pop();
      }
      return 0;
}