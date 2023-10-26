import java.io.*;
import java.util.*;

class MinHeap {
    private long[] heap;
    private int size;

    public MinHeap(int capacity) {
        heap = new long[capacity + 1];
        size = 0;
    }

    public void insert(long value) {
        heap[++size] = value;
        int current = size;
        while (current > 1 && heap[current] < heap[current / 2]) {
            swap(current, current / 2);
            current = current / 2;
        }
    }

    public long extractMin() {
        long min = heap[1];
        heap[1] = heap[size--];
        int current = 1;
        while (current * 2 <= size) {
            int child = current * 2;
            if (child + 1 <= size && heap[child + 1] < heap[child]) {
                child++;
            }
            if (heap[current] <= heap[child]) {
                break;
            }
            swap(current, child);
            current = child;
        }
        return min;
    }

    public int size() {
        return size;
    }

    private void swap(int i, int j) {
        long temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }
}

public class Huffman {
    public static void main(String[] args) {
        try {
            Scanner in = new Scanner(new File("huffman.in"));
            PrintWriter out = new PrintWriter(new File("huffman.out"));

            int n = in.nextInt();
            MinHeap minHeap = new MinHeap(n);

            for (int i = 0; i < n; i++) {
                long pi = in.nextLong();
                minHeap.insert(pi);
            }

            long l = 0;

            while (minHeap.size() > 1) {
                long x = minHeap.extractMin();
                long y = minHeap.extractMin();
                long sum = x + y;
                l += sum;
                minHeap.insert(sum);
            }

            out.println(l);

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
