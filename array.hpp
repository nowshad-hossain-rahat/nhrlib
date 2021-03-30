#include <iostream>
using namespace std;



// ArrayException
class ArrayException {
    public:
        string msg;
        ArrayException(string msg = "Something went wrong!"){
            this->msg = msg;
        }
};



class ArrayIndexOutOfBound : public ArrayException {
    public:
        ArrayIndexOutOfBound(string msg) : ArrayException(msg){}
};







template <class T>
class Array {
    
    T* arr = new T[10];
    int orig_size = 10;
    int arr_size = 0;
    bool sorted = false;
    
    int inline parse_index(int index){
        if(index <= 0){
            if((0 - index) < arr_size){
                index = arr_size + index;
            }else{
                index = arr_size;
            }
        }
        return index;
    }
    
    
    
    // to shift the items to their left index one by one
    void shift_left(T item, int i, int &deleted){
        deleted++;
        int current = 0;
        int next = i + current + 1;
        
        while((next <= arr_size) && (arr_size <= orig_size)){
            arr[i + current] = arr[next];
            current++;
            next = i + current + 1;
        }
        
        if(arr[i] == item){
            shift_left(item, i, deleted);
        }
    }
    
    
    public:
        
        
        Array(T a[], int size){
            for (int i = 0; i < size; i++) {
                
                T item = a[i];
                
                if((arr_size + 1) >= orig_size){
                    
                    orig_size += 10;
                    T* new_arr = new T[orig_size];
                    for (int i = 0; i < arr_size; i++) {
                        new_arr[i] = (*arr++);
                    }
                    new_arr[arr_size] = item;
                    arr = new_arr;
                    arr_size++;
                    
                }else{
                    arr[arr_size] = item;
                    arr_size++;
                }
            }
        }
        
        
        // default constructor
        Array(){}
        
        
        
        // to push items in Array
        Array* push(T item){
            if((arr_size + 1) >= orig_size){
                
                orig_size += 10;
                T* new_arr = new T[orig_size];
                for (int i = 0; i < arr_size; i++) {
                    new_arr[i] = (*arr++);
                }
                new_arr[arr_size] = item;
                arr = new_arr;
                arr_size++;
                
            }else{
                arr[arr_size] = item;
                arr_size++;
            }
            return this;
        }
        
        
        
        // to get item from array
        T get(int index){
            
            T* item;
            index = parse_index(index);
            
            if(index >= arr_size){
                throw ArrayIndexOutOfBound("Given index is greater than the Array size!");
            }else{
                *item = arr[index];
            }
            
            return *item;
        }
        
        
        
        // to check itens existance
        bool has(T item){
            bool exists = false;
            for (int i = 0; i < arr_size; i++) {
                if(arr[i] == item){
                    exists = true;
                    break;
                }
            }
            return exists;
        }
        
        
        
        
        // to get item's index
        bool index_of(T item){
            bool index = -1;
            for (int i = 0; i < arr_size; i++) {
                if(arr[i] == item){
                    index = i;
                    break;
                }
            }
            return index;
        }
        
        
        
        // to insert items
        Array* insert(int index, T item, int times=1){
            if((index >=0) && (index < arr_size)){
                for (int i = 0; i < times; i++) {
                    if((arr_size + 1) >= orig_size ){
                        orig_size += 10;
                        T* new_arr = new T[orig_size];
                        
                        for (int i = 0; i < index; i++) {
                            new_arr[i] = arr[i];
                        }
                        
                        new_arr[index] = item;
                        arr_size++;
                        
                        for (int i = (index+1); i < arr_size; i++) {
                            new_arr[i] = arr[i-1];
                        }
                        
                        arr = new_arr;
                        
                    }else{
                        arr_size++;
                        for (int i = (arr_size - 1); i > index; i--) {
                            arr[i] = arr[i-1];
                        }
                        arr[index] = item;
                    }
                }
            }
            return this;
        }
        
        
        
        // to delete item
        Array* del(T item){
            int deleted = 0;
            for (int i = 0; i < arr_size; i++) {
                if(arr[i] == item){
                    shift_left(item, i, deleted);
                }
            }
            
            arr_size -= deleted;
            
            if((orig_size - arr_size - 10) > 0){
                orig_size -= 10;
                T* new_arr = new T[orig_size];
                for (int i = 0; i < arr_size; i++) {
                    new_arr[i] = *arr++;
                }
                arr -= arr_size;
                arr = new_arr;
            }
            return this;
        }
        
        
        
        // to sort the Array
        Array* sort(bool to_greater=true){
            int swapped = 0;
            for (int pass = (arr_size - 1); pass >= 1; pass--) {
                for (int i = 0; i < pass; i++) {
                    if(to_greater){
                        if(arr[i] > arr[i+1]){
                            T temp = arr[i];
                            arr[i] = arr[i+1];
                            arr[i+1] = temp;
                            swapped++;
                        }
                    }else{
                        if(arr[i] < arr[i+1]){
                            T temp = arr[i];
                            arr[i] = arr[i+1];
                            arr[i+1] = temp;
                            swapped++;
                        }
                    }
                }
                
                if(swapped==0){ break; }
            }
            
            sorted = true;
            return this;
        }
        
        
        
        // to check is size is 0
        bool is_empty(){ return (arr_size==0); }
        
        
        
        // to delete all items
        Array* clear(){
            for (int i = 0; i < arr_size; i++) {
                delete[] arr++;
            }
            arr = new T[10];
            orig_size = 10;
            arr_size = 0;
            return this;
        }
        
        
        
        // to loop through the Array
        void each(void(for_each)(int, T)){
            for (int i = 0; i < arr_size; i++) {
                for_each(i, arr[i]);
            }
        }
        
        
        
        // to loop through the Array items and set the value as the lambda function returns
        void map(T(for_each)(T)){
            for (int i = 0; i < arr_size; i++) {
                T item = for_each(arr[i]);
                arr[i] = item;
            }
        }
        
        
        
        // to get a new array in reverse order
        Array reverse(){
            Array<T> a;
            for (int i = 1; i < arr_size; i++) {
                a.push(arr[parse_index(-i)]);
            }
            return a;
        }
        
        
        
        // to slice the array
        Array slice(int from, int to){
            Array a;
            if(from < to){
                for (int i = from; i < to; i++) {
                    a.push(arr[i]);
                }
            }
            return a;
        }
        
        
        // to get the Array size
        int size(){ return arr_size; }
        
    
};

