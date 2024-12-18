#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>
#include <algorithm>

typedef std::pair<int, int> edge;

constexpr int Infintiy = std::numeric_limits<int>::max();

void Dijkstra(std::vector<std::vector<edge>>& edges, int start, std::vector<int>& lenght, std::vector<int>& way);

void AddEdge(std::vector<std::vector<edge>>& edges, int start, int end, int distance);

void AddEdges(std::vector<std::vector<edge>>& edges, int start, std::initializer_list<edge> ends);

int main()
{
  std::vector<std::vector<edge>> edges;
  AddEdges(edges, 0, { {1, 7}, {2, 9}, {5, 14} });
  AddEdges(edges, 1, { {0, 7}, {2, 10}, {3, 15} });
  AddEdges(edges, 2, { {0, 9}, {1, 10}, {3, 11}, {5, 2} });
  AddEdges(edges, 3, { {1, 15}, {2, 11}, {4, 6} });
  AddEdges(edges, 4, { {3, 6}, {5, 9} });
  AddEdges(edges, 5, { {0, 14}, {2, 2}, {4, 9} });
  std::vector<int> lenght;
  std::vector<int> way;
  Dijkstra(edges, 0, lenght, way);
  for (int i = 0; i < lenght.size(); i++)
  {
    std::cout << lenght[i] << " ";
  }
  std::cout << '\n';
  for (int i = 0; i < way.size(); i++)
  {
    std::cout << way[i] << " ";
  }
}

void Dijkstra(std::vector<std::vector<edge>>& edges, int start, std::vector<int>& distances, std::vector<int>& way) {
  distances.resize(edges.size(), Infintiy);
  way.resize(edges.size(), -1);
  distances[start] = 0;
  std::vector<std::vector<int>> buckets;
  int maxLength = -1;
  for (const auto& e : edges) {
      for (const auto& v : e) {
      maxLength=std::max(maxLength, v.second);
    }
  }
  buckets.resize(maxLength * edges.size() + 1);
  buckets[0].push_back(start);
  int L = 0;
  while (L < buckets.size())
  {
    if (buckets[L].size() == 0)
    {
      ++L;
      continue;
    }
    int vertex = buckets[L].back();
    buckets[L].pop_back();
    for (const auto& e : edges[vertex]) {
      int neighbor = e.first;
      int weight = e.second;

      if (distances[vertex] + weight < distances[neighbor]) {
        distances[neighbor] = distances[vertex] + weight;
        way[neighbor] = vertex;
        buckets[distances[neighbor]].push_back(neighbor);
      }
    }
  }

}

void AddEdge(std::vector<std::vector<edge>>& edges, int start, int end, int distance) {
  if (edges.size() < (std::max(start, end) + 1))
  {
    edges.resize(std::max(start, end) + 1);
  }
  edges[start].push_back(edge(end, distance));
}

void AddEdges(std::vector<std::vector<edge>>& edges, int start, std::initializer_list<edge> ends) {
  for (auto i = ends.begin(); i < ends.end(); i++)
  {
    AddEdge(edges, start, i->first, i->second);
  }
}