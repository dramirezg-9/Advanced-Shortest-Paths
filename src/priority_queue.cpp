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