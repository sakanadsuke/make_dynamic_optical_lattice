PROG = lattice
OBJS = make_lattice.o get_csv_contents.o check_file_status.o


CC := g++
FRAMES := -framework GLUT -framework OpenGL

.PHONY: all
all: $(PROG)

### make object files ###
.SUFFIXES: .o .cpp
.cpp.o:
	$(CC) -c $<


### make EXE file ###
$(PROG): $(OBJS)
	$(CC) $(FRAMES) $^ -o $(PROG)

### clean up! ###
.PHONY: clean
clean:
	rm -f $(PROG) $(OBJS)