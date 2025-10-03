package src.compiler;

public class EvalVisitor implements ASTVisitor<Integer> {
    @Override
    public Integer visitNumber(NumberNode node) {
        return node.value;
    }

    @Override
    public Integer visitBinaryOp(BinaryOpNode node) {
        int leftVal = node.left.accept(this);
        int rightVal = node.right.accept(this);

        switch (node.operator) {
            case "+": return leftVal + rightVal;
            case "-": return leftVal - rightVal;
            case "*": return leftVal * rightVal;
            case "/": return leftVal / rightVal;
            default: throw new IllegalArgumentException("Unknown op: " + node.operator);
        }
    }
}