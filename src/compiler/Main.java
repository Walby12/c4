package src.compiler;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        ArrayList<TokenType> toks = Lexer.tokenize("\n12 + 13");
        System.out.println(Lexer.int_val + " " + Lexer.int_index);
        System.out.println(toks);
    }
}