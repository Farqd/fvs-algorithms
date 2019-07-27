#include "interval.h"
#include <chrono>


using namespace std;
using namespace interval;

IntervalGraph GenerateIG(int n)
{
  vector<int> v;
  for(int i=0; i<2*n; i++)
    v.push_back(i);
  random_shuffle(v.begin(), v.end());

  IntervalGraph result;
  for(int i=0; i<n; i++)
  {
    int x = v[2*i]; int y = v[2*i+1];
    if(x > y) swap(x, y);
    result.push_back({x, y, i});
  }
  return result;
}

IntervalGraph GenerateIGSparse(int n)
{
  vector<int> v;
  for(int i=0; i<2*n; i++)
    v.push_back(i);

    for(int i=0; i < n/10; i++)
        random_shuffle(v.begin() + i*10, v.begin() + (i+1)*10);

  IntervalGraph result;
  for(int i=0; i<n; i++)
  {
    int x = v[2*i]; int y = v[2*i+1];
    if(x > y) swap(x, y);
    result.push_back({x, y, i});
  }
  return result;
}

int main()
{
    vector<int> sizes_N = {100000, 300000, 500000, 700000, 1000000, 2000000, 3000000, 4000000, 5000000};
    cout << "DENSE" << endl;
    for(const int N : sizes_N)
    {
      // const int N = 5000000;
      srand(time(0));
      auto graph = GenerateIG(N);
      // std::cout << "Edges: "  << CountEdges(graph) << endl;
      auto start = std::chrono::system_clock::now();

      auto fvs_result = Fvs(graph);
      // std::cout << "N = " << N << endl;
      // std::cout << "FVS= " << fvs_result.size() << endl;

      auto end = std::chrono::system_clock::now();
  
      std::chrono::duration<double> elapsed_seconds = end-start;
      std::time_t end_time = std::chrono::system_clock::to_time_t(end);
      std::cout << N  << " " << elapsed_seconds.count() << endl;
      // std::cout << "finished computation at " << std::ctime(&end_time)
      //           << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
}