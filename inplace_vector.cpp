#include <memory>
#include <new>
#include <print>
#include <cstdint>
#include <chrono>
#include <list>
#include <ratio>
#include <stdexcept>
#include <vector>

template <typename T,size_t capacity>
class StackAllocator{
    static inline T buffer[capacity];
    size_t elements_already_used=0; 
    public:
        using value_type = T;
        constexpr T* allocate(size_t n) {
            size_t elements_needed = n;
            if (elements_already_used + elements_needed > capacity) {
                throw std::logic_error("All the buffer has begin used");
            }
            T* result_ptr=&buffer[elements_already_used];
            elements_already_used += elements_needed;
            return result_ptr;
        }
        constexpr void deallocate(T* ptr,size_t n){
            return ; // Nothing is actually done
        }
        
    // Required rebind mechanism
    template<typename U>
    struct rebind {
        using other = StackAllocator<U, capacity>;
    };
    
    
};

using namespace std::chrono;

int main(){
    constexpr size_t N=1024*1024;
    auto start=high_resolution_clock::now();
    std::vector<int,StackAllocator<int,N>> stack_vec;
    stack_vec.reserve(N);
    auto end=high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    std::println("Stack allocator: {}",duration);
   
   
    start=high_resolution_clock::now();
    std::vector<int> heap_vec;
    heap_vec.reserve(N);
    end=high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    std::println("Heap allocator: {}",duration);
   


}