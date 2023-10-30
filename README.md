# Vector-Class
Implementation of a self written Template Vector class with Iterators, like the standart template library vector class from C++. 

Unfortunantely the Vector does not contain every single functionallity the std::vector container includes. 

const_iterator ≠ constant iterator 
-> rather, a const iterator provides a constant reference to the references value. 
That means that the dereference operation (operator*) only provides read access to the in the vector safed element.

Keep in mind that its nearly impossible to reach the efficiency of the STL Container with self implementation! 
