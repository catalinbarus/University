package com.oop_pub.exceptions.ex4;

import java.util.EnumSet;

public abstract class LoggerBase {

    EnumSet<LogLevel> set;
    LoggerBase loggerBase;

    public LoggerBase(LoggerBase loggerBase, EnumSet<LogLevel> set) {
        this.loggerBase = loggerBase;
        this.set = set;
    }

    public void setNext(LoggerBase loggerBase) {
        this.loggerBase = loggerBase;
    }

    protected abstract void writeMessage(String message);

    public void message(String message, LogLevel severity) {

        for (LogLevel l : this.set) {

            if(l.equals(severity)) {
                writeMessage(message);
                setNext(loggerBase);
            }
        }
    }
}
