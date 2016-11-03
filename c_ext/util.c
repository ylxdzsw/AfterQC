int min3(int a, int b, int c) {
    return a < b ? a < c ? a : c
                 : b < c ? b : c;
}

char* reverseComplement(int len, char* origin) {
    int i;
    char* rev = (char*) malloc(len+1);
    for (i=0; i<len; i++) {
        switch (origin[len-i-1]) {
            case 'A': rev[i]='T'; break;
            case 'T': rev[i]='A'; break;
            case 'C': rev[i]='G'; break;
            case 'G': rev[i]='C'; break;

            case 'a': rev[i]='t'; break;
            case 't': rev[i]='a'; break;
            case 'c': rev[i]='g'; break;
            case 'g': rev[i]='c'; break;

            case 'N': rev[i]='N'; break;
            case '\n': rev[i]='\n'; break;

            default: rev[i]='N';
        }
    }
    rev[len] = '\0';
    return rev;
}

int editDistance(int len1, char* s1, int len2, char* s2) {
    int m = len1 + 1;
    int n = len2 + 1;
    int i, j, cost;

    int* tbl = (int*) malloc(m * n * sizeof(int));
    for (i=0; i<m; i++) tbl[i*n] = i;
    for (j=0; j<n; j++) tbl[j] = j;
    for (i=1; i<m; i++) {
        for (j=1; j<n; j++) {
            cost = s1[i-1] != s2[j-1];
            tbl[i*n+j] = min3(tbl[i*n+j-1]+1, tbl[i*n-n+j]+1, tbl[i*n-n+j-1]+cost);
        }
    }

    return tbl[m*n-1];
}
