ell expo1(ell a, ell b, ell mod) {
    ell res = 1; 
    while (b > 0) {
        if (b & 1)
            res = (res * a) % mod; 
        a = (a * a) % mod; 
        b = b >> 1;
    } 
    return res;
}

bool check_composite(ell n, ell a, ell d, ell s) {
    ell x = expo1(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (x * x) % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(ell n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}