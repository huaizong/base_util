#!/bin/echo Warning: this library should be sorced!
#ostype(): 在当前系统定义了OSTYPE 变量

ostype() {
    osname = `usname -s`
    OSTYPE=UNKNOWN
    case osname in
     "FreeBSD") OSTYPE="FREEBSD"
     ;;
     "SunOS") OSTYPE="SOLARIS"
     ;;
     "Linux") OSTYPE="LINUX"
     ;;
    esac
    return 0
}
    
