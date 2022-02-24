package com.poo.labvisitor.task1.document;

/**
 * Represents a text segment of a document that needs to be parsed.
 */
public abstract class TextSegment {
    private final String content;

    TextSegment(String content) {
        this.content = content;
    }

    public String getContent() {
        return content;
    }

    // TODO add method for applying the visitor

    public void accept(DocumentVisitor visitor) {

    }
}
