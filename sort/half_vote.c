
/*
 *@return >= 0 valid
   < 0 invalid
*/
int half_vote(int ary[], int n)
{
    if(n < 1) {
        return -1;
    }
    if(n == 1) {
        return 0;
    }
    int win = -1;
    int count = 0;
    int walk = 0;
    for(walk = 0; walk < n; walk+= 2) {
        if(count == 0 && ary[walk] == ary[walk+1]) {
            win = walk;
            count = 2;
        } else if(count > 0 && ary[walk] == ary[walk+1]) {
            if(ary[win] != ary[walk]) {
                count -= 2;
            } else {
                count += 2;
            }
        }
    }
    if(walk != n -1) {
        if(count == 2) {
            if(ary[win] != ary[n-1]) {
                return -1;
            } else {
                return win;
            }
        } else if(count < 2) {
            return n - 1;
        } else {
            return win;
        }
    } else if(count > 0) {
        return win;
    }
    return -1;
}
