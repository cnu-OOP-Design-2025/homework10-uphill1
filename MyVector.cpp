#ifdef MYVECTOR_IMPLEMENTATION

template<typename T>
void MyVector<T>::ensure_capacity(size_t min_capacity) {
    if (cap >= min_capacity) {
        return;
    }

    size_t new_cap = cap == 0 ? 1 : cap;
    while (new_cap<min_capacity) {
        new_cap*= 2;
    }

    T* new_data= new T[new_cap];
    for (size_t i = 0;i < length; i++) {
        new_data[i] =data[i];
    }
    delete[] data;
    data =new_data;
    cap= new_cap;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other): data(nullptr), cap(other.cap), length(other.length) {
    if (cap != 0) {
        data =new T[cap];
        for(size_t i = 0;i <length; i++) {
            data[i] = other.data[i];
        }
    }
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept: data(other.data), cap(other.cap), length(other.length) {
    other.data =nullptr;
    other.cap =0;
    other.length =0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this ==&other) {
        return *this;
    }

    T* new_data = nullptr;
    if (other.cap!= 0) {
        new_data = new T[other.cap];
        for (size_t i = 0;i <other.length;i++) {
            new_data[i] =other.data[i];
        }
    }
    delete[] data;
    data = new_data;
    cap =other.cap;
    length =other.length;
    return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if(this ==&other) {
        return *this;
    }

    delete[] data;
    data = other.data;
    cap =other.cap;
    length = other.length;

    other.data =nullptr;
    other.cap =0;
    other.length =0;
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& val) {
    ensure_capacity(length + 1);
    data[length++] =val;
}

template<typename T>
void MyVector<T>::pop_back() {
    if (length==0) {
        throw std::out_of_range("pop_back on empty vector");
    }
    length-=1;
}

template<typename T>
size_t MyVector<T>::size()const{
    return length;
}

template<typename T>
T& MyVector<T>::operator[](int i){
    return data[i];
}
template<typename T>
bool MyVector<T>::operator==(const MyVector& other) const {
    if(length !=other.length) {
        return false;
    }
    for (size_t i = 0;i<length;i++) {
        if (!(data[i]==other.data[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector& other)const{
    return !(*this == other);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector& other) const {
    size_t min_len = length < other.length ? length : other.length;
    for (size_t i = 0;i < min_len; i++) {
        if (data[i]<other.data[i]) {
            return true;
        }
        if (other.data[i]<data[i]) {
            return false;
        }
    }
    return length <other.length;
}
template<typename T>
bool MyVector<T>::operator>(const MyVector& other)const {
    return other<*this;
}
template<typename T>
bool MyVector<T>::operator<=(const MyVector& other)const {
    return !(other < *this);
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector& other)const {
    return !(*this<other);
}

// Iterator definitions
template<typename T>
T& MyVector<T>::Iterator::operator*() {
    return *ptr;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++() {
    ++ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--() {
    --ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(int n) const {
    if(ptr == nullptr){
        return Iterator(nullptr);
    }
    return Iterator(ptr + n);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator-(int n) const {
    if(ptr== nullptr) {
        return Iterator(nullptr);
    }
    return Iterator(ptr - n);
}

template<typename T>
bool MyVector<T>::Iterator::operator==(const Iterator& other) const {
    return ptr== other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator& other) const {
    return ptr!= other.ptr;
}
template<typename T>
int MyVector<T>::Iterator::operator-(const Iterator& other) const {
    if (ptr == nullptr|| other.ptr == nullptr) {
        return ptr== other.ptr ? 0 : 0;
    }
    return static_cast<int>(ptr - other.ptr);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
    if (length ==0) {
        return cap== 0 ? Iterator(nullptr):Iterator(data);
    }
    return Iterator(data);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() {
    if (length ==0) {
        return cap== 0 ? Iterator(nullptr):Iterator(data);
    }
    return Iterator(data + length);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator pos, const T& value) {
    size_t index = 0;
    if (length != 0){
        Iterator first = begin();
        index = static_cast<size_t>(pos - first);
    }

    if (index>length) {
        throw std::out_of_range("insert position out of range");
    }

    ensure_capacity(length + 1);
    for (size_t i =length; i >index; i--) {
        data[i] =data[i-1];
    }
    data[index] = value;
    length++;
    return Iterator(data+index);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator pos) {
    if (length ==0) {
        throw std::out_of_range("erase on empty vector");
    }

    size_t index =static_cast<size_t>(pos - begin());
    if (index >=length) {
        throw std::out_of_range("erase position out of range");
    }

    for (size_t i = index;i + 1 < length; i++) {
        data[i] = data[i +1];
    }
    length--;
    return Iterator(index <length ?data + index:data + length);
}

template<typename T>
void MyVector<T>::clear() {
    length =0;
}

template<typename T>
T& MyVector<T>::at(size_t i) {
    if (i >=length) {
        throw std::out_of_range("index out of range");
    }
    return data[i];
}

template<typename T>
T& MyVector<T>::front() {
    if (length== 0) {
        throw std::out_of_range("front on empty vector");
    }
    return data[0];
}

template<typename T>
T& MyVector<T>::back() {
    if (length== 0) {
        throw std::out_of_range("back on empty vector");
    }
    return data[length - 1];
}

template<typename T>
size_t MyVector<T>::capacity()const {
    return cap;
}

template<typename T>
bool MyVector<T>::empty()const{
    return length == 0;
}

#endif
