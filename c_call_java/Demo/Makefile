CFLAGS = /home/intel/work/jdk1.6.0_38/include

all: Demo
	echo "---------------------------"

Demo: Demo.c Demo.h Demo.java
	gcc -g -I /home/intel/work/jdk1.6.0_38/include -I /home/intel/work/jdk1.6.0_38/include/linux -L /home/intel/work/jdk1.6.0_38/jre/lib/amd64/server/libjvm.so -o Demo Demo.c -ldl
	javac Demo.java

run:
	java -Djava.library.path=. Demo

clean:
	rm -rf Demo.class Demo *.log
