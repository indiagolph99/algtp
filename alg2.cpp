#include <iostream>

int n = 0;
int m = 0;
int *a = nullptr;
int *b = nullptr;

std::cin >> n >> m;
a = new int[n];
b = new int[b];
assert((a != NULL) && (b != NULL));
assert(n > m);
int max = 0;
for (int i = 0; i < n; i++) {
    std::cin >> a[i];
}

for (int i = 0; i < m; i++) {
    std::cin >> b[i];
}
