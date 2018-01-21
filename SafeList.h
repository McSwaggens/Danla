//
// Created by daniel on 1/19/2018.
//

#pragma once

#include <vector>
#include <algorithm>

template<typename T>
class SafeList
{
private:
public:
	std::vector<T> addStack;
	std::vector<T> removeStack;
	std::vector<T> values;
	
	SafeList ();
	SafeList (std::vector<T> _values);
	
	void Add (T t);
	void Remove (T t);
	
	void Sort ();
};

template<typename T>
SafeList<T>::SafeList ()
{
}

template<typename T>
SafeList<T>::SafeList (std::vector<T> _values)
{
	values = _values;
}

template<typename T>
void SafeList<T>::Add (T t)
{
	addStack.push_back(t);
}

template<typename T>
void SafeList<T>::Remove (T t)
{
	removeStack.push_back (t);
}

template<typename T>
void SafeList<T>::Sort ()
{
	if (addStack.size() > 0) // Add
	{
		values.insert(values.end(), addStack.begin(), addStack.end());
		
		addStack.clear();
	}
	
	
	if (removeStack.size()) // Remove
	{
		for (auto element : removeStack)
		{
			typename std::vector<T>::iterator position = std::find(values.begin(), values.end(), element);
			
			if (position != values.end())
			{
				values.erase(position);
			}
		}
		
		removeStack.clear();
	}
}
