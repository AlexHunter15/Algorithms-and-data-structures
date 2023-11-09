import java.io.*;
import java.util.ArrayDeque;
import java.util.HashSet;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        solve();
    }

    public static void solve() throws IOException {
        Scanner str = new Scanner(new File("input.txt"));
        long tmp = 1;
        int n = str.nextInt();

        long[] ar1 = new long[n];
        long[][] mts1 = new long[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mts1[i][j] = str.nextLong();
            }
        }

        Bfs(n, mts1, ar1);

        FileWriter out = new FileWriter("output.txt");

        for (long i : ar1)
            out.append(String.valueOf(i)).append(" ");
        str.close();
        out.close();
    }

    public static void Bfs(int n, long[][] mts1, long[] ar1) {
        long tmp = 1;

        ArrayDeque<Integer> q1 = new ArrayDeque<>();
        HashSet<Integer> IsV = new HashSet<>();

        for (int i = 0; i < n; i++) {
            if (ar1[i] == 0) {
                ar1[i] = tmp++;
                q1.add(i);
                IsV.add(i);
            }
            while (!q1.isEmpty()) {
                int k = q1.poll();
                for (int j = 0; j < mts1[i].length; j++) {
                    if (mts1[k][j] == 1 && !IsV.contains(j)) {
                        q1.add(j);
                        IsV.add(j);
                        ar1[j] = tmp++;
                    }
                }
            }
        }
    }

}
