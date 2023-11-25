import java.io.*;
import java.util.*;

class DSU {
    private long part;
    private long[] len;
    private long[] orig;

    public DSU(long n) {
        part = n;
        len = new long[(int) (n + 1)];
        orig = new long[(int) (n + 1)];

        for (int i = 1; i <= n; ++i) {
            len[i] = 1;
            orig[i] = i;
        }
    }

    public long PartConst() {
        return part;
    }

    public long FindSet(long x) {
        if (x != orig[(int) x]) {
            orig[(int) x] = FindSet(orig[(int) x]);
        }
        return orig[(int) x];
    }

    public void Union(long x, long y) {
        x = FindSet(x);
        y = FindSet(y);

        if (x != y) {
            if (len[(int) x] < len[(int) y]) {
                long temp = x;
                x = y;
                y = temp;
            }

            if (len[(int) x] == len[(int) y]) {
                len[(int) x]++;
            }

            --part;
            orig[(int) y] = x;
        }
    }
}

class Pair<T, U> {
    public final T first;
    public final U second;

    public Pair(T first, U second) {
        this.first = first;
        this.second = second;
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));
        PrintWriter out = new PrintWriter(new FileWriter("output.txt"));

        long n, m, q;
        String[] input = in.readLine().split(" ");
        n = Long.parseLong(input[0]);
        m = Long.parseLong(input[1]);
        q = Long.parseLong(input[2]);

        DSU SU = new DSU(n);
        List<Pair<Long, Long>> hw = new ArrayList<>();
        boolean[] elim = new boolean[(int) m];
        long[] del = new long[(int) q];

        for (int i = 0; i < m; ++i) {
            input = in.readLine().split(" ");
            long tmp1 = Long.parseLong(input[0]);
            long tmp2 = Long.parseLong(input[1]);
            hw.add(new Pair<>(tmp1, tmp2));
            elim[i] = false;
        }

        for (int i = 0; i < q; ++i) {
            long tmp = Long.parseLong(in.readLine());
            --tmp;
            del[(int) (q - 1 - i)] = tmp;
            elim[(int) tmp] = true;
        }

        for (int i = 0; i < m; ++i) {
            if (!elim[i]) {
                SU.Union(hw.get(i).first, hw.get(i).second);
            }
        }

        StringBuilder sout = new StringBuilder();
        for (int i = 0; i < q; ++i) {
            Pair<Long, Long> coup = hw.get((int) del[i]);
            sout.append(SU.PartConst() > 1 ? '0' : '1');
            SU.Union(coup.first, coup.second);
        }
        sout.reverse();
        out.println(sout);

        in.close();
        out.close();
    }
}
