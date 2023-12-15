import java.io.*;
import java.util.*;

public class Main {

    static class Pair<T, U> {
        T fir;
        U sec;

        Pair(T fir, U sec) {
            this.fir = fir;
            this.sec = sec;
        }
    }

    static class DirectedGraph {
        int peak;
        List<List<Integer>> AdjLst;
        List<List<Integer>> RevAdjLst;

        DirectedGraph(int vrt) {
            this.peak = vrt;
            AdjLst = new ArrayList<>(vrt);
            RevAdjLst = new ArrayList<>(vrt);
            for (int i = 0; i < vrt; i++) {
                AdjLst.add(new ArrayList<>());
                RevAdjLst.add(new ArrayList<>());
            }
        }

        void addDirectedEdge(int u, int v) {
            AdjLst.get(u).add(v);
            RevAdjLst.get(v).add(u);
        }

        Pair<Integer, List<Integer>> SCCSearch() {
            boolean[] paint = new boolean[peak];
            List<Integer> ordPeak = new ArrayList<>();

            for (int v = 0; v < peak; v++) {
                if (!paint[v]) {
                    DepthVisit(v, paint, ordPeak);
                }
            }

            Arrays.fill(paint, false);
            int numCmp = 0;
            int[] cmp = new int[peak];

            for (int i = ordPeak.size() - 1; i >= 0; i--) {
                int v = ordPeak.get(i);
                if (!paint[v]) {
                    DepthVisitReverse(v, paint, cmp, numCmp);
                    numCmp++;
                }
            }

            List<Integer> vrtCmp = new ArrayList<>();
            for (int cmpnum : cmp) {
                vrtCmp.add(cmpnum);
            }
            return new Pair<>(numCmp, vrtCmp);
        }

        void DepthVisit(int v, boolean[] IsV, List<Integer> ordPeak) {
            IsV[v] = true;
            for (int u : AdjLst.get(v)) {
                if (!IsV[u]) {
                    DepthVisit(u, IsV, ordPeak);
                }
            }
            ordPeak.add(v);
        }

        void DepthVisitReverse(int v, boolean[] IsV, int[] cmps, int cmpNum) {
            IsV[v] = true;
            cmps[v] = cmpNum;
            for (int u : RevAdjLst.get(v)) {
                if (!IsV[u]) {
                    DepthVisitReverse(u, IsV, cmps, cmpNum);
                }
            }
        }

        List<List<Integer>> spCmp(int countCmps, List<Integer> vrtxCmps) {
            List<List<Integer>> contCmps = new ArrayList<>(countCmps);
            for (int i = 0; i < countCmps; i++) {
                contCmps.add(new ArrayList<>());
            }
            for (int i = 0; i < vrtxCmps.size(); i++) {
                contCmps.get(vrtxCmps.get(i)).add(i);
            }
            return contCmps;
        }

        boolean bpMer(int v, int component, List<Integer> cmps, boolean[] visited, boolean[] part) {
            visited[v] = true;
            boolean isBp = true;
            for (int u : AdjLst.get(v)) {
                if (cmps.get(u) == component) {
                    if (visited[u] && part[u] == part[v]) {
                        isBp = false;
                    }
                    if (!visited[u]) {
                        part[u] = !part[v];
                        isBp = bpMer(u, component, cmps, visited, part);
                    }
                }
            }
            return isBp;
        }

        Pair<Boolean, List<Integer>> MerGraph() {
            Pair<Integer, List<Integer>> sccResult = SCCSearch();
            int countCmps = sccResult.fir;
            List<Integer> vertexComponents = sccResult.sec;

            List<List<Integer>> connectedCmps = spCmp(countCmps, vertexComponents);
            List<Pair<List<Integer>, List<Integer>>> cmpMer = new ArrayList<>(countCmps);

            for (int i = 0; i < countCmps; i++) {
                boolean[] IsV = new boolean[peak];
                boolean[] part = new boolean[peak];
                boolean result = bpMer(connectedCmps.get(i).get(0), i, vertexComponents, IsV, part);
                if (!result) {
                    return new Pair<>(false, new ArrayList<>());
                }
                List<Integer> mer1 = new ArrayList<>();
                List<Integer> mer2 = new ArrayList<>();
                for (int j = 0; j < part.length; j++) {
                    if (vertexComponents.get(j) == i) {
                        if (part[j]) {
                            mer1.add(j);
                        } else {
                            mer2.add(j);
                        }
                    }
                }
                cmpMer.add(new Pair<>(mer1, mer2));
                Arrays.fill(IsV, false);
            }

            cmpMer.sort((a, b) -> Math.max(a.fir.size(), a.sec.size()) > Math.max(b.fir.size(), b.sec.size()) ? -1 : 1);

            List<Integer> a = new ArrayList<>();
            List<Integer> b = new ArrayList<>();

            for (Pair<List<Integer>, List<Integer>> cp : cmpMer) {
                List<Integer> p1 = cp.fir;
                List<Integer> p2 = cp.sec;
                if (a.size() > b.size()) {
                    if (p1.size() > p2.size()) {
                        a.addAll(p2);
                        b.addAll(p1);
                    } else {
                        a.addAll(p1);
                        b.addAll(p2);
                    }
                } else {
                    if (p1.size() > p2.size()) {
                        a.addAll(p1);
                        b.addAll(p2);
                    } else {
                        a.addAll(p2);
                        b.addAll(p1);
                    }
                }
            }

            if (a.size() < b.size()) {
                List<Integer> temp = a;
                a = b;
                b = temp;
            }

            if ((double) a.size() / (double) b.size() > 2.0) {
                return new Pair<>(false, new ArrayList<>());
            }

            Collections.sort(a);
            return new Pair<>(true, a);
        }
    }

    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new FileReader("input.in"));
             BufferedWriter writer = new BufferedWriter(new FileWriter("output.out"))) {

            int n = Integer.parseInt(reader.readLine());
            if (n == 1) {
                writer.write("NO");
                return;
            }
            DirectedGraph directedGraph = new DirectedGraph(n);
            String[] nums;
            int tmp;
            for (int i = 0; i < n; i++) {
                nums = reader.readLine().split(" ");
                for (int j = 0; j < n; j++) {
                    tmp = Integer.parseInt(nums[j]);
                    if (tmp == 0 && i != j) {
                        directedGraph.addDirectedEdge(i, j);
                    }
                }
            }

            Pair<Boolean, List<Integer>> fin = directedGraph.MerGraph();

            if (!fin.fir) {
                writer.write("NO");
                return;
            }

            writer.write("YES\n");
            for (int i = 0; i < fin.sec.size(); i++) {
                writer.write((fin.sec.get(i) + 1) + (i == fin.sec.size() - 1 ? "\n" : " "));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
