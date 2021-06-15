// ...
// Fill in all necessary extra code in this space to satisfy all questions below. // You cannot change any other content other than the places marked as red.
// ...
// StudentID: S018039, Name: Muhammed Esad Simitcioglu
#include <iostream>
#include <vector>
template<typename ...> struct TD; // your compile time debug helper (TypeDisplayer)

// WRITE YOUR CODE HERE (STARTS)

template<typename T>
concept isContainer = requires (T t) {
    t.begin();
    t.end();
    t.size();
};


template<typename Header,typename Second,typename ...Rest>
void print(Header header,Second input,Rest ...rest){
    std::cout << std::endl;
    std::cout << header << std::endl;

    if constexpr(isContainer<Second>){
        for(auto item : input)
            std::cout << item << " ";

        std::cout << std::endl;

    }
    else{
        std::cout << input << std::endl;
    }

    if constexpr(sizeof... (rest) > 0){
        print(rest...);
    }
}



struct ${

    int order = 0;

    auto operator()(auto&& first,auto&& second,auto&& third){
        if(order == 1){
            return first;
        }
        else if(order == 2){
            return second;
        }
        else{
            return third;
        }
    }
    auto operator==(auto value){
        return[=](auto item){
            return item==value;
        };
    }
    auto operator++(){
        return[=](auto&& item){

            return ++item;
        };
    }
    auto operator++(int){
        return[=](auto&& item){
            return item++;
        };
    }
};

auto operator>($,auto&& value){
    return[=](auto&& item){
        return item>value;
    };
}


template<typename val,typename Lambda>
requires std::is_arithmetic_v<std::remove_cvref_t<val>>
    auto operator>(val&& value,Lambda&& lambda) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lambda(rest...)  > std::forward<val>(value);
    };
}

template<typename Lambda1,typename Lambda2>
auto operator>(Lambda1&& lam1,Lambda2&& lam2) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lam1(rest...) > lam2(rest...);
    };
}

template<typename Lambda,typename val>
requires std::is_arithmetic_v<std::remove_cvref_t<val>>
    auto operator>(Lambda&& lam,val&& value) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lam(rest...)  > std::forward<val>(value);
    };
}

template<typename val,typename Lambda>
requires std::is_arithmetic_v<std::remove_cvref_t<val>>
    auto operator+(val&& value,Lambda&& lambda) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lambda(rest...) + std::forward<val>(value);
    };
}

template<typename Lambda1,typename Lambda2>
auto operator+(Lambda1&& lam1,Lambda2&& lam2) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lam1(rest...) + lam2(rest...);
    };
}

template<typename Lambda,typename val>
requires std::is_arithmetic_v<std::remove_cvref_t<val>>
    auto operator+(Lambda&& lam,val&& value) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lam(rest...) + std::forward<val>(value);
    };
}

template<typename val,typename Lambda>
requires std::is_arithmetic_v<std::remove_cvref_t<val>>
    auto operator*(val&& value,Lambda&& lambda) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lambda(rest...) * std::forward<val>(value);
    };
}

template<typename Lambda1,typename Lambda2>
auto operator*(Lambda1&& lam1,Lambda2&& lam2) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lam1(rest...) * lam2(rest...);
    };
}

template<typename Lambda,typename val>
requires std::is_arithmetic_v<std::remove_cvref_t<val>>
    auto operator*(Lambda&& lam,val&& value) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return  lam(rest...)  * std::forward<val>(value);
    };
}

template<typename val,typename Lambda>
requires std::is_arithmetic_v<std::remove_cvref_t<val>>
    auto operator/(val&& value,Lambda&& lambda) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lambda(rest...) / std::forward<val>(value);
    };
}

template<typename Lambda1,typename Lambda2>
auto operator/(Lambda1&& lam1,Lambda2&& lam2) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lam1(rest...) / lam2(rest...);
    };
}

template<typename Lambda,typename val>
requires std::is_arithmetic_v<std::remove_cvref_t<val>>
    auto operator/(Lambda&& lam,val&& value) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lam(rest...) / std::forward<val>(value);
    };
}

template<typename val,typename Lambda>
requires std::is_arithmetic_v<std::remove_cvref_t<val>>
    auto operator-(val&& value,Lambda&& lambda) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lambda(rest...)  - std::forward<val>(value);
    };
}

template<typename Lambda1,typename Lambda2>
auto operator-(Lambda1&& lam1,Lambda2&& lam2) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lam1(rest...) - lam2(rest...);
    };
}

template<typename Lambda,typename val>
requires std::is_arithmetic_v<std::remove_cvref_t<val>>
    auto operator-(Lambda&& lam,val&& value) -> decltype (auto){
    return[=](auto&& ...rest) mutable {
        return lam(rest...) - std::forward<val>(value);
    };
}

