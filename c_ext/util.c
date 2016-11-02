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
