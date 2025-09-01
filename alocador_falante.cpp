#include <memory>
#include <print>
#include <vector>

template <typename T>
class StackAllocator{
    std::allocator<T> default_alloc;
    public:
        using value_type = T;
        T* allocate(size_t n){
            std::println("Im allocating {} elements",n);
            return default_alloc.allocate(n);
        }
        void deallocate(T* ptr,size_t n){
            std::println("I'm deallocating");
            default_alloc.deallocate(ptr,n);
        }
};


int main(){
    std::vector<int,StackAllocator<int>> vec;
    for (int i=0;i<5;i++){
        vec.push_back(i);
    }
}