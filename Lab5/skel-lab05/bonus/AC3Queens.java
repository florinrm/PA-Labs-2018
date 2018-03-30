import java.util.*;

class Queen {
    public int column;
    public List<Integer> domain;

    public Queen (int column, int lel) {
        this.column = column;
        domain = new ArrayList<>();
        for (int i = 0; i < lel; ++i)
            domain.add(i);
    }

    public Queen () {
        domain = new ArrayList<>();
    }

    public void setVal (int val) {
        domain.clear();
        domain.add(val);
    }

    // copie a reginei
    public Queen cloneQueen() {
		Queen q = new Queen();
		q.column = column;
		for(Integer i : domain)
			q.domain.add(i);
		return q;
	}
}

class Arc {
    public Queen q1, q2;

    public Arc (Queen q1, Queen q2) {
        this.q1 = q1;
        this.q2 = q2;
    }
}

public class AC3Queens {

    public static int count = 0;
    public static int sol = 0;

    public static List<Queen> deepCopy (List <Queen> queens) {
        List <Queen> copy = new ArrayList<>();
        for (int i = 0; i < queens.size(); ++i)
            copy.add(queens.get(i).cloneQueen());
        return copy;
    }


    // vedem daca 2 regine se ataca
    public static boolean doQueensAttack (int rowQ1, int columnQ1, int rowQ2, int columnQ2) {
        boolean row, column, firstDiag, secondDiag;
        if (rowQ2 == rowQ1)
            row = true;
        else 
            row = false;

        if (columnQ1 == columnQ2)
            column = true;
        else 
            column = false;

        if (columnQ1 - columnQ2 == rowQ1 - rowQ2)
            firstDiag = true;
        else
            firstDiag = false;
        
        if (columnQ1 + rowQ1 == columnQ2 + rowQ2)
            secondDiag = true;
        else
            secondDiag = false;

        return row || column || firstDiag || secondDiag;
    }

    // vedem daca domeniul lui q1 a avut modificari
    public static boolean checkDomain (Queen q1, Queen q2) {
        boolean edit = false;
        List <Integer> domain = new ArrayList<> ();
        for (int val1: q1.domain) {
            boolean lel = false;
            for (int val2: q2.domain) {
                if (!doQueensAttack(val1, q1.column, val2, q2.column)) {
                    lel = true; // nu se ataca
                }
            }
            if (!lel) { // se ataca
                edit = true;
            } else {
                domain.add(val1);
            }
        }
        q1.domain = domain;
        return edit;
    }

    // aplicam algoritmul AC3
    public static void doAC3Algo (List <Queen> queens) {
        Queue <Arc> queueArc = new LinkedList<>();
        for (int i = 0; i < queens.size(); ++i) {
            for (int j = 0; j < queens.size(); ++j) {
                if (i != j) {
                    queueArc.add(new Arc(queens.get(i), queens.get(j)));
                }
            }
        }

        while (!queueArc.isEmpty()) {
            Arc arc = queueArc.remove();
            if (checkDomain (arc.q1, arc.q2)) {
                for (Queen queen: queens) {
                    if (queen.column != arc.q1.column && queen.column != arc.q2.column) {
                        queueArc.add(new Arc(queen, arc.q1));
                    }
                }
            }
        }
    }


    public static void doBKT (List <Queen> queens, int k, int n) {
        if (k == n) {
            ++sol;
            System.out.println("Solutia cu numarul: " + sol);
            int[] list = new int[n];
            for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					if(queens.get(j).domain.get(0) == i) {
						list[i] = j;
					}
				}
			}
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					if(list[i] == j) {
						System.out.print("1 ");
					} else {
						System.out.print("0 ");
					}
				}
				System.out.print("\n");
			}

        } else {
            ++count;
            Queen currQueen = queens.get(k);
            doAC3Algo(queens);
            for(int i = 0; i < currQueen.domain.size(); ++i) {
				List<Queen> copy = deepCopy(queens);
				copy.get(k).setVal(currQueen.domain.get(i));
				doBKT (copy, k + 1, n);
			}
        }
    }

    public static void main (String[] args) {
        List <Queen> queens = new ArrayList<>();
        int dim = 5;
		for (int i = 0; i < dim; i++)
			queens.add(new Queen(i, dim));
		doBKT(queens, 0, dim);
        System.out.println("Solutii: " + sol);
        System.out.println("Intrari in recursivitate: " + count);
    }

}