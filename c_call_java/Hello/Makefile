CFLAGS = /home/intel/work/jdk1.6.0_38/include

all: Hello
	echo "---------------------------"

Hello: Hello.cpp Hello.h Hello.java
	g++ -I /home/intel/work/jdk1.6.0_38/include -I /home/intel/work/jdk1.6.0_38/include/linux -fPIC -shared -o libHello.so Hello.cpp
	javac Hello.java

run:
	java -Djava.library.path=. Hello

clean:
	rm -rf Hello.class libHello.so
