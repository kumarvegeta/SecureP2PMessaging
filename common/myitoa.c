

//Function to convert my integer key into a string - myitoa()

void myitoa(long long int n, char s[]) {
    long long int i, sign;
    sign = n;
    
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ( n /= 10 );
    if (sign < 0)
        s[i++] = '-';
    
    s[i] = '\0';
    reverse(s);
}

//Used by myitoa()

void reverse(char s[]) {
    long long int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}



