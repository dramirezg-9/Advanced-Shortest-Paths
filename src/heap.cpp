#ifndef GP0_HEAP
#define GP0_HEAP

#include "priority_queue.cpp"
#include <vector>
#include <unordered_map>
#include <limits>

namespace gp0{

    template <typename K, typename V>
    class Heap: public gp0::priority_queue<K,V>
    {
        private:
            Heap<int, V> real_heap;
            std::unordered_map<K, int> keys_to_indices;
            std::unordered_map<int, K> indices_to_keys;
        public:
            size_t size(){
                return real_heap.size();
            }

            bool empty(){
                return real_heap.empty();
            }

            void popTop(){
                real_heap.popTop(); 
            }

            void addKey(K key, V value){
                if (keys_to_indices.end() != keys_to_indices.find(key)) throw -1;
                else {
                    keys_to_indices[key] = real_heap.real_size();
                    indices_to_keys[real_heap.real_size()] = key;
                    real_heap.addKey(0, value);
                }
            }

            V getValue(K key){
                if (keys_to_indices.end() == keys_to_indices.find(key)) throw -1;
                else return real_heap.getValue(keys_to_indices[key]);
            }

            std::pair<K,V> getTop(){
                std::pair<int,V> real_pair = real_heap.getTop();
                return std::pair<K,V> (indices_to_keys[real_pair.first], real_pair.second);
            }

            void decreaseKey(K key, V value){
                if (keys_to_indices.end() == keys_to_indices.find(key)) throw -1;
                real_heap.decreaseKey(keys_to_indices[key], value);
            }

            explicit Heap(): real_heap(0){}
    };
    
    template<typename V> class Heap<int,V>: public gp0::priority_queue<int,V>{
        private:
            size_t tsize;
            std::vector<std::pair<int,V>> distances;
            std::vector<int> positions;

            void custom_swap(int a, int b){
                swap(distances[a], distances[b]);
                positions[distances[a].first] =  a;
                positions[distances[b].first] =  b;
            }

            void sink(int &current){
                V parent_distance = distances[current].second;
                V left_distance = current * 2 + 1 < tsize ? distances[current * 2 + 1].second: std::numeric_limits<V>::max();
                V right_distance = current * 2 + 2 < tsize ? distances[current * 2 + 2].second: std::numeric_limits<V>::max();
                if (parent_distance <= left_distance &&  parent_distance <= right_distance){
                positions[distances[current].first] =  current;
                current=tsize;
                } else if (left_distance <= right_distance){
                custom_swap(current, current * 2 + 1);
                current = current * 2 + 1;
                } else {
                custom_swap(current, current * 2 + 2);
                current = current * 2 + 2;
                }
            }

            void raise (int &current){
                V child_distance = distances[current].second;
                V parent_distance = distances[(current - 1) / 2].second;
                if (parent_distance == -1 || child_distance < parent_distance){
                custom_swap(current, (current - 1)/2);
                current = (current - 1)/2;
                } else current = 0;
            }

        public:
        
            size_t size(){
                return tsize;
            }

            size_t real_size(){
                return positions.size();
            }

            bool empty(){
                return tsize != 0;
            }

            void popTop(){
                if(tsize){
                    tsize--;
                    distances[0] = distances[tsize];
                    positions[distances[0].first] = 0;
                    int current = 0;
                    while(current < tsize){
                        sink(current);
                    }
                }   
            }

            void addKey(int key, V value){
                key = positions.size();
                if (tsize >= distances.size()) distances.push_back(std::pair<int,V> (key,std::numeric_limits<V>::max()));
                else distances[tsize] = std::pair<int,V> (key,std::numeric_limits<V>::max());
                positions.push_back(tsize);
                tsize++;
                decreaseKey(key, value);
            }

            V getValue(int key){
                return distances[positions[key]].second;
            }

            std::pair<int,V> getTop(){
                if (tsize) return std::pair<int,V> (distances[0].first, distances[0].second);
                else throw -1;
            }

            void decreaseKey(int key, V value){
                int position = positions[key];
                if (position != -1 && value < distances[position].second){
                    distances[position].second = value;
                    while(position){
                        raise(position);
                    }
                }
            }

            explicit Heap(): tsize(0), distances(std::vector<std::pair<int,V>>(0)), positions(std::vector<int> (0)) {

            }

            explicit Heap(int v): tsize(v), distances(std::vector<std::pair<int,V>>(v)), positions(std::vector<int> (v, 0)) {
                for (int i = 0; i < v; ++i){
                    distances[i] = std::pair<int,int> (i,std::numeric_limits<V>::max());
                    positions[i] = i;
                }
            }
    };
}

#endif