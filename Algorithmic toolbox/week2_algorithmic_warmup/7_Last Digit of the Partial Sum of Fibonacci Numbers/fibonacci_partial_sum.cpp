#include <iostream>
#include <vector>
using std::vector;

/*
long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}
*/
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

long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    long long sum = 0;
    long long rf = from % 60;
    long long rt = to % 60;
    int i = rf;
    if (rf > rt)
        rt += 60; //because rt can be smaller than rf

   while (i <= rt)
   {
        sum += get_fibonacci_huge_optimized(i, 10);
        i++;
        sum %= 10;
   } 
    return sum % 10;
}
int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
