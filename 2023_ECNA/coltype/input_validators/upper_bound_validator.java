/**
 * Check that if there exists a solution, then it is smaller than the guaranteed
 * upper bound.
 * @author Finn Lidbetter
 */

import java.math.BigInteger;
import java.io.*;


public class upper_bound_validator {
    public static int STR_LEN_MAX = 50;
    public static int START_EXP_MAX = 47;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        char[] seq = br.readLine().toCharArray();
        int END_EXP_MAX = START_EXP_MAX + (int)((STR_LEN_MAX/2.0) * (Math.log(1.5)/Math.log(2))) + 10;
        BigInteger TWO = new BigInteger("2");
        BigInteger THREE = new BigInteger("3");
        BigInteger UPPER_BOUND = BigInteger.ONE.shiftLeft(START_EXP_MAX);
        BigInteger best = new BigInteger(UPPER_BOUND.toString());
        for (int endExp=0; endExp<=END_EXP_MAX; endExp++) {
            BigInteger curr = BigInteger.ONE.shiftLeft(endExp);
            boolean valid = true;
            for (int index=0; index<seq.length; index++) {
                char ch = seq[seq.length - index - 1];
                if (ch == 'E') {
                    curr = curr.multiply(TWO);
                } else {
                    // ch == 'O'
                    if (!curr.mod(THREE).equals(BigInteger.ONE)) {
                        valid = false;
                        break;
                    }
                    curr = curr.subtract(BigInteger.ONE);
                    curr = curr.divide(THREE);
                    if (curr.mod(TWO).equals(BigInteger.ZERO)) {
                        valid = false;
                        break;
                    }
                }
                if (curr.bitCount() == 1) {
                    // curr is a power of two.
                    valid = false;
                    break;
                }
            }
            if (valid && curr.compareTo(best) < 0) {
                best = curr;
            }
        }
        if (best.compareTo(UPPER_BOUND) < 0) {
            // There is a solution lower than the upper bound.
            System.exit(42);
        } else {
            if (seq[seq.length-1] == 'E') {
                // There is no solution but this is one of the special "INVALID" cases.
                System.exit(42);
            }
            for (int i=0; i<seq.length-1; i++) {
                if (seq[i]=='O' && seq[i+1]=='O') {
                    // There is no solution, but this is one of the special "INVALID" cases.
                    System.exit(42);
                }
            }
            // It is not a special "INVALID" case and there is no solution.
            System.exit(3);
        }
    }
}