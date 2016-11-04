int min3(int a, int b, int c) {
    return a < b ? a < c ? a : c
                 : b < c ? b : c;
}

void min_with_index3(int a, int b, int c, int* min, char* index) {
    *min   = a;
    *index = 1;

    if (*min > b) {
        *min   = b;
        *index = 2;
    }

    if (*min > c) {
        *min   = c;
        *index = 3;
    }
}


char* reverseComplement(int len, char* origin) {
    int i;
    char* rev = (char*) malloc(len+1); // hope python interpreter will gc it automatically
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

    return cost = tbl[m*n-1], free(tbl), cost;
}

/*
* An implementation of a variant of Needleman-Wunsch algorithm as described [here](http://www.stanford.edu/class/cs262/presentations/lecture2.pdf)
*
* s1 and s2 should both 5' -> 3' (you may need calculate the reverse complement of R2)
* ret contains at least 3 element: offset, length and edit_distance
*/
void overlap(int len1, char* s1, int len2, char* s2, int* ret) {
    int m = len1 + 1;
    int n = len2 + 1;
    int i, j, cost, opt1, opt2;

    int*  F = (int*)  malloc(m * n * sizeof(int));
    char* P = (char*) malloc(m * n);

    if (len1 < 10 || len2 < 10) {
        ret[0] = ret[1] = ret[2] = 0;
        return;
    }

    for (i=0; i<m; i++) F[i*n] = 0;
    for (j=0; j<n; j++) F[j]   = 0;

    for (i=0; i<m; i++) P[i*n] = 0;
    for (j=0; j<n; j++) P[j]   = 0;

    for (i=1; i<m; i++) {
        for (j=1; j<n; j++) {
            cost = s1[i-1] != s2[j-1];
            min_with_index3(F[i*n-n+j-1]+cost, F[i*n+j-1]+1, F[i*n-n+j]+1, F+i*n+j, P+i*n+j);
        }
    }

    cost = m + n; // minimum distance

    for (i=10; i<m; i++) { // ignore too short alignments < 10
        if (cost >= F[i*n+n-1]) {
            cost = F[i*n+n-1];
            opt1 = i;
            opt2 = n-1;
        }
    }
    for (j=10; j<n; j++) {
        if (cost >= F[m*n-n+j]) {
            cost = F[m*n-n+j];
            opt1 = m-1;
            opt2 = j;
        }
    }

    i = opt1;
    j = opt2;
    ret[1] = 0;

    while (P[i*n+j] != 0) {
        ret[1] += 1;

        switch (P[i*n+j]) {
            case 1:
                i -= 1;
                j -= 1;
                break;
            case 2:
                j -= 1;
                break;
            case 3:
                i -= 1;
                break;
        }
    }

    ret[0] = i >= 0 ? i : -j;
    ret[2] = cost;

    free(F);
    free(P);
}
