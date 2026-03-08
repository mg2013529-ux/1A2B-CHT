#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char data[5];
} Candidate;

Candidate pool[5040];
int pool_size;

void get_score(const char *guess, const char *ans, int *A, int *B) {
    int a = 0, common = 0;
    int g_cnt[10] = {0}, a_cnt[10] = {0};
    for (int i = 0; i < 4; i++) {
        if (guess[i] == ans[i]) a++;
        g_cnt[guess[i] - '0']++;
        a_cnt[ans[i] - '0']++;
    }
    for (int i = 0; i < 10; i++) {
        common += (g_cnt[i] < a_cnt[i]) ? g_cnt[i] : a_cnt[i];
    }
    *A = a;
    *B = common - a;
}

void generate_pool() {
    char digits[] = "0123456789";
    pool_size = 0;
    for (int i0 = 0; i0 < 10; i0++) {
        for (int i1 = 0; i1 < 10; i1++) {
            if (i1 == i0) continue;
            for (int i2 = 0; i2 < 10; i2++) {
                if (i2 == i0 || i2 == i1) continue;
                for (int i3 = 0; i3 < 10; i3++) {
                    if (i3 == i0 || i3 == i1 || i3 == i2) continue;
                    Candidate c;
                    c.data[0] = digits[i0];
                    c.data[1] = digits[i1];
                    c.data[2] = digits[i2];
                    c.data[3] = digits[i3];
                    c.data[4] = '\0';
                    pool[pool_size++] = c;
                }
            }
        }
    }
}

void filter_pool(const char *guess, int A, int B) {
    int new_size = 0;
    for (int i = 0; i < pool_size; i++) {
        int a, b;
        get_score(guess, pool[i].data, &a, &b);
        if (a == A && b == B) {
            pool[new_size++] = pool[i];
        }
    }
    pool_size = new_size;
}

void auto_1a2b() {
    generate_pool();
    while (pool_size > 0) {
        char guess[5];
        strcpy(guess, pool[0].data);
        printf("%s\n", guess);

        char res[10];
        if (!fgets(res, sizeof(res), stdin)) {
            break;
        }

        int len = strlen(res);
        while (len > 0 && (res[len-1] == '\n' || res[len-1] == '\r')) {
            res[--len] = 0;
        }

        if (strlen(res) < 3) {
            continue;
        }

        int A = res[0] - '0';
        int B = res[2] - '0';

        if (A < 0 || A > 4 || B < 0 || B > 4 || A + B > 4) {
            continue;
        }

        if (A == 4) {
            return;
        }

        filter_pool(guess, A, B);
    }
}

int main() {
    auto_1a2b();
    return 0;
}
