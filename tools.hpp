#include <iostream>
using namespace std;



// to get typeid
template <class T>
string type(T val){
    return typeid(val).name();
}



// convert string to uppercase
string upper(string txt){
    string new_str;
    for (char c : txt) {
        int ascii = (int) c;
        if((ascii >= 97) && (ascii<123)){
            new_str += (char) (ascii - 32);
        }else{
            new_str += c;
        }
    }
    return new_str;
}



// convert string to lowercase
string lower(string txt){
    string new_str;
    for (char c : txt) {
        int ascii = (int) c;
        if((ascii >= 65) && (ascii<91)){
            new_str += (char) (ascii + 32);
        }else{
            new_str += c;
        }
    }
    return new_str;
}



// to search sub_str in string
int search(string sub_str, string sub){
    int pos = -1;
    size_t idx = sub.find(sub_str);
    if(idx != string::npos){
        pos = idx;
    }
    return pos;
}



// to replace sub_str of a string
string replace(string to_repl, string repl_by, string repl_from){
    string new_str;
    int pos = search(to_repl, repl_from);
    int len = (repl_by.length() == 0) ? 1:repl_by.length();
    if(pos!= -1){
        new_str = repl_from.replace(pos, len, repl_by);
    }
    return new_str;
}




// to replace all occurances sub_str of a string
string replace_all(string to_repl, string repl_by, string repl_from){
    string new_str = repl_from;
    int pos = search(to_repl, new_str);
    int len = (repl_by.length() == 0) ? 1:repl_by.length();
    while(pos!= -1){
        new_str = new_str.replace(pos, len, repl_by);
        pos = search(to_repl, new_str);
    }
    return new_str;
}



// to match typeid
template <class T1,class T2>
bool is_same_type(T1 v1, T2 v2){
    return (typeid(v1).name() == typeid(v2).name());
}



template <class T>
bool is_str(T v){
    return is_same_type(v, "str");
}



template <class T>
bool is_int(T v){
    return is_same_type(v, 1);
}



template <class T>
bool is_float(T v){
    return is_same_type(v, 1.1);
}




template <class T>
bool is_bool(T v){
    return is_same_type(v, true);
}




template <class T>
bool is_char(T v){
    return is_same_type(v, 'c');
}



// to convert to string
template <class T>
string str(T val){
    string new_str;
    
    if(is_int(val) || is_float(val)){
        new_str = to_string(val);
    }else if(is_bool(val)){
        new_str = (val) ? "ture":"false";
    }else if(is_char(val)){
        new_str += val;
    }
    
    return new_str;
}



// to convert ascii to char
char chr(int ascii){
    return ((char) ascii);
}



// to convert a single char to a single int digit
int to_one_digit(char c){
    int n = 0;
    if(c=='1'){
        n = 1;
    }else if(c=='2'){
        n = 2;
    }else if(c=='3'){
        n = 3;
    }else if(c=='4'){
        n = 4;
    }else if(c=='5'){
        n = 5;
    }else if(c=='6'){
        n = 6;
    }else if(c=='7'){
        n = 7;
    }else if(c=='8'){
        n = 8;
    }else if(c=='9'){
        n = 9;
    }
    return n;
}



// to convert to number
template <class T>
double num(T val){
    double number = 0;
    
    if(is_char(val)){
        number = (int) val;
    }else if(is_str(val)){
        
        string new_str;
        new_str += val;
        bool dot = false;
        int div_by = 10;
        
        for (int i = 0; i < new_str.length(); i++) {
            
            if((i==0) && (new_str.at(i)=='-')){
                number = 0 - number;
                continue;
            }else if(new_str.at(i)=='.'){
                dot = true;
                continue;
            }
            
            if(!dot){
                number = (number * 10) + to_one_digit(new_str.at(i));
            }else{
                int n = to_one_digit(new_str.at(i));
                float nfl = (float) n / div_by;
                div_by *= 10;
                number += nfl;
            }
            
        }
        
        
    }else if(is_bool(val)){
        number = (val) ? 1:0;
    }
    
    return number;
}



// to take input from console
string input(string text){
    string val;
    cout << text;
    getline(cin, val);
    return val;
}


// to output text in console
template <
        class T1=string,
        class T2=string,
        class T3=string,
        class T4=string,
        class T5=string,
        class T6=string,
        class T7=string,
        class T8=string,
        class T9=string,
        class T10=string,
        class T11=string,
        class T12=string,
        class T13=string,
        class T14=string,
        class T15=string,
        class T16=string,
        class T17=string,
        class T18=string,
        class T19=string,
        class T20=string
    >
void print(
        T1 str1="",
        T2 str2="",
        T3 str3="",
        T4 str4="",
        T5 str5="",
        T6 str6="",
        T7 str7="",
        T8 str8="",
        T9 str9="",
        T10 str10="",
        T11 str11="",
        T12 str12="",
        T13 str13="",
        T14 str14="",
        T15 str15="",
        T16 str16="",
        T17 str17="",
        T18 str18="",
        T19 str19="",
        T20 str20=""
    ){
    // printing them to the console
    cout
    << str1 
    << str2
    << str3
    << str4 
    << str5 
    << str6
    << str7
    << str8 
    << str9
    << str10
    << str11
    << str12
    << str13 
    << str14 
    << str15
    << str16
    << str17 
    << str18 
    << str19
    << str20
    << endl;
}
