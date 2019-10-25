public class Factorial {
    /**
     * A procedure that calculates the factorial of a given N.
     */
    public static long f(long n) {
        if (n == 1)
            return 1;
        else
            return n * f(n - 1);
    }

    public static void main(String[] args) {
        long n = Integer.parseInt(args[0]);
        long currentTime = System.currentTimeMillis();
        System.out.printf("!d = %d\n", n, f(n));
        System.out.printf("Time spent: %4.2f s\n",
                          (System.currentTimeMillis() - currentTime) / 1000.0);
    }
}
