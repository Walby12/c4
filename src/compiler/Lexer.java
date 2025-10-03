package src.compiler;

import java.util.ArrayList;

public class Lexer {
    public static ArrayList<Integer> int_val = new ArrayList<>();
    public static int int_index = 0;

    public static ArrayList<TokenType> tokenize(String src) {
        ArrayList<TokenType> toks = new ArrayList<>();
        int line = 1;
        int i = 0;

        while (i < src.length()) {
            char c = src.charAt(i);

            switch (c) {
                case '+': toks.add(TokenType.TOK_PLUS); i++; break;
                case '-': toks.add(TokenType.TOK_MINUS); i++; break;
                case '*': toks.add(TokenType.TOK_MULT); i++; break;
                case '/': toks.add(TokenType.TOK_DIV); i++; break;
                case '(': toks.add(TokenType.TOK_LPAREN); i++; break;
                case ')': toks.add(TokenType.TOK_RPAREN); i++; break;
                case ' ':
                case '\t': i++; break;
                case '\n': line++; toks.add(TokenType.TOK_NEWLINE); i++; break;
                default:
                    if (Character.isDigit(c)) {
                        StringBuilder builder = new StringBuilder();
                        while (i < src.length() && Character.isDigit(src.charAt(i))) {
                            builder.append(src.charAt(i));
                            i++;
                        }
                        int_val.add(int_index++, Integer.parseInt(builder.toString()));
                        toks.add(TokenType.TOK_INT);
                    } else {
                        System.out.printf("Error: unknown character '%c' at line %d\n", c, line);
                        System.exit(1);
                    }
                    break;
            }
        }
        return toks;
    }
}
