#pragma once

#include <initializer_list>
#include <cstddef>
#include <stdexcept>


template<typename T>
class MyVector {
    T* data;            // 동적 배열을 가리키는 포인터
    size_t cap;         // 현재 할당된 배열 크기
    size_t length;      // 실제 저장된 요소 개수    

    void ensure_capacity(size_t min_capacity);
public:

    MyVector(std::initializer_list<T> init): data(nullptr), cap(init.size()), length(init.size()) {
        if (cap != 0) {
            data = new T[cap];
            size_t i = 0;
            for (const auto& val : init) {
                data[i++] = val;
            }
        }
    }

    MyVector(): data(nullptr), length(0), cap(0) {}
    ~MyVector() { delete[] data; }

    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;

    void push_back(const T& val);   // Vector 마지막에 항목을 추가하는 함수 구현, 필요시 벡터 크기 증가
    void pop_back();                // Vector의 마지막 항목을 제거하는 함수 구현
    size_t size() const;            // Vecotr에 있는 항목 개수(length)를 리턴하는 함수 구현
    T& operator[](int i) ;          // [] 연산자 구현

    bool operator==(const MyVector& other) const;

    bool operator!=(const MyVector& other) const;

    bool operator<(const MyVector& other) const;

    bool operator>(const MyVector& other) const;

    bool operator<=(const MyVector& other) const;

    bool operator>=(const MyVector& other) const;


    // Vector에 대한 반복자
    class Iterator {
        T* ptr;         // 항목에 대한 포인터
    public:
        Iterator(T* p = nullptr): ptr(p) {}

        T& operator*(); // 역참조 연산자 구현 

        Iterator& operator++();   //전위 증가 연산자 구현
        Iterator& operator--();   //전위 감소 연산자 구현
        Iterator operator+(int n) const ;   // 산술 연산자 구현
        Iterator operator-(int n) const ;   // 산술 연산자 구현

        bool operator==(const Iterator& other) const ;
        bool operator!=(const Iterator& other) const ;

        int operator-(const Iterator& other) const ;
    };

    // 첫번째 항목에 대한 iterator 리턴 함수 구현
    Iterator begin() ;
    // 마지막 항목에 대한 iterator 리턴 함수 구현 
    Iterator end() ;


    // insert: 지정 위치에 요소 삽입 함수 구현
    Iterator insert(Iterator pos, const T& value);

    // erase: 지정 위치 요소 제거 함수 구현
    Iterator erase(Iterator pos);

    // clear: 모든 요소 제거 함수 구현 (size = 0 초기화)
    void clear() ;

    // at: 범위 체크 후, i번째 항목 접근 함수 구현
    T& at(size_t i); 

    // front/back
    T& front() ;    // 첫번째 항목 리턴 함수 구현
    T& back() ;     // 마지막 항목 리턴 함수 구현

    // capacity
    size_t capacity() const ;   // cap 값 리턴하는 함수 구현

    // empty
    bool empty() const ;    // 현재 vector가 empty인지 확인하는 함수 구현

};

#define MYVECTOR_IMPLEMENTATION
#include "MyVector.cpp"
#undef MYVECTOR_IMPLEMENTATION
