package com.poo.labvisitor.task1.document;

public class UrlSegment extends TextSegment {

    private String url;

    private String description;

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public UrlSegment(String content, String url, String description) {
        super(content);
        this.url = url;
        this.description = description;
    }

    @Override
    public void accept(DocumentVisitor visitor) {
        super.accept(visitor);
    }
}
