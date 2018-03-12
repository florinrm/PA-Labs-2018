import java.util.*;
import java.io.*;


public class Dishonest {

    static class Pair {
        public int a, b;
    
        public Pair (int a, int b) {
            this.a = a;
            this.b = b;
        }
    
        public int getDifference () {
            return b - a;
        }
    }

    public static void main (String[] args) {
        try {
            int n, k;
            Scanner scan = new Scanner (new File (args[0]));
            n = scan.nextInt();
            k = scan.nextInt();
            Vector<Integer> before = new Vector<>();
            Vector<Integer> after = new Vector<>();
            for (int i = 0; i < n; ++i) {
                int lel = scan.nextInt();
                before.add(lel);
            }     
            for (int i = 0; i < n; ++i) {
                int lel = scan.nextInt();
                after.add(lel);
            } 
            Vector<Pair> list = new Vector<> ();
            for (int i = 0; i < n; ++i)
                list.add(new Pair (before.get(i), after.get(i)));
            Collections.sort(list, new Comparator<Pair> () {
                public int compare (Pair one, Pair two) {
                    return two.getDifference() - one.getDifference();
                }
            });
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                if (i < k)
                    sum += list.get(i).a;
                else
                    sum += Math.min (list.get(i).b, list.get(i).a);
            }
            System.out.println(sum);            
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}