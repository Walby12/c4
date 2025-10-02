package src.compiler;

import java.util.ArrayList;

public class Lexer {
    public static ArrayList<Integer> int_val = new ArrayList<>();
    public static int int_index = 0;

    static public ArrayList<TokenType> tokenize(String src) {
        ArrayList<TokenType> toks = new ArrayList<>();
        int line = 1;

        String[] source = src.split("");

        for (int i = 0; i < source.length; i++) {
            String c = source[i];
            switch (c) {
                case "+":
                    toks.add(TokenType.TOK_PLUS);
                    break;
                case " ":
                    continue;
                case "\t":
                    continue;
                case "\n":
                    line++;
                    toks.add(TokenType.TOK_NEWLINE);
                    break;
                default:
                    if (is_numeric(c)) {
                        StringBuilder builder = new StringBuilder();
                        while (i < source.length && is_numeric(c)) {
                            builder.append(c);
                            i++;
                            if (i < source.length) {
                                c = source[i];
                            } else {
                                break;
                            }
                        }
                        String str = builder.toString();

                        try {
                            int_val.add(int_index++, Integer.parseInt(str));
                            toks.add(TokenType.TOK_INT);
                        } catch (NumberFormatException e) {
                            System.out.printf("Error: could not parse int: %d at line: %d", str, line);
                            System.exit(1);
                        }
                    } else {
                        System.out.printf("Error: unknow string: %s at line: %d", c, line);
                        System.exit(1);
                    }
                    break;
            }
        }
        return toks;
    }
    static boolean is_numeric(String strNum) {
        if (strNum == null) {
            return false;
        }
        try {
            int d = Integer.parseInt(strNum);
        } catch (NumberFormatException e) {
            return false;
        }
        return true;
    }
}