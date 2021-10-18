/*
**********************************************************************************************************
@file      vector_z.h
@author    Zeyad Mohamed Abd ElHamid
@brief     This file contains the headers vector_z methods and its attributes
*********************************************************************************************************
*/
#pragma once
using namespace std;
template<class T>
class vector_z
{
private:
	size_t Size;
	int MaxIndex;
	size_t Capacity;
	T* P;
public:
	void push_back(T Element);
	void pop_back();
	size_t size();
	void resize(size_t Size, T Val = 0);
	size_t capacity();
	T& operator[](int Index);
	const T& operator[](int Index) const;
	T& at(int Index);
	const T& at(int Index) const;
	T front();
	T back();
	bool empty();
	void clear();
	T* data();
	void swap(vector_z<T>& SecondVecor);
	void shrink_to_fit();
	void emplace_back(T Element);
	void reserve(size_t Capacity);
	vector_z(size_t Size = 0, T Val = 0);
	~vector_z();
private:
	void ignore(const T&);
	void out_of_range_exception(int Index);
	void empty_vector_exception();
	void calc_capacity();
	void copy(T* POld, T* PNew);
	void move_block(T* PNew);
	void allocate_block(size_t Capacity, T Val = 0);
};
