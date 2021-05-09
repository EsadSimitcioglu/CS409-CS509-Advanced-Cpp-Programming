// StudentID: S018039, Name: MUHAMMED ESAD SIMITCIOGLU
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <variant>

using namespace std;

template<typename ...> struct TD;



template<typename T>
struct Mat{

    size_t rows,columns;
    vector<vector<T>> values;

    Mat(int x,int y,T values) : rows(x) , columns(y) ,values(x,vector<T>(y,values)){

    }
    auto& operator[](int item){
        return values[item];
    }

    Mat(const Mat& oldMatrix) : rows(oldMatrix.rows) , columns(oldMatrix.columns) , values(oldMatrix.values) {}

};

template<
    template<typename> typename PrintableType,
    typename T
    >
void print(const PrintableType<T>& printable){
    if constexpr(is_same_v<remove_reference_t<T>,const char*> || is_same_v<remove_reference_t<T>,string>){
        for(auto& row : printable.values){
            for(auto& item : row){
                cout << "\"" << item << "\"" << " ";
             }
             cout << endl;
        }
    }
    else{
        for(auto& row : printable.values){
            for(auto& item : row){
                cout << item << " ";
            }
            cout << endl;
        }
    }
}

template<typename T1,typename T2>
[[nodiscard]]auto transform(T1&& mat_src,T2&& function){
    if constexpr(is_same_v<T1,T1&>){
        cout << "Transforming l-value parameter" << endl;
    }
    else{
        cout << "Transforming r-value parameter" << endl;
    }
    auto T = *mat_src.values.begin()->begin();

    auto transformedMat = Mat(mat_src.rows,mat_src.columns,forward<decltype(function(T))>(function(T)));
    return transformedMat;
}

template<typename T>
concept isInc = requires(T t)
{
    t.values.begin()->begin();
    t.rows;
    t.columns;
    t.values;
    t[t.rows-1][t.columns-1];
    (*t.values.begin()->begin())*2;
};

template<isInc T>
auto inc(T&& mat_src){

    if constexpr(is_same_v<T,T&>)
        cout << "Transforming l-value matrix" << endl;
    else
        cout << "Transforming r-value matrix" << endl;

        auto newMat = transform((mat_src),[](auto&& Mat){
            return Mat;
        });
        newMat = forward<T>(mat_src);

        for(auto&& item : newMat.values)
            for(auto&& item2 : item)
                item2+=1;

        return newMat;
    }


template <typename, typename>                               struct concat;
template <typename... First, typename... Second>            struct concat<tuple<First...>, tuple<Second...>> {  using type = std::tuple<First..., Second...>;};
template<typename T1>                                       struct concat<T1,void>                           { using type =T1;};
template<typename T1>                                       struct concat<void,T1>                           { using type =T1;};


template<typename T1,typename T2>
using concat_t = typename concat<T1, T2>::type;


template<typename ...>                    struct IsIntegral;
template<typename...T>                    struct IsIntegral       { static const bool value = ((IsIntegral<T>::value)&& ...);};
template<typename First>                  struct IsIntegral<First>{ static const bool value = false;};
template<>                                struct IsIntegral<int>  { static const bool value = true; };
template<>                                struct IsIntegral<long> { static const bool value = true; };
template<>                                struct IsIntegral<short>{ static const bool value = true; };
template<>                                struct IsIntegral<char> { static const bool value = true; };


// A String class to hide the underlying details of std::string (i.e. std::basic_string<char, ...>) This shows as "String" when type-debugging, and facilitates
struct String : string { using string::string; };
// The transformer required by Q7 is supplied here
template<typename ...>      struct Transformer;
template<typename T>        struct Transformer<T>           {using type = T; };
template<>                  struct Transformer<char>        {using type = int; };
template<>                  struct Transformer<short>       {using type = int; };
template<>                  struct Transformer<long>        {using type = int; };
template<>                  struct Transformer<double>      {using type = float; };
template<>                  struct Transformer<string>      {using type = String; };



template<typename T_true, typename T_false, bool b>
struct ConditionalType {
    using type = T_false;
};

template<typename T_true, typename T_false>
struct ConditionalType<T_true, T_false, true>
{
    using type = T_true;
};

template<typename T_true, typename T_false, bool b>
using ConditionalType_t = typename ConditionalType<T_true, T_false, b>::type;

template <typename T1>
struct declareType{
    using type = T1;
};



//template <template<typename>  typename ValueTrait, typename First,typename ...Rest> struct filter_type;

//template <template<typename>  typename ValueTrait, typename First,typename ...Rest>
//struct filter_type<ValueTrait, std::tuple<First,Rest...>>
//{


//    using type = concat_t<typeFilter<First>,>;


//};

//template <template<typename>  typename ValueTrait, typename First> struct typeFilter;

//template <template<typename>  typename ValueTrait, typename First>
//struct typeFilter{
//    using type = ConditionalType_t<tuple<E>, void,ValueTrait<E>::value>;
//};




template<template<typename...> typename Condition,
         typename ConditionType = void,
         template<typename...> typename Container,
         typename First,typename ...Rest
         >
static constexpr auto count_types(Container<First,Rest...>){
           if constexpr(Condition<First>::value){
               if constexpr(sizeof... (Rest) == 0)
                   return 1;
               else
                   return 1 + count_types<Condition>(Container<Rest...>{});
           }
           else{
               if constexpr(sizeof... (Rest) == 0)
                   return 0;
               else
                   return count_types<Condition>(Container<Rest...>{});
           }
}



