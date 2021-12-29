#include <list>
#include <unordered_map>
#include <vector>
#ifndef GP0_GRAPH
#define GP0_GRAPH

namespace gp0
{
    template <typename VertexType, typename W>
    class Graph{
        private:
            std::unordered_map<VertexType,int> vertices_to_indices;
            std::unordered_map<int,VertexType> indices_to_vertices;
            Graph<int, W> real_graph;
        public:
            virtual unsigned long long size(){
                return real_graph.size();
            }

            virtual void addVertex(VertexType key){
                if (vertices_to_indices.end() != vertices_to_indices.find(key)) throw -1;
                else{
                    vertices_to_indices[key] = real_graph.size();
                    indices_to_vertices[real_graph.size()] = key;
                    real_graph.addVertex(0);
                }
            }

            virtual void addEdge(VertexType source, VertexType destiny, W weight){
                if (vertices_to_indices.end() == vertices_to_indices.find(source) || vertices_to_indices.end() == vertices_to_indices.find(destiny)) throw -1;
                else real_graph.addEdge(vertices_to_indices[source], vertices_to_indices[destiny], weight);
            }

            virtual W getWeight(VertexType source, VertexType destiny){
                if (vertices_to_indices.end() == vertices_to_indices.find(source) || vertices_to_indices.end() == vertices_to_indices.find(destiny)) throw -1;
                else return real_graph.getWeight(vertices_to_indices[source], vertices_to_indices[destiny]);
            }

            virtual std::pair<std::list<VertexType>,W> shortest_path(VertexType source, VertexType destiny){
                if (vertices_to_indices.end() == vertices_to_indices.find(source) || vertices_to_indices.end() == vertices_to_indices.find(destiny)) throw -1;
                std::pair<std::list<int>,W> real_path = real_graph.shortest_path(vertices_to_indices[source], vertices_to_indices[destiny]);
                std::list<VertexType> vertices_list;
                for(const int &index: real_path.first){
                    vertices_list.push_back(indices_to_vertices[index]);
                }
                return std::pair<std::list<VertexType>,W> (vertices_list, real_path.second);
            }

            explicit Graph(Graph<int, W> _real_graph): real_graph(_real_graph){

            };
    };

    template<typename W>
    class Graph<int,W>{
        public:
            virtual unsigned long long size()=0;
            virtual void addVertex(int key)=0;
            virtual void addEdge(int source, int destiny, W weight)=0;
            virtual W getWeight(int source, int destiny)=0;
            virtual std::pair<std::list<int>,W> shortest_path(int source, int destiny)=0;
    };

    template<typename VertexType, typename W>
    class SpreadGraph: public Graph<VertexType,W>{
        explicit SpreadGraph(): gp0::Graph<VertexType,W>(SpreadGraph<int,W> (0)) {

        };
    };

    template<typename W>
    class SpreadGraph<int,W>: public Graph<int,W>{
        protected:
            std::vector<std::list<std::pair<int,W>>> edges;
        public:
            unsigned long long size(){
                return edges.size();
            }

            void addVertex(int key){
                edges.push_back(std::list<std::pair<int,W>> ());
            }

            void addEdge(int source, int destiny, W weight){
                bool alreadyExists = false;
                for(std::pair<int,W> next: edges[source]){
                    if (next.first == destiny){
                        if (next.second > weight){
                            next.second = weight;
                        }
                        alreadyExists = true;
                    }
                }
                if(!alreadyExists){
                    edges[source].push_back(std::pair<int,W>(destiny, weight));
                }
            }

            W getWeight(int source, int destiny){
                for(std::pair<int,W> next: edges[source]){
                    if (next.first == destiny){
                        return next.second;
                    }
                }
                throw -1;
            }

            explicit SpreadGraph(int n): edges(std::vector<std::list<std::pair<int,W>>> (n)){

            }
    };
}

#endif