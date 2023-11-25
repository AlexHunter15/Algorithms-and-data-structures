import java.io.*;
import java.util.*;

public class Main {
    static class DijClass {
        int aim;
        long arr;

        public DijClass(int aim, long arr) {
            this.aim = aim;
            this.arr = arr;
        }
    }

    static class FastReader {
        BufferedReader in;
        StringTokenizer tkn;

        public FastReader() {
            in = new BufferedReader(new InputStreamReader(System.in));
        }

        public FastReader(String fileName) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(fileName));
        }

        String next() {
            while (tkn == null || !tkn.hasMoreElements()) {
                try {
                    tkn = new StringTokenizer(in.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return tkn.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }
    }

    public static void main(String[] args) throws IOException {
        FastReader reader = new FastReader("input.txt");
        int n = reader.nextInt();
        int m = reader.nextInt();

        List<DijClass>[] cnt = new ArrayList[n + 1];
        for (int i = 1; i <= n; i++) {
            cnt[i] = new ArrayList<>();
        }

        for (int i = 0; i < m; i++) {
            int u = reader.nextInt();
            int v = reader.nextInt();
            long w = reader.nextLong();

            cnt[u].add(new DijClass(v, w));
            cnt[v].add(new DijClass(u, w));
        }

        long shortBP = dijkstra(cnt, 1, n);

        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        out.write(Long.toString(shortBP));
        out.close();
    }

    private static long dijkstra(List<DijClass>[] cnt, int beg, int fin) {
        PriorityQueue<DijClass> minHP = new PriorityQueue<>(Comparator.comparingLong(e -> e.arr));
        long[] range = new long[cnt.length];
        Arrays.fill(range, Long.MAX_VALUE);

        minHP.add(new DijClass(beg, 0));
        range[beg] = 0;

        while (!minHP.isEmpty()) {
            DijClass tmp = minHP.poll();

            if (tmp.aim == fin) {
                return range[fin];
            }

            for (DijClass nxt : cnt[tmp.aim]) {
                long finrange = range[tmp.aim] + nxt.arr;

                if (finrange < range[nxt.aim]) {
                    range[nxt.aim] = finrange;
                    minHP.add(new DijClass(nxt.aim, finrange));
                }
            }
        }

        return -1;
    }
}