$ $1 = ${1};
$ $2 = ${2};
$ $3 = ${3};

template<typename T>
struct Vector : public std::vector<T>{

    using std::vector<T>::vector;

    auto operator[](int&& n) -> T{
        if(n<0){
            return this->at(this->size()+n);
        }
        else {
            return this->at(n);
        }

    }
    template<typename arithmetic>
    auto operator[](std::vector<arithmetic> vector){

        auto new_vector = std::vector<T>();

        for(size_t i =0;i<vector.size();++i){
            if(vector[i]){
                new_vector.push_back(this->at(i));
            }
        }
        return new_vector;
    }
    auto operator[](auto lambda){

        auto new_vector = std::vector<T>();
        for(auto&& item : *this){
            new_vector.push_back(lambda(std::forward<decltype (item)>(item)));
        }
        return new_vector;
    }
};

template<typename T>
Vector(T) -> Vector<T>;

template<typename First,typename ...Rest>
Vector(First,Rest...) -> Vector<First>;


// WRITE YOUR CODE HERE (ENDS)


int main() {
    // design a print overload-set or a single print function that can generically print any number of
    // containers and strings and other values in a single call to print. check the below usage of print.
    // design a math expression system that lazily represents an operation over values that will be later provided // use $1, $2, $3 as special variables of this math expression toolkit
    // $1 means the first value, $2 means the second, $3 means the third value supplied to a function/lambda
    // (yes, using $ is valid for variables!)
    // for instance; auto e=$3-$1+$2 creates an expression via composing 3 different lambdas
    // when later called with (10, 20, 30, 40, 50, ...) evaluates to 30-10+20
    // your design shall take care of at least +, -, *, /, ++, > operators
    // note that ++i and i++ are different overloads. How to overload both of them? Check the internet. // > will create a lazy boolean expression
    // ++ will also touch and change the item itself
    // (for instance running $1++ over a vector will increment all elements by one after the evaluation is done) // operator precedence is the same as the precedences that are defined in the C++ language
    // if you do compose two lambdas from left to right, there shall be no problem with the precedence
    // language will take care of it for you
    // create a Vector<...> class that inherits from vector<...> and extends it so that after auto v = Vector{...}; // v[boolean expression] outputs a mask of vector<bool>
    // v[other expression] creates a new vector that contains transformed items according to the expression
    // v[vector<bool>] selects only the elements that correspond to boolean true locations of the vector<bool> mask // v[index] works as before
    // v[-index] selects the item starting from the end of the vector. For instance, -1 is the last element.


    // Q1 (15 pts) - print overload-set working correctly as used below in all questions
    // Q2 (30 pts) – below and all expressions that can be written with $1, $2, $3 and +, -, *, / works correctly
    auto l1 = (1.1 + $3) * ($1 + $2 / 2.0);
    print("l1(5, 10, 15)", l1(5, 10, 15));


    // Q3 (5 pts) - deduction guide for below line
    // you can change below line to Vector<int>{10, 20, 30} if you want to skip this question auto v = Vector{10, 20, 30};
    // not written Vector<int>{10, 20, 30} especially.
    auto v = Vector{10, 20, 30};

    // Q4 (5 pts) - $1>10 works as expected
    // Q5 (10 pts) - masking of a Vector works auto mask_gt_10 = v[$1 > 10];
    auto mask_gt_10 = v[$1 > 10];


    // Q6 (10 pts) - selection of Vector elements by means of a mask
    auto v_selected = v[mask_gt_10];
    print("v", v, "Mask of $1>10", mask_gt_10, "v_selected", v_selected);


    // Q7 (10 pts) - accessing elements of a Vector in standard way and in reverse direction
    print("First element of v", v[0], "Last Element of v", v[-1]);
    print("v", v);




    // Q8 (only for CS409) (15 pts) - item++ operator works on Vector<int>
    print("v applied with $1++ * 3", v[$1++ * 3]);
    print("v", v); // note that v's items are now incremented by one due to $1++ above



    // Q8 (only for CS509) (15 pts) - ++item operator works on Vector<double>
    // you can change below line to Vector<double>{1.1, 2.2, 3.3} if you don't want points from Q3 auto v2 = Vector{1.1, 2.2, 3.3};
//    auto v2 = Vector{1.1, 2.2, 3.3};
//    print("v2", v2);
//    print("v2 applied with ++$1 - 1", v2[++$1 - 1]);
//    print("v2", v2); // note that v's items are now incremented by one due to $1++ above
//    return 0;
}
