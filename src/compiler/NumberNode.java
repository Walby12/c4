package src.compiler;

public class NumberNode implements ASTNode {
    public final int value;

    public NumberNode(int value) { this.value = value; }

    @Override
    public <R> R accept(ASTVisitor<R> visitor) {
        return visitor.visitNumber(this);
    }
}

