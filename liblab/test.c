#include <stdlib.h>

#include "liba/api_a.h"
#include "libb/api_b.h"


int main()
{
    a_test_conf_file(NULL);
    b_test_conf_file(0, NULL);
    return 0;
}
