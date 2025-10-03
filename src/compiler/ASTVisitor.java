package src.compiler;

public interface ASTVisitor<R> {
    R visitNumber(NumberNode node);
    R visitBinaryOp(BinaryOpNode node);
}