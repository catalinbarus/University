CC=g++
kmp=KMP.cpp
edit=Edit.cpp
EXE=algo.o

kmp: KMP.cpp
	$(CC) $(kmp) -o $(EXE)

edit: Edit.cpp
	$(CC) $(edit) -o $(EXE)

run: $(EXE)
	./$(EXE)

clean:
	rm -f $(EXE)

.PHONY: clean run
