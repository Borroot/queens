all: queens

queens: queens.cpp
	$(CXX) -o $@ $<

clean:
	rm queens
