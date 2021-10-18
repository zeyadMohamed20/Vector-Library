/*
**********************************************************************************************************
@file      vector_z.cpp
@author    Zeyad Mohamed Abd ElHamid
@brief     This file contains the implementation of all vector_z template class
*********************************************************************************************************
*/
#include "vector_z.h"
#include<iostream>
using namespace std;
#define OUT_OF_RANGE_ERROR 139 //Out of range exit code
#define FAILURE_ERROR 1 //failure exit code

template<class T>
void vector_z<T>::ignore(const T&) {} //To remove warning unused variable in exception handling

template<class T>
void vector_z<T>::empty_vector_exception() //exception is thrown when we try to access empty vector 
{
	try
	{
		if (MaxIndex < 0)
		{
			throw MaxIndex;
		}
	}
	catch (int MaxIndex)
	{
		ignore(MaxIndex);
		cout << "Exception error: Try to acess empty vector";
		exit(FAILURE_ERROR);
	}
}

template<class T>
void vector_z<T>::out_of_range_exception(int Index) //exception is thrown when we try to acess element out of the
{                                                  // vector range
	try
	{
		if (Index > MaxIndex)
		{
			throw Index;
		}
	}
	catch (int Index)
	{
		ignore(Index);
		cout << "Exception error: Vector subscript is out of range";
		exit(OUT_OF_RANGE_ERROR);
	}
}

template<class T>
void vector_z<T>::calc_capacity()
{
	if ((Size == 1) || (Size == 2))
	{
		Capacity = Size;
	}
	else
	{
		Capacity = (size_t)(1.5 * (Size - 1));
	}
}

template<class T>
void vector_z<T>::copy(T* POld, T* PNew)
{
	for (int i = 0; i <= MaxIndex; i++)
	{
		PNew[i] = POld[i];
	}
}

template<class T>
void vector_z<T>::move_block(T* PNew)
{
	copy(P, PNew);
	std::swap(P, PNew);
	delete[] PNew;
}

template<class T>
void vector_z<T>::allocate_block(size_t Capacity, T Val)
{
	T* PNew{ nullptr };
	if (Capacity > 0)
	{
		PNew = new T[Capacity]{ Val };
	}
	else
	{
		PNew = new T[Capacity];
	}
	move_block(PNew);
}

template<class T>
void vector_z<T>::push_back(T Element)
{
	Size++;
	if (Size > Capacity || Size == 1) //Size = 1 when we clear vector so pointer will refer to null 
	{                                //then push_back and size < capacity but pointer lost its address  
		calc_capacity();            //so reallocation is needed
		allocate_block(Capacity);
	}
	MaxIndex = Size - 1;
	P[MaxIndex] = Element;
}

template<class T>
void vector_z<T>::pop_back()
{
	empty_vector_exception();
	Size--;
	MaxIndex = Size - 1;
}

template<class T>
size_t vector_z<T>::size()
{
	return Size;
}


template<class T>
size_t vector_z<T>::capacity()
{
	return Capacity;
}

template<class T>
T& vector_z<T>::operator[](int Index) // for non-constant objects
{
	out_of_range_exception(Index);
	return P[Index]; // it returns L-value to be allowed for setting and getting values
}

template<class T>
const T& vector_z<T>::operator[](int Index) const //for constant objects
{
	out_of_range_exception(Index);
	return P[Index]; // it returns constant L-value to be allowed for getting values only
}

template<class T>
void vector_z<T>::resize(size_t Size, T Val)
{
	this->Size = Size;
	if (Size > Capacity)
	{
		Capacity = Size;
		allocate_block(Capacity, Val);
	}
	MaxIndex = this->Size - 1;
}

template<class T>
T& vector_z<T>::at(int Index) //for non-constant objects
{
	return operator[](Index); // it returns L-value to be allowed for setting and getting values
}

template<class T>
const T& vector_z<T>::at(int Index) const //for constant objects
{
	return operator[](Index); // it returns constant L-value to be allowed for getting values only
}

template<class T>
T vector_z<T>::front()
{
	empty_vector_exception();
	return P[0];
}

template<class T>
T vector_z<T>::back()
{
	empty_vector_exception();
	return P[MaxIndex];
}

template<class T>
bool vector_z<T>::empty()
{
	if (Size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
void vector_z<T>::clear()
{
	Size = 0;
	MaxIndex = Size - 1;
	P = nullptr;
}

template<class T>
T* vector_z<T>::data()
{
	return P;
}

template<class T>
void vector_z<T>::swap(vector_z<T>& SecondVecor)
{
	//std to diffrentiation swap method in object from swap standard function as we can't overload standard function
	std::swap(P, SecondVecor.P);
	std::swap(Size, SecondVecor.Size);
	std::swap(Capacity, SecondVecor.Capacity);
	std::swap(MaxIndex, SecondVecor.MaxIndex);
}

template<class T>
void vector_z<T>::shrink_to_fit() //method used to shrink vector so capacity = size
{
	Capacity = Size;
	allocate_block(Capacity);
}

template<class T>
void vector_z<T>::emplace_back(T Element) //behave like push_backfunction
{
	this->push_back(Element);
}

template<class T>
void vector_z<T>::reserve(size_t Capacity) // method used to specify capacity of vector 
{
	if (Capacity > this->Capacity)
	{
		this->Capacity = Capacity;
	}
}

template<class T>
vector_z<T>::vector_z(size_t Size, T Val) :MaxIndex(Size - 1), Capacity(Size), P(Size > 0 ? new T[Size] : nullptr)
{
	this->Size = Size;
	for (size_t i = 0; i < Size; i++)
	{
		this->operator[](i) = Val;
	}
}

template<class T>
vector_z<T>::~vector_z()
{
	delete[] P;
}