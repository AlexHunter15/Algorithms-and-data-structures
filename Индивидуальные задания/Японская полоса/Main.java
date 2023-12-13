import java.io.*;
import java.math.BigInteger;

public class Main {

    public static void main(String[] args) {
        try {
            BufferedReader input = new BufferedReader(new FileReader("in.txt"));
            BufferedWriter output = new BufferedWriter(new FileWriter("out.txt"));

            long n = Long.parseLong(input.readLine());
            long k = Long.parseLong(input.readLine());

            if (k == 0) {
                output.write("1");
            } else {
                long m = n - k - k - 1;
                long s = k + 1;

                if (s <= m) {
                    BigInteger result = BinCoefficient(m, s);
                    output.write(result.toString());
                } else {
                    output.write("0");
                }
            }

            input.close();
            output.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static BigInteger BinCoefficient(long n, long k) {
        if (k < 0 || k > n) {
            return BigInteger.ZERO;
        }

        BigInteger result = BigInteger.ONE;
        for (long i = 1; i <= k; i++) {
            result = result.multiply(BigInteger.valueOf(n - i + 1)).divide(BigInteger.valueOf(i));
        }
        return result;
    }
}
