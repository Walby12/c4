package src.compiler;

public interface ASTNode {
    <R> R accept(ASTVisitor<R> visitor);
}

