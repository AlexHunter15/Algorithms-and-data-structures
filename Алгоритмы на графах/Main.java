import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {

        BufferedReader in = new BufferedReader(new FileReader("input.txt"));
        PrintWriter out = new PrintWriter(new FileWriter("output.txt"));

        int n = Integer.parseInt(in.readLine());
        int[][] mts1 = new int[n][n];

        for (int ind = 0; ind < n; ind++) {
            String[] row = in.readLine().split(" ");
            for (int j = 0; j < n; j++) {
                mts1[ind][j] = Integer.parseInt(row[j]);
            }
        }

        int[] arl = new int[n];
        boolean[] IsV = new boolean[n];

        FindConnect(mts1, IsV, arl);

        for (int i = 0; i < n; i++) {
            out.print(arl[i] + " ");
        }

        in.close();
        out.close();
    }
    public static void Dfs(int vin, int[][] mts, boolean[] IsV, int[] arl) {

        IsV[vin] = true;
        arl[vin] = Arrays.stream(arl).max().orElse(0) + 1;

        for (int i = 0; i < mts.length; i++) {
            if (mts[vin][i] == 1 && !IsV[i]) {
                Dfs(i, mts, IsV, arl);
            }
        }

    }
    public static void FindConnect(int[][] mts, boolean[] IsV, int[] arl) {

        for (int i = 0; i < IsV.length; i++) {
            if (!IsV[i]) {
                Dfs(i, mts, IsV, arl);
            }
        }

    }


}