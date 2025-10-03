package src.compiler;


public class BinaryOpNode implements ASTNode {
    public final String operator;
    public final ASTNode left, right;

    public BinaryOpNode(String operator, ASTNode left, ASTNode right) {
        this.operator = operator; this.left = left; this.right = right;
    }

    @Override
    public <R> R accept(ASTVisitor<R> visitor) {
        return visitor.visitBinaryOp(this);
    }
}
