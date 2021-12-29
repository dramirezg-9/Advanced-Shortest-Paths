#ifndef GP0_PRIORITY_QUEUE
#define GP0_PRIORITY_QUEUE
#include <utility>

namespace gp0
{
    template<typename K, typename V>
    class priority_queue{
        public:
            virtual void addKey(K key, V value)=0;
            virtual V getValue(K key)=0;
            virtual void decreaseKey(K key, V value)=0;
            virtual std::pair<K,V> getTop()=0;
            virtual void popTop()=0;
            virtual unsigned long long size()=0;
            virtual bool empty()=0;
    };
}
#endif