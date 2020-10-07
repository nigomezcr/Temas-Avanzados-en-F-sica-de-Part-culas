makeit: hist3

random.x: random_numbers_gen.cpp
	g++ $< -o $@

data.txt: random.x
	./$<

hist3: tutorial3.c data.txt
	root $<


clean: rm -f a.out *.x data.txt
