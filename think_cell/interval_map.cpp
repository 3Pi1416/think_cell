#include <map>

template<typename K, typename V>

class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;


public:
	std::map<K, V> m_map;
	// constructor associates whole range of K with val
	interval_map(V const& val)
		: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, V const& val) {
		if (!(keyBegin < keyEnd))
		{
			return;
		}

		if (this->m_map.size() == 0) {
			if (val == this->m_valBegin) {
				return;
			}
			this->m_map.insert_or_assign(keyBegin, val);
			this->m_map.insert_or_assign(keyEnd, this->m_valBegin);
			return;
		}


		typename std::map<K, V>::iterator upperIterator = this->m_map.upper_bound(keyEnd);

		V oldEndValue = m_valBegin;

		if (upperIterator != this->m_map.end()) {
			oldEndValue = upperIterator->second;
		}
		--upperIterator;

		if (upperIterator != this->m_map.end() && (!(keyBegin < upperIterator->first) && !(upperIterator->first < keyBegin ))) {
			//if  == with the end of another
			this->m_map.insert_or_assign(keyEnd, upperIterator->second);
			K toDeleteIfSameVal = upperIterator->first;

			--upperIterator;
			if (upperIterator != this->m_map.end() && upperIterator->second == val) {
				this->m_map.erase(toDeleteIfSameVal);
				return;
			}

			
		}



		if (upperIterator != this->m_map.end() && keyBegin < upperIterator->first) {

			if (upperIterator->second == val) {
				V todelete = upperIterator->first;
				--upperIterator;
				this->m_map.erase(todelete);
			}
			else {
				this->m_map.insert_or_assign(keyEnd, upperIterator->second);
			}


			while (upperIterator != this->m_map.end() && keyBegin < upperIterator->first) {
				//clean inside the interval and find the other side 
				V todelete = upperIterator->first;
				--upperIterator;
				this->m_map.erase(todelete);
			}

			if ((upperIterator == this->m_map.end() && (val == m_valBegin)) ||
				upperIterator != this->m_map.end() && upperIterator->second == val) {
				//case when loop until the end and  found that m_valBegin == val
				//or when the val == the val before the interval
				return;
			}

		}
		else if (upperIterator != this->m_map.end() && upperIterator->second == val) {
			//We are inside the same value
			return;
		}
		else {
			this->m_map.insert_or_assign(keyEnd, oldEndValue);
		}

		//inside another value 
		if (upperIterator == this->m_map.end() && (val == m_valBegin))
		{
			return;
		}
		this->m_map.insert_or_assign(keyBegin, val);


	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		auto it = m_map.upper_bound(key);
		if (it == m_map.begin()) {
			return m_valBegin;
		}
		else {
			return (--it)->second;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.