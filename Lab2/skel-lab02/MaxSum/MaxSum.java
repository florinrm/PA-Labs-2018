import java.util.*;
import java.io.*;

public class MaxSum {
    public static void main (String[] args) {
        try {
            Scanner scan = new Scanner (new File (args[0]));
            int n, k;
            n = scan.nextInt();
            k = scan.nextInt();
            Vector<Integer> list = new Vector<>();
            for (int i = 0; i < n; ++i) {
                int lel = scan.nextInt();
                list.add(lel);
            }
            Collections.sort(list);
            int index = 0;
            for (int i = 0; i < n; ++i) {
                if (i < k && list.get(i) < 0) {
                    list.set(i, (-1) * list.get(i));
                } else {
                    index = i;
                    break;
                }
            }
            int repetitions = index;
            while (repetitions < k) {
                list.set(index, (-1) * list.get(index));
                repetitions++;
            }

            int sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += list.get(i);
            }

            System.out.println(sum);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}