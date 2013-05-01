#include <iostream>
using namespace std;
class EleBase {
 public:
    virtual ~EleBase()
    {
        cout << "call ~EleBase() destructor\n";
    }
    int test;
};

class Ele: public EleBase
{
 public:
    ~Ele()
    {
        cout << "call ~Ele() destructor\n";
    }
    int test2;
    int test3;
    int test4;
};

void clean_elebase(EleBase ary[], int num)
{
    for(int i = 0; i < num; i++) {
        cout << ary[i].test << endl;
    }
//    delete [] ary;
}

int main(int argc, char *argv[])
{
    Ele *ary = new Ele[5];
    EleBase *base = ary;
    delete []base;
//    clean_elebase(ary, 5);
    return 0;
}
