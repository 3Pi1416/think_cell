
#include "test_interval_map.h"
#include "interval_map.cpp"
#include <assert.h>

using namespace std;


int main() {
	test3();
}



void test1() {

	interval_map<int, char>  intervalMap = interval_map<int, char>('A');
	intervalMap.assign(1, 3, 'B');
	intervalMap.assign(3, 5, 'A');

	cout << intervalMap[-1] <<endl;
	cout << intervalMap[2] << endl;
	cout << intervalMap[3] << endl;

}


void test2() {

	interval_map<int, char>  intervalMap = interval_map<int, char>('A');
	intervalMap.assign(1, 5, 'B');
	intervalMap.assign(5, 9, 'D');
	intervalMap.assign(3, 6, 'C');

	cout << intervalMap[-1] << endl;
	cout << intervalMap[1] << endl;
	cout << intervalMap[4] << endl;
	cout << intervalMap[5] << endl;
	cout << intervalMap[7] << endl;
	cout << intervalMap[10] << endl;
	return; 

}


void test3() {

	interval_map<int, char>  intervalMap = interval_map<int, char>('A');
	intervalMap.assign(1, 5, 'B');
	assert(intervalMap[-1] == 'A');
	assert(intervalMap[1] == 'B');
	assert(intervalMap[5] == 'A');

	intervalMap.assign(5, 9, 'D');
	assert(intervalMap[1] == 'B');
	assert(intervalMap[5] == 'D');
	assert(intervalMap[9] == 'A');


	intervalMap.assign(3, 6, 'C');
	assert(intervalMap[4] == 'C');
	assert(intervalMap[6] == 'D');
	assert(intervalMap[9] == 'A');


	intervalMap.assign(3, 12, 'E');
	assert(intervalMap[4] == 'E');
	assert(intervalMap[6] == 'E');
	assert(intervalMap[9] == 'E');
	assert(intervalMap[14] == 'A');

	//test aucun changement
	intervalMap.assign(14, 12, 'E');
	assert(intervalMap[13] == 'A');


	//tests canonique
	intervalMap = interval_map<int, char>('A');
	intervalMap.assign(3, 12, 'A');
	assert(intervalMap.m_map.size() == 0);
	intervalMap.assign(4, 10, 'C');
	intervalMap.assign(10, 12, 'C');
	assert(intervalMap.m_map.size() == 2);
	intervalMap.assign(6, 10, 'C');
	assert(intervalMap.m_map.size() == 2);
	intervalMap.assign(3, 8, 'C');
	assert(intervalMap.m_map.size() == 2);
	intervalMap.assign(2, 24, 'C');
	assert(intervalMap.m_map.size() == 2);

}