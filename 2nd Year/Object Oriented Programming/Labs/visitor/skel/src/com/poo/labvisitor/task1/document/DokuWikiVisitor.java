package com.poo.labvisitor.task1.document;

public class DokuWikiVisitor implements DocumentVisitor {

    private final StringBuilder stringBuilder = new StringBuilder();

    @Override
    public void visit(BoldTextSegment text) {
        stringBuilder.append("**").append(text.getContent()).append("**");
    }

    @Override
    public void visit(ItalicTextSegment text) {
        stringBuilder.append("//").append(text.getContent()).append("//");
    }

    @Override
    public void visit(PlainTextSegment text) {
        stringBuilder.append(text.getContent());
    }

    @Override
    public void visit(UrlSegment url) {
        stringBuilder.append("[[").append(url.getUrl()).append("|").append(url.getDescription()).append("]]");

    }


    @Override
    public StringBuilder getDocument() {
        return stringBuilder;
    }
}