int main()
{
    auto m1 = Mat(2, 3, 9.9); // 2 row, 3 column matrix with double values is initialized to 9.9 for each cell
    print(m1);
    // Q1b - Make below assignment style work (i.e. m1[rowindex][colindex])
    for(size_t i=0; i<m1.rows; ++i) m1[i][i] = 1.1;
    // LIMITATION! For Q1a and Q1b in total, you can use at most 6 semicolon (;) characters // including the struct ending semicolon. More than 6 semicolons, you get zero points. // Q1a - Create a Mat<T> class with a constructor of Mat(rows, cols, initial_value)
    // T is automatically deduced from the initial_value's type
    //CS 409/509 – Advanced C++ Programming - Midterm Project 1 (Spring 2020-21) Page 3 of 4 // Q1c - write a print free-function that prints an instance of Mat<T>
        // if T is string, it puts " around the value, otherwise it directly prints the value print(m1);
        // Q2 - Write a "auto transform(const Mat<T>& mat_src, auto&& func)" free-function // that can take a source matrix and transform its contents globally.
        // At the end it returns the transformed matrix. Original matrix stays untouched.
        // Returned matrix can be of a different type depending on the "func"'s return value. // i.e. Mat<int> after transformation can be Mat<double> for instance.
        auto m2 = transform( Mat{2, 1,
                        map<string, variant<string, double, int>>{ {"pi", 3.14},
                                                                  {"CS", "409/509"},
                                                                  {"year", 2021} }
                    }, []<typename T>(T&& map_) {
                        auto s = string{};
                        for(const auto& [key, value] : map_) {
                            auto value_str = string{}; if(holds_alternative<string>(value))
                                value_str = get<string>(value);
                            else if(holds_alternative<double>(value))
                                value_str = to_string(get<double>(value)); else if(holds_alternative<int>(value))
                                value_str = to_string(get<int>(value)); s += key + ": " + value_str + " ";
                        }
                        return s; });
    print(m1);
    print(m2);
    // Q3a - Write a SINGLE (overloading inc is not allowed) free-function named "inc".
    // writing overloads for inc function will get you zero points
    // This function returns a new Mat<T> whose contents are incremented by 1.
    // It also writes l-value or r-value to the console based on its parameter's situation at the call site.
    // Q3b - Make the SINGLE "inc" function available only for Mat<T> types using concepts // writing overloads for "inc" function will get you zero points
    // For instance, Mat<string> cannot be incremented. Mat<int>, Mat<float>, ... can be incremented.
        print(inc(m1));
        print(inc(Mat(1, 4, 1)));
    // Q4 - Write a concat struct that can concatenate tuples at least as described below // concat omits the void at the end
    // concat concatenates types of two tuples into one tuple
    using T1 = tuple<int, double, float>;
    //TD< concat_t<T1, void> > q4a; // ---> tuple<int, double, float>
    //TD< concat_t<T1, T1> > q4b; // ---> tuple<int, double, float, int, double, float>
    // Q5 - Write IsIntegral value-trait which is similar to std::is_integral. // But your implementation must also accept IsIntegral<> as a valid entry. // i.e. <> means an empty parameter-pack

    //CS 409/509 – Advanced C++ Programming - Midterm Project 1 (Spring 2020-21) Page 4 of 4
    // Q6 - Write "filter_types" type-trait
    // that accepts a value-trait and many types
    // as a value trait you must support at least both of IsIntegral<> and is_integral<void> // a value-trait can be, for instance, IsIntegral that checks if a type is suitable or not // in the end, filter_types struct supplies the types filtered according to the value-trait
    // in its "type" attribute
    // Do not write templated classes in the main() function block. Leave them in the global
    //namespace.
     using TUPLE = tuple<int, float, string, char, short, double, string, double, float>;
    //using TUPLE_INTEGRAL = filter_types_t<IsIntegral<>, TUPLE>; TUPLE_INTEGRAL --> tuple<int, char, short>
      //      TD< TUPLE_INTEGRAL > q6a;
   // using TUPLE_FLOATING = filter_types_t<is_floating_point<void>, TUPLE>; TUPLE_FLOATING --> tuple<float, double, double, float>
     //       TD< TUPLE_FLOATING > q6b;
    // Q7 - Write a "transform_types" type trait
    // that accepts convertion type-trait and many types
    // a type-trait specialized for your scenario is already supplied. Its called
    //"Transformer".
        // in the end, transform_types struct supplies the transformed types according to the type-
      //  trait in its "type" attribute
        // Do not write templated classes in the main() function block. Leave them in the global
        //namespace.
        //using TUPLE_TRANSFORMED = transform_types_t<Transformer<>, TUPLE>;
    // TUPLE_TRANSFORMED --> tuple<int, float, String, int, int, float, String, float, float> // TD< TUPLE_TRANSFORMED > q7a;
    // Q8 - Write a constexpr free-function named count_types
    // when used as shown below it returns the number of types in a tuple that fits to the criterion supplied
    cout << "Number of integral types in TUPLE is " << count_types<IsIntegral>(TUPLE{}) << endl;
    cout << "Number of integral types in TUPLE is " << count_types<is_integral>(TUPLE{}) << endl;
    cout << "Number of floating types in TUPLE is " << count_types<is_floating_point>(TUPLE{}) << endl;
    return 0;
}

