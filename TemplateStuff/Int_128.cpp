// int128 bit for numbers larger than 1e18. Will support numbers till 1e36
// Comment out everything related to PBDS while using this
// Put all the code in the same order


// Typedef to ell
typedef __int128 ell;

// For printing
std::ostream&
operator<<( std::ostream& dest, __int128_t value ) {
	std::ostream::sentry s( dest );
	if ( s ) {
		__uint128_t tmp = value < 0 ? -value : value; char buffer[ 128 ];
		char* d = std::end( buffer );
		do {	-- d; *d = "0123456789"[ tmp % 10 ]; tmp /= 10;} while ( tmp != 0 );
		if ( value < 0 ) {-- d; *d = '-';}
		int len = std::end( buffer ) - d;
		if ( dest.rdbuf()->sputn( d, len ) != len ) {dest.setstate( std::ios_base::badbit );}
	}
	return dest;
}

// For reading _int128 to_read = read()
__int128 read() {
	__int128 x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}

// For debugging
void _print(ell t) {cerr << t;}
