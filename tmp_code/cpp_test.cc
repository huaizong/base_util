#include <iostream>
#include <vector>
#include <iterator>
#include<algorithm>

using namespace std;

int test2(void);
int test1(void);
int main()
{
    return test2();
}
int test2(void)
{
    int eles[] = {1, 2, 3};
    const size_t N = sizeof(eles)/sizeof(eles[0]);
    vector<int> vec(eles, eles+N);
    int count = 0;
    do {
        cout << ++count << ": ";
        copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, ", "));
        cout << endl;
    }while(next_permutation(vec.begin(), vec.end()));
    return 0;
}
        
int test1(void)
{
	vector<int> vct;
	vct.push_back(1);
	vct.push_back(2);
	cout << vct.size() << endl;
	for( vector<int>::size_type i= vct.size()-1; i>=0; --i ){
		break;
		cout << vct[i] << endl;
	}
	return 0;
}

