int jump_table(char c) {
    switch (c) {
        case 'A': return 0;
        case 'T': return 1;
        case 'C': return 2;
        case 'G': return 3;

        case 'a': return 4;
        case 't': return 5;
        case 'c': return 6;
        case 'g': return 7;

        case 'N': return 8;
        default: return -1;
    }
}

char hasPolyX(int len, char* seq, int maxPoly, int mismatch) {
    int table[9] = { 0 };
    int i, pos;
    char frontbase, tailbase;

    if (len < maxPoly)
        return '\0';

    for (i=0; i<len; i++) {
        frontbase = seq[i];
        pos = jump_table(frontbase);

        if (pos == -1)
            return '\0';

        if (i >= maxPoly) {
            tailbase = seq[i - maxPoly];
            table[jump_table(tailbase)] -= 1;
        }

        table[pos] += 1;

        if (table[pos] >= maxPoly - mismatch)
            return frontbase;
    }

    return '\0';
}
