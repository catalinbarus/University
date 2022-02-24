package com.oop_pub.exceptions.ex4;

import java.util.EnumSet;

enum LogLevel {Info, Debug, Warning, Error, FunctionalMessage, FunctionalError};

public class LogLevelClass {


    public static EnumSet<LogLevel> returnValues() {

        return EnumSet.allOf(LogLevel.class);
    }


}
