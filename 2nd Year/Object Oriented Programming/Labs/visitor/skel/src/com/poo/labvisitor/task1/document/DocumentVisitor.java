package com.poo.labvisitor.task1.document;

public interface DocumentVisitor {

    void visit(BoldTextSegment text);

    void visit(ItalicTextSegment text);

    void visit(PlainTextSegment text);

    void visit(UrlSegment url);

    StringBuilder getDocument();
}
