package src.compiler;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        ArrayList<TokenType> toks = Lexer.tokenize("(1 + 12) * 2 / 2");
        System.out.println(Lexer.int_val + " " + Lexer.int_index);
        System.out.println(toks);
        Parser parse = new Parser(toks, Lexer.int_val);
        ASTNode ast = parse.parseExpression();
        EvalVisitor visitor = new EvalVisitor();
        int result = ast.accept(visitor);
        System.out.println(result);
    }
}