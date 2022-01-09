// The MIT License (MIT)

// Copyright (c) 2021 Diego Ramírez

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "graph.cpp"
#include "heap.cpp"

#ifndef GP0_DIJKSTRA
#define GP0_DIJKSTRA

namespace gp0{
    template<typename V, typename W, typename PQ = gp0::Heap<int,W>>
    class DijkstraGraph: public gp0::SpreadGraph<V,W>{
        public:
            explicit DijkstraGraph(): gp0::Graph<V,W>(DijkstraGraph<int,W, PQ> (0)) {

            };
    };

    template <typename W, typename PQ>
    class DijkstraGraph<int,W,PQ>: public gp0::SpreadGraph<int,W>{
        private:
            std::list<int> getPath(std::vector<int> &predecesors, int destiny){
                int predecesor = predecesors[destiny];
                std::list<int> path;
                if (predecesor != -1){
                    path = getPath(predecesors, predecesor);
                }
                path.push_back(destiny);
                return path;
            }

            void discoverVertex(std::pair<int,W> currentVertex, std::vector<int> &predecesors, PQ &distances){
                if (currentVertex.second != std::numeric_limits<W>::max()){
                    std::list<std::pair<int,W>> neighbors = SpreadGraph<int,W>::edges[currentVertex.first];
                    for (std::pair<int,W> next: neighbors){
                        W nextDistance = currentVertex.second + next.second;
                        distances.decreaseKey(next.first, nextDistance);
                        if (distances.getValue(next.first) == nextDistance) predecesors[next.first] = currentVertex.first;
                    }
                }
            }

        public:
            std::pair<std::list<int>,W> shortest_path(int source, int destiny){
                PQ distances (SpreadGraph<int,W>::size());
                std::vector<int> predecesors(SpreadGraph<int,W>::size(),-1);
                distances.decreaseKey(source, 0);
                while (!distances.empty()){
                    std::pair<int,W> currentVertex = distances.getTop();
                    distances.popTop();
                    if (currentVertex.first == destiny){
                        return std::pair<std::list<int>,W> (getPath(predecesors, destiny), currentVertex.second);
                    } else {
                        discoverVertex(currentVertex, predecesors, distances);
                    }
                }
                return std::pair<std::list<int>,W> (std::list<int> (), W(0));
            }

            explicit DijkstraGraph(int n): SpreadGraph<int,W>(n){

            }
    };
}

#endif