#include <iostream>
#include <cstddef>
#include <iterator>

template <typename T>
class Vector
{
    private:
    size_t size;
    size_t capacity;
    T* data;
    void reallocate(size_t n_cap)
    {
        T* n_data = new T[n_cap];
        for(size_t i = 0; i < size; ++i)
        {
            n_data[i]= std::move(data[i]);
        }
        delete[] data;
        data = n_data;
        capacity = n_cap; 
    }

    public:
    Vector():size(0), capacity(0), data(nullptr){}
    Vector(const Vector& other):size(0), capacity(0), data(nullptr)
    {
        reallocate(other.size);
        for(size_t i = 0; i < other.size; ++i)
        {
            data[i]= other.data[i];
        }
        size= other.size;
    }
    Vector& operator=(const Vector& other)
    {
        if(this != &other)
        {
            delete[] data;
            data = new T[other.size];
            capacity =  other.size;
            size = other.size;
            for(size_t i = 0; i < other.size; ++i)
            {
                data[i] = other.data[i];
            }

        }
    }
    ~Vector()
    {
        delete [] data;
    }
    size_t get_size()const
    {
        return size;
    }
    size_t get_cap()const
    {
        return capacity;
    }
    void push_back(const T& value)
    {
        if(size==capacity)
        {
            size_t n_cap = (capacity == 0) ? 1 : capacity * 2;
            reallocate(n_cap);
        }
        data[size++] = value;
    }
    T& operator[] (size_t i)
    {
        return data[i];
    }
    const T& operator[](size_t i) const
    {
        return data[i]; 
    }
    void clear()
    {
        size = 0;
    }

    class Iterator
    {
        private:
        T* ptr;

        public:
        using iterator_cat = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(T* n_ptr = nullptr): ptr(n_ptr){}

        reference operator*()const {return *ptr;};
        pointer operator ->()const {return  ptr;};
        Iterator operator++(){
            ++ptr;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++ptr;
            return tmp;
        }
        Iterator operator--(){
            --ptr;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator tmp = *this;
            --ptr;
            return tmp;
        }
        Iterator operator+(difference_type val) const
        {
            return Iterator(ptr + val);
        }
        Iterator operator-(difference_type val) const
        {
            return Iterator(ptr - val);
        }
        Iterator& operator+=(difference_type val) 
        {
            ptr += val;
            return *this;
        }
        Iterator& operator-=(difference_type val) 
        {
            ptr -= val;
            return *this;
        }
        reference operator[](difference_type val) const
        {
            return ptr[val];
        }
        bool operator ==(const Iterator& val) const
        {
            return ptr == val.ptr;
        }
        bool operator !=(const Iterator& val) const
        {
            return ptr != val.ptr;
        }
        bool operator <(const Iterator& val) const
        {
            return ptr < val.ptr;
        }
        bool operator >(const Iterator& val) const
        {
            return ptr > val.ptr;
        }
        bool operator <=(const Iterator& val) const
        {
            return ptr <= val.ptr;
        }
        bool operator >=(const Iterator& val) const
        {
            return ptr >= val.ptr;
        }
        difference_type operator-(const Iterator& val)const
        {
            return ptr- val.ptr;
        }
    };
    class Const_Iterator
    {
        private:
        const T* ptr;

        public:
        using iterator_cat = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        Const_Iterator(const T* n_ptr=nullptr):ptr(n_ptr){}
        Const_Iterator(const Iterator& other): ptr(other.ptr){}
        reference operator*()const {return *ptr;};
        pointer operator ->()const {return  ptr;};
        Const_Iterator operator++(){
            ++ptr;
            return *this;
        }
        Const_Iterator operator++(int)
        {
            Const_Iterator tmp = *this;
            ++ptr;
            return tmp;
        }
        Const_Iterator operator--(){
            --ptr;
            return *this;
        }
        Const_Iterator operator--(int)
        {
            Const_Iterator tmp = *this;
            --ptr;
            return tmp;
        }
        Const_Iterator operator+(difference_type val) const
        {
            return Const_Iterator(ptr + val);
        }
        Const_Iterator operator-(difference_type val) const
        {
            return Const_Iterator(ptr - val);
        }
        Const_Iterator& operator+=(difference_type val) 
        {
            ptr += val;
            return *this;
        }
        Const_Iterator& operator-=(difference_type val) 
        {
            ptr -= val;
            return *this;
        }
        reference operator[](difference_type val) const
        {
            return ptr[val];
        }
        bool operator ==(const Const_Iterator& val) const
        {
            return ptr == val.ptr;
        }
        bool operator !=(const Const_Iterator& val) const
        {
            return ptr != val.ptr;
        }
        bool operator <(const Const_Iterator& val) const
        {
            return ptr < val.ptr;
        }
        bool operator >(const Const_Iterator& val) const
        {
            return ptr > val.ptr;
        }
        bool operator <=(const Const_Iterator& val) const
        {
            return ptr <= val.ptr;
        }
        bool operator >=(const Const_Iterator& val) const
        {
            return ptr >= val.ptr;
        }
        difference_type operator-(const Const_Iterator& val)const
        {
            return ptr- val.ptr;
        }

    };
    class Reverse_Iterator
    {
        private:
        T* ptr;

        public:
        using iterator_cat = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        Reverse_Iterator(T* n_ptr=nullptr):ptr(n_ptr){}
        reference operator*()const {return *(ptr-1);};
        pointer operator ->()const {return  ptr-1;};
        Reverse_Iterator operator++(){
            --ptr;
            return *this;
        }
        Reverse_Iterator operator++(int)
        {
            Reverse_Iterator tmp = *this;
            --ptr;
            return tmp;
        }
        Reverse_Iterator operator--(){
            ++ptr;
            return *this;
        }
        Reverse_Iterator operator--(int)
        {
            Reverse_Iterator tmp = *this;
            ++ptr;
            return tmp;
        }
        Reverse_Iterator operator+(difference_type val) const
        {
            return Reverse_Iterator(ptr - val);
        }
        Reverse_Iterator operator-(difference_type val) const
        {
            return Reverse_Iterator(ptr + val);
        }
        Reverse_Iterator& operator+=(difference_type val) 
        {
            ptr -= val;
            return *this;
        }
        Reverse_Iterator& operator-=(difference_type val) 
        {
            ptr += val;
            return *this;
        }
        reference operator[](difference_type val) const
        {
            return *(ptr-val-1);
        }
        bool operator ==(const Reverse_Iterator& val) const
        {
            return ptr == val.ptr;
        }
        bool operator !=(const Reverse_Iterator& val) const
        {
            return ptr != val.ptr;
        }
        bool operator <(const Reverse_Iterator& val) const
        {
            return ptr > val.ptr;
        }
        bool operator >(const Reverse_Iterator& val) const
        {
            return ptr < val.ptr;
        }
        bool operator <=(const Reverse_Iterator& val) const
        {
            return ptr >= val.ptr;
        }
        bool operator >=(const Reverse_Iterator& val) const
        {
            return ptr <= val.ptr;
        }
        difference_type operator-(const Reverse_Iterator& val)const
        {
            return val.ptr-ptr;
        }

    };
    class Const_Reverse_Iterator
    {
        private:
        const T* ptr;

        public:
        using iterator_cat = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        Const_Reverse_Iterator(const T* n_ptr=nullptr):ptr(n_ptr){}
        Const_Reverse_Iterator(const Reverse_Iterator& other): ptr(other.ptr){}
        reference operator*()const {return *(ptr-1);};
        pointer operator ->()const {return  ptr-1;};
        Const_Reverse_Iterator operator++(){
            --ptr;
            return *this;
        }
        Const_Reverse_Iterator operator++(int)
        {
            Const_Reverse_Iterator tmp = *this;
            --ptr;
            return tmp;
        }
        Const_Reverse_Iterator operator--(){
            ++ptr;
            return *this;
        }
        Const_Reverse_Iterator operator--(int)
        {
            Const_Reverse_Iterator tmp = *this;
            ++ptr;
            return tmp;
        }
        Const_Reverse_Iterator operator+(difference_type val) const
        {
            return Const_Reverse_Iterator(ptr - val);
        }
        Const_Reverse_Iterator operator-(difference_type val) const
        {
            return Const_Reverse_Iterator(ptr + val);
        }
        Const_Reverse_Iterator& operator+=(difference_type val) 
        {
            ptr -= val;
            return *this;
        }
        Const_Reverse_Iterator& operator-=(difference_type val) 
        {
            ptr += val;
            return *this;
        }
        reference operator[](difference_type val) const
        {
            return *(ptr-val-1);
        }
        bool operator ==(const Const_Reverse_Iterator& val) const
        {
            return ptr == val.ptr;
        }
        bool operator !=(const Const_Reverse_Iterator& val) const
        {
            return ptr != val.ptr;
        }
        bool operator <(const Const_Reverse_Iterator& val) const
        {
            return ptr > val.ptr;
        }
        bool operator >(const Const_Reverse_Iterator& val) const
        {
            return ptr < val.ptr;
        }
        bool operator <=(const Const_Reverse_Iterator& val) const
        {
            return ptr >= val.ptr;
        }
        bool operator >=(const Const_Reverse_Iterator& val) const
        {
            return ptr <= val.ptr;
        }
        difference_type operator-(const Const_Reverse_Iterator& val)const
        {
            return val.ptr-ptr;
        }

    };
    Iterator begin()
    {
        return Iterator(data);
    }
    Iterator end()
    {
        return Iterator(data+size);
    }
    Const_Iterator begin()const
    {
        return Const_Iterator(data);
    }
    Const_Iterator end()const
    {
        return Const_Iterator(data+size);
    }
    Const_Iterator cbegin()const
    {
        return Const_Iterator(data);
    }
    Const_Iterator cend()const
    {
        return Const_Iterator(data+size);
    }
    Reverse_Iterator rbegin()
    {
        return Reverse_Iterator(data+ size);
    }
    Reverse_Iterator rend()
    {
        return Reverse_Iterator(data);
    }
    Const_Reverse_Iterator rbegin()const
    {
        return Const_Reverse_Iterator(data+ size);
    }
    Const_Reverse_Iterator rend()const 
    {
        return Const_Reverse_Iterator(data);
    }
    Const_Reverse_Iterator crbegin()const
    {
        return Const_Reverse_Iterator(data+ size);
    }
    Const_Reverse_Iterator crend()const 
    {
        return Const_Reverse_Iterator(data);
    }
};
int main()
{
    Vector<int> vec;
    vec.push_back(7);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(1);
    for(Vector<int>::Iterator i = vec.begin(); i != vec.end(); ++i)
    {
        std::cout<<*i<<" ";
    }
    std::cout<<std::endl;
    for(Vector<int>::Reverse_Iterator i = vec.rbegin(); i != vec.rend(); ++i)
    {
        std::cout<<*i<<" ";
    }
    std::cout<<std::endl;
    vec.push_back(12);
    vec.push_back(21);
    vec.push_back(17);
    for(Vector<int>::Const_Iterator i = vec.cbegin(); i != vec.cend(); ++i)
    {
        std::cout<<*i<<" ";
    }
    std::cout<<std::endl;

    for(Vector<int>::Const_Reverse_Iterator i = vec.crbegin(); i != vec.crend(); ++i)
    {
        std::cout<<*i<<" ";
    }
    std::cout<<std::endl;

    return 0;
}