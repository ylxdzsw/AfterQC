TARGET = editdistance/libed.so
CC = g++
PYEXECUTABLE = pypy

.PHONY: c_ext clean

${TARGET}:${OBJ}
	$(CC) editdistance/_editdistance.cpp -fPIC -shared -O3 -o editdistance/libed.so

c_ext: c_ext/compile.py
	cd c_ext && $(PYEXECUTABLE) compile.py

clean:
	rm -f *.so
	rm -f c_ext/*.so
