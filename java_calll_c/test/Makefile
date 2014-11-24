CFLAGS = /home/intel/work/jdk1.6.0_38/include

all: test
	echo "---------------------------"

test: test.c test.h test.java
	gcc -I /home/intel/work/jdk1.6.0_38/include -I /home/intel/work/jdk1.6.0_38/include/linux -fPIC -shared -o libtest.so test.c
	javac test.java

run:
	java -Djava.library.path=. test

clean:
	rm -rf test.class libtest.so
