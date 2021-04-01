#include <iostream>
using namespace std;



// MapException
class MapException {
    public:
        string msg;
        MapException(string msg = "Something went wrong!"){
            this->msg = msg;
        }
};



class MapKeyNotFound : public MapException {
    public:
        MapKeyNotFound(string msg) : MapException(msg){}
};







template <class K, class V>
class Map {
    
    const string pass_key = "_GEJH[[&392YSJW_}2";
    const int fixed_size = 50;
    
    K* keys_array = new K[fixed_size];
    V* values_array = new V[fixed_size];
    
    int orig_size = fixed_size;
    int map_size = 0;
    bool sorted = false;
    
    
    
    int inline parse_index(int index){
        if(index < 0){
            if((0 - index) < map_size){
                index = map_size + index;
            }else{
                index = map_size;
            }
        }
        return index;
    }
    
    
    
    // to shift the items to their left index one by one
    void shift_left(K key, int i, int &deleted){
        deleted++;
        int current = 0;
        int next = i + current + 1;
        
        while((next <= map_size) && (map_size <= orig_size)){
            keys_array[i + current] = keys_array[next];
            values_array[i + current] = values_array[next];
            current++;
            next = i + current + 1;
        }
        
        if(keys_array[i] == key){
            shift_left(key, i, deleted);
        }
    }
    
    
    public:
        
        
        // to check key's existance
        bool has(K key){
            bool exists = false;
            for (int i = 0; i < map_size; i++) {
                if(keys_array[i] == key){
                    exists = true;
                    break;
                }
            }
            return exists;
        }
        
        
        // to set items in Map
        Map* set(K key, V val){
            if(!has(key)){
                
                if((map_size + 1) >= orig_size){
                    
                    orig_size += fixed_size;
                    K* k_arr = new K[orig_size];
                    V* v_arr = new V[orig_size];
                    
                    for (int i = 0; i < map_size; i++) {
                        k_arr[i] = (*keys_array++);
                        v_arr[i] = (*values_array++);
                    }
                    
                    k_arr[map_size] = key;
                    v_arr[map_size] = val;
                    keys_array = k_arr;
                    values_array = v_arr;
                    map_size++;
                    
                }else{
                    keys_array[map_size] = key;
                    values_array[map_size] = val;
                    map_size++;
                }
                
            }else{
                
                for (int i = 0; i < map_size; i++) {
                    if(keys_array[i] == key){
                        values_array[i] = val;
                        break;
                    }
                }
                
            }
            
            return this;
        }
        
        
        
        // to get item from array
        V get(K key){
            V val; int idx = -1;
            for (int i = 0; i < map_size; i++) {
                if(keys_array[i] == key){
                    idx = i;
                    break;
                }
            }
            if(idx >= 0){
                val = values_array[idx];
            }else{
                throw new MapKeyNotFound("given key doesn't exists!");
            }
            return val;
        }
        
        
        
        // to delete item
        Map* del(K key){
            int deleted = 0;
            for (int i = 0; i < map_size; i++) {
                if(keys_array[i] == key){
                    shift_left(key, i, deleted);
                }
            }
            
            map_size -= deleted;
            
            if((orig_size - map_size - fixed_size) > 0){
                
                orig_size -= fixed_size;
                K* k_arr = new K[orig_size];
                V* v_arr = new V[orig_size];
                
                for (int i = 0; i < map_size; i++) {
                    k_arr[i] = *keys_array++;
                    v_arr[i] = *values_array++;
                }
                
                // pointing to the first mem location
                keys_array -= map_size;
                values_array -= map_size;
                
                keys_array = k_arr;
                values_array = v_arr;
                
            }
            return this;
        }
        
        
        
        // to get an Array of the keys
        Array<K> keys(){
            Array<K> k_arr(keys_array, map_size);
            return k_arr;
        }
        
        
        
        // to get an Array of the values
        Array<V> values(){
            Array<V> v_arr(values_array, map_size);
            return v_arr;
        }
        
        
        
        // to sort the Map
        Map* sort(bool to_greater=true){
            int swapped = 0;
            for (int pass = (map_size - 1); pass >= 1; pass--) {
                for (int i = 0; i < pass; i++) {
                    if(to_greater){
                        if(keys_array[i] > keys_array[i+1]){
                            K temp_key = keys_array[i];
                            keys_array[i] = keys_array[i+1];
                            keys_array[i+1] = temp_key;
                            
                            V temp_val = values_array[i];
                            values_array[i] = values_array[i+1];
                            values_array[i+1] = temp_val;
                            swapped++;
                        }
                    }else{
                        if(keys_array[i] < keys_array[i+1]){
                            K temp_key = keys_array[i];
                            keys_array[i] = keys_array[i+1];
                            keys_array[i+1] = temp_key;
                            
                            V temp_val = values_array[i];
                            values_array[i] = values_array[i+1];
                            values_array[i+1] = temp_val;
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
        bool is_empty(){ return (map_size==0); }
        
        
        
        // to delete all items
        Map* clear(){
            for (int i = 0; i < map_size; i++) {
                delete[] keys_array++;
                delete[] values_array++;
            }
            keys_array = new K[fixed_size];
            values_array = new V[fixed_size];
            orig_size = fixed_size;
            map_size = 0;
            return this;
        }
        
        
        
        // to loop through the Map
        void each(void(for_each)(K, V)){
            for (int i = 0; i < map_size; i++) {
                for_each(keys_array[i], values_array[i]);
            }
        }
        
        
        
        // to loop through the Map items and set the value as the lambda function returns
        void map(V(for_each)(V)){
            for (int i = 0; i < map_size; i++) {
                V item = for_each(values_array[i]);
                values_array[i] = item;
            }
        }
        
        
        
        // to get a new array in reverse order
        Map reverse(){
            Map<K, V> a;
            for (int i = 1; i < map_size; i++) {
                a.set(keys_array[parse_index(-i)], values_array[parse_index(-i)]);
            }
            return a;
        }
        
        
        
        // to slice the array
        Map slice(int from, int to){
            Map<K, V> m;
            if(from < to){
                for (int i = from; i < to; i++) {
                    m.set(keys_array[i], values_array[i]);
                }
            }
            return m;
        }
        
        
        
        Map* merge(Map<K, V> &m){
            for (int i = 0; i < m.size(); i++) {
                K k = m.__key_at__(i, this->pass_key);
                this->set(k, m.get(k));
            }
            m.clear();
            return this;
        }
        
        
        // to get the Map size
        int size(){ return map_size; }
        
        
        // to get key at index
        K __key_at__(int i, string pass_key){
            K *k;
            if(pass_key == this->pass_key){
                *k = keys_array[i];
            }
            return *k;
        }
    
};

