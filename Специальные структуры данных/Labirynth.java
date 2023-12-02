import java.io.*;
import java.util.*;

public class Main {
    static final int MOVE_D = 5;
    static final int MOVE_L = -1;
    static final int MOVE_R = 1;
    static final int MOVE_U = -5;

    public static void main(String[] args) {
        try {
            BufferedReader in = new BufferedReader(new FileReader("input.txt"));
            PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("output.txt")));

            StringTokenizer st = new StringTokenizer(in.readLine());
            int rows = Integer.parseInt(st.nextToken());
            int columns = Integer.parseInt(st.nextToken());
            int moves = Integer.parseInt(st.nextToken());

            int[] startPositions = new int[moves];
            int[] endPositions = new int[moves];
            int[][] grid = new int[rows][columns];

            st = new StringTokenizer(in.readLine());
            for (int i = 0; i < moves; ++i) {
                startPositions[i] = Integer.parseInt(st.nextToken()) - 1;
            }

            st = new StringTokenizer(in.readLine());
            for (int i = 0; i < moves; ++i) {
                endPositions[i] = Integer.parseInt(st.nextToken()) - 1;
            }

            for (int i = 0; i < rows; ++i) {
                st = new StringTokenizer(in.readLine());
                for (int j = 0; j < columns; ++j) {
                    grid[i][j] = Integer.parseInt(st.nextToken());
                }
            }

            for (int i = 0; i < moves; ++i) {
                grid[rows - 1][endPositions[i]] = -3;
            }

            int count = 0;

            for (int i = 0; i < moves; ++i) {
                Deque<Pair<Pair<Integer, Integer>, Integer>> temp = new ArrayDeque<>();

                if (grid[0][startPositions[i]] != 0) {
                    continue;
                }

                temp.push(new Pair<>(new Pair<>(0, startPositions[i]), MOVE_D));

                while (!temp.isEmpty()) {
                    Pair<Pair<Integer, Integer>, Integer> item = temp.peek();
                    int direction = item.second;
                    temp.pop();

                    Pair<Integer, Integer> coordinates = item.first;
                    int x = coordinates.first;
                    int y = coordinates.second;

                    if (grid[x][y] < -2) {
                        count++;
                        grid[x][y] = -4 - i;
                        break;
                    } else {
                        grid[x][y] = i + 2;
                    }

                    int[] nextPositions = new int[3];
                    switch (direction) {
                        case MOVE_D:
                            nextPositions[0] = MOVE_L;
                            nextPositions[1] = MOVE_D;
                            nextPositions[2] = MOVE_R;
                            break;
                        case MOVE_L:
                            nextPositions[0] = MOVE_U;
                            nextPositions[1] = MOVE_L;
                            nextPositions[2] = MOVE_D;
                            break;
                        case MOVE_R:
                            nextPositions[0] = MOVE_D;
                            nextPositions[1] = MOVE_R;
                            nextPositions[2] = MOVE_U;
                            break;
                        default:
                            nextPositions[0] = MOVE_R;
                            nextPositions[1] = MOVE_U;
                            nextPositions[2] = MOVE_L;
                    }

                    boolean all = true;

                    for (int j = 0; j < 3; ++j) {
                        int nextX = x + nextPositions[j] / 5;
                        int nextY = y + nextPositions[j] % 5;

                        if (nextX >= 0 && nextX < rows &&
                                nextY >= 0 && nextY < columns &&
                                (grid[nextX][nextY] == 0 || grid[nextX][nextY] < -2)) {

                            Pair<Integer, Integer> newItem = new Pair<>(nextX, nextY);
                            temp.push(item);
                            temp.push(new Pair<>(newItem, nextPositions[j]));
                            all = false;
                            break;
                        }
                    }

                    if (all) {
                        grid[x][y] = -2;
                    }
                }
            }

            for (int j = 0; j < rows; ++j) {
                for (int l = 0; l < columns; ++l) {
                    if (grid[j][l] == -2) {
                        grid[j][l] = 0;
                    }
                }
            }

            for (int i = 0; i < moves; ++i) {
                if (grid[rows - 1][endPositions[i]] == -3) {
                    grid[rows - 1][endPositions[i]] = 0;
                } else {
                    grid[rows - 1][endPositions[i]] = -grid[rows - 1][endPositions[i]] - 2;
                }
            }

            out.println(count);
            for (int i = 0; i < rows; ++i) {
                out.print(grid[i][0]);
                for (int j = 1; j < columns; ++j) {
                    out.print(" " + grid[i][j]);
                }
                out.println();
            }

            in.close();
            out.close();

        } catch (IOException e) {
            System.err.println("Failed to open input.txt or output.txt");
            e.printStackTrace();
        }
    }

    static class Pair<U, V> {
        U first;
        V second;

        Pair(U first, V second) {
            this.first = first;
            this.second = second;
        }
    }
}
