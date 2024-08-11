#include <iostream>

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current = 1;
    long long sum = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}
long long get_pisano_period(long long m) {

    long long a = 0, b = 1, c = a + b;
    for (int i = 0; i < m * m; i++) {
        c = (a + b) % m;
        a = b;
        b = c;
        if (a == 0 && b == 1)
            return i + 1;
    }
}

//Returns n-th term Fibonacci number modulo m
long long get_fibonacci_huge_optimized(long long n, long long m) {
    if (n <= 1)
        return n;

    long long pisano_period = get_pisano_period(m);
    long long reduced_term = n % pisano_period;
    if (reduced_term == 0) return 0;

    long long previous = 0;
    long long current = 1;
    for (long long i = 0; i < reduced_term - 1; ++i) {
        long long temp = previous;
        previous = current;
        current = (temp + current) % m;
    }

    return current % m;
}

int fibonacci_sum_squares_fast(long long n) {
    if (n <= 1)
        return n;
    int r1 = (int)(n % 60);
    int r2 = (int)((n + 1) % 60);
    int last = get_fibonacci_huge_optimized(r1, 10) * get_fibonacci_huge_optimized(r2, 10);
    return last % 10;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_fast(n);
}
