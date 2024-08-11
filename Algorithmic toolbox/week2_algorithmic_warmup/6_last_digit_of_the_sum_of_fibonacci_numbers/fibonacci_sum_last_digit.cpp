#include <iostream>

/*
long long fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current = 1;
    long long sum = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}
*/

/*
Calculate the Pisano period for a given modulus
m. The Pisano period, pi(m), is the period with
which the sequence of Fibonacci numbers taken
modulo m repeats.
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

//Summing all Fibonacci until n-th term and returning the sum's last digit
int fibonacci_sum_fast(long long n) {
    long long sum = 0;
    int remainder = n % 60;//Interestingly, all the last digits of Fibonacci repeats every 60terms
    int i = 0;
    while (i <= remainder) {
        sum += get_fibonacci_huge_optimized(i, 10);
        i++;
    }
    return sum % 10;

}
int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_fast(n);
}