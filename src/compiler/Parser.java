package src.compiler;

import java.util.ArrayList;

public class Parser {
    private final ArrayList<TokenType> tokens;
    private final ArrayList<Integer> values; 
    private int pos = 0;
    private int valPos = 0;

    public Parser(ArrayList<TokenType> tokens, ArrayList<Integer> values) {
        this.tokens = tokens;
        this.values = values;
    }

    public ASTNode parseExpression() {
        return parseAddSub();
    }

    private ASTNode parseAddSub() {
        ASTNode left = parseMulDiv();

        while (pos < tokens.size() &&
              (tokens.get(pos) == TokenType.TOK_PLUS || tokens.get(pos) == TokenType.TOK_MINUS)) {

            TokenType op = tokens.get(pos++);
            ASTNode right = parseMulDiv();

            String operator = (op == TokenType.TOK_PLUS) ? "+" : "-";
            left = new BinaryOpNode(operator, left, right);
        }

        return left;
    }

    private ASTNode parseMulDiv() {
        ASTNode left = parseFactor();

        while (pos < tokens.size() &&
              (tokens.get(pos) == TokenType.TOK_MULT || tokens.get(pos) == TokenType.TOK_DIV)) {

            TokenType op = tokens.get(pos++);
            ASTNode right = parseFactor();

            String operator = (op == TokenType.TOK_MULT) ? "*" : "/";
            left = new BinaryOpNode(operator, left, right);
        }

        return left;
    }

    private ASTNode parseFactor() {
        if (pos >= tokens.size()) {
            throw new RuntimeException("Unexpected end of input");
        }

        TokenType tok = tokens.get(pos);

        if (tok == TokenType.TOK_INT) {
            int value = values.get(valPos++);
            pos++;
            return new NumberNode(value);
        }

        if (tok == TokenType.TOK_LPAREN) {
            pos++; 
            ASTNode expr = parseExpression();

            if (pos >= tokens.size() || tokens.get(pos) != TokenType.TOK_RPAREN) {
                throw new RuntimeException("Expected ')' at position " + pos);
            }

            pos++;
            return expr;
        }

        throw new RuntimeException("Unexpected token: " + tok + " at position " + pos);
    }
}