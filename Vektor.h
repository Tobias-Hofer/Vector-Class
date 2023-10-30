#ifndef CLASS_H
#define CLASS_H

#include<iostream>
#include<stdexcept>


template<typename T>
class Vector {
private:
 size_t sz; 					//Elemente im Vektor 
 size_t max_sz; 				//Kapazität des Vektors
 T* values; 					//Zeiger auf Eintrag
public:
class ConstIterator;
class Iterator;
using value_type = T;
using size_type = std::size_t;
using difference_type = std::ptrdiff_t;
using reference = value_type&;
using const_reference = const value_type&;
using pointer = value_type*;
using const_pointer = const value_type*;
using iterator = Vector::Iterator;
using const_iterator = Vector::ConstIterator;
public:
 
 Vector() : sz{0}, max_sz{0}, values{new value_type[max_sz]} {  								
 }
 
 Vector(const Vector& v) :  sz{v.sz}, max_sz{v.max_sz} {
    									
  values = new value_type[v.max_sz];
  for(size_t i{0}; i<v.sz; i++)
   values[i] = v.values[i];
 }
 
 Vector(size_t n) : sz{0}, max_sz{n}, values{new value_type[max_sz]} {							
 } 
 
 Vector(std::initializer_list<value_type> c) : sz{c.size()}, max_sz{c.size()*2} {				
   
   values = new value_type[max_sz];
    size_t i{0};
     for(const auto& a : c) {
      values[i] = a;
       i++; 
  } 
 }
 
 ~Vector() {																				//
 delete [] values;
 values = nullptr;
 }

 Vector operator=(Vector v) {
  std::swap(sz, v.sz);
  std::swap(max_sz, v.max_sz);
  std::swap(values, v.values);
  return *this;
}

 size_t size() const {
  return sz;
 }
  
 bool empty() const {
  return sz == 0 ? true : false;
 }

 void clear() {
  sz=0;
 }

 void reserve(size_t n) {
   if(max_sz < n) {
    
    pointer help = new value_type[n];
    for(size_t i{0}; i<sz; i++)
     help[i] = values[i];
      max_sz = n;
      delete[] values;
      values = help;
 }
 else
  return;
}

 void shrink_to_fit() {
  max_sz = sz; 
}
 
 
 void push_back(value_type x) {
   if(sz >= max_sz) 
     reserve((max_sz+1)*2);
     
        values[sz++] = x; 
 }
  
 void pop_back() {
  if (sz == 0)
   throw std::runtime_error("Vector is Empty");
    
     sz--;
 }

double& operator[](size_t index) {
 if (index < 0 || sz == 0)
  throw std::runtime_error{"Negative index not allowed"};
 
 if (index >= sz)
  throw std::runtime_error{"no element at this point"};
   
  return values[index];
 }

const double& operator[](size_t index) const {
  if (index < 0 || sz == 0)
   throw std::runtime_error{"negative index not allowed"};
  
  if (index >= sz)
   throw std::runtime_error{"no element at this point"};
   
  return values[index];
 }

size_t capacity() const {
 return max_sz;
 }

  
iterator insert(const_iterator pos, const_reference val) { 
 auto diff = pos-begin();
 if (diff<0 || static_cast<size_type>(diff)>sz)
  throw std::runtime_error("Iterator out of bounds");
 size_type current{static_cast<size_type>(diff )}; 
 if(sz>=max_sz)
  reserve ((max_sz+1)*2); //Achtung Sonderfall , wenn keine Mindestgröße definiert ist
 for(auto i{sz}; i-->current;)
  values[i+1] = values[i]; 
 values[current] = val ;
 ++sz ;
 return iterator{values+current};
}

iterator erase(const_iterator pos) {
 auto diff = pos-begin();
 if (diff<0 || static_cast<size_type>(diff)>=sz)
  throw std::runtime_error("Iterator out of bounds");
 size_type current{static_cast<size_type>(diff)};
 for (auto i{current}; i<sz-1; ++i)
  values[i]=values[i+1]; --sz ;
return iterator{values+current}; 
}

 iterator begin() {
  return iterator(values);
 }

 const_iterator begin() const {
  return const_iterator(values);
 }

 iterator end() {
  return iterator(values+sz);
 }

 const_iterator end() const {
  return const_iterator(values+sz);
 }

 std::ostream& print(std::ostream& o) const {
  o << "[";
   for(size_t i{0}; i<sz; i++) {
    o << values[i];
    }
     return o << "]";
 }

class Iterator {
public:
 using value_type = Vector::value_type;
 using reference = Vector::reference;
 using pointer = Vector::pointer;
 using difference_type = Vector::difference_type;
 using iterator_category = std::forward_iterator_tag;
private: 
 value_type* point;
public: 
 Iterator() : point{nullptr} {}		//default constructor
 
 Iterator(pointer ptr) : point{ptr} {}  //ptr constructor

 reference operator*() const {
  return *point;
 }

 pointer operator->() const {
  return point;
 }

 bool operator==(const const_iterator& it) const {    
  return static_cast<const_iterator>(point) == it;
 }

 bool operator!=(const const_iterator& it) const {    
  return static_cast<const_iterator>(point) != it;
 }

 iterator& operator++() {
  point++;
   return *this;
 }
 
 iterator operator++(int) {
  iterator origin = point;
   ++point;
   return origin;
 }

 operator const_iterator() const {
  return const_iterator{point};
 }
 
 };


class ConstIterator {
public:
 using value_type = Vector::value_type;
 using reference = Vector::const_reference;
 using pointer = Vector::const_pointer;
 using difference_type = Vector::difference_type;
 using iterator_category = std::forward_iterator_tag;
private:
 const value_type* point;
public:
 ConstIterator() : point{nullptr} {}			//default const constructor

 ConstIterator(const pointer ptr) : point{ptr} {}	

 reference operator*() const {
  return *point;
 }

 pointer operator->() const {
  return point;
 } 

 bool operator==(const const_iterator& it) const {
  return point == it.point;
 }
 
 bool operator!=(const const_iterator& it) const {
  return point != it.point;
 } 
 
 const_iterator &operator++() {
  point++;
  return *this;
 }
 
 const_iterator operator++(int) {
  const_iterator origin = point;
     ++point;
   return origin; 
 }
 
 friend Vector::difference_type operator-(const Vector::ConstIterator& lop, const Vector::ConstIterator& rop) {
  return lop.point-rop.point;
 }

 };

};
 
 template<typename T>
 std::ostream& operator<<(std::ostream& o, const Vector<T>& v) {
  return v.print(o);
 }

#endif
