CXX = g++
experiments_amount = 10
modes = Without-specifying-optimization O0 O1 O2 O3 Os march mtune Ofast

Without-specifying-optimization:
ifeq (,$(wildcard ./main))
	$(CXX) -o main main.cpp
else
	@echo "Without-specifying-optimization was already compiled"
endif
	
Without-specifying-optimization-run:
	@echo "Process Without explicitly specifying optimization"
	./main
	@echo ""

O0:
ifeq (,$(wildcard ./main0))
	$(CXX) -O0 -o main0 main.cpp
else
	@echo "O0 was already compiled"
endif

O0-run:
	@echo "Process with no optimization options (O0)"
	./main0
	@echo ""

O1:
ifeq (,$(wildcard ./main1))
	$(CXX) -O1 -o main1 main.cpp
else
	@echo "O1 was already compiled"
endif

O1-run:
	@echo "Process with O1 optimization level"
	./main1
	@echo ""

O2:
ifeq (,$(wildcard ./main2))
	$(CXX) -O2 -o main2 main.cpp
else
	@echo "O2 was already compiled"
endif

O2-run:
	@echo "Process with O2 optimization level"
	./main2
	@echo ""

O3:
ifeq (,$(wildcard ./main3))
	$(CXX) -O3 -o main3 main.cpp
else
	@echo "O3 was already compiled"
endif
	

O3-run:
	@echo "Process with O3 optimization level"
	./main3
	@echo ""

Os:
ifeq (,$(wildcard ./mains))
	$(CXX) -Os -o mains main.cpp
else
	@echo "Os was already compiled"
endif

Os-run:
	@echo "Process with Os optimization level"
	./mains
	@echo ""

march:
ifeq (,$(wildcard ./main_march_native))
	$(CXX) -march=native -o main_march_native main.cpp
else
	@echo "march was already compiled"
endif
	
march-run:
	@echo "Process with march=native optimization level"
	./main_march_native
	@echo ""

mtune:
ifeq (,$(wildcard ./main_mtune_native))
	$(CXX) -mtune=native -o main_mtune_native main.cpp
else
	@echo "mtune was already compiled"
endif

mtune-run:
	@echo "Process with mtune=native optimization level"
	./main_mtune_native
	@echo ""

Ofast:
ifeq (,$(wildcard ./main_fast))
	$(CXX) -Ofast -o main_fast main.cpp
else
	@echo "Ofast was already compiled"
endif

Ofast-run:
	@echo "Process with Ofast optimization level"
	./main_fast
	@echo ""

run:
	@echo "modes,time-diff(one cycle),time-diff(two cycles)" > data.csv
	@for key in $(modes) ; do \
        make $$key ; \
		echo $$key >> data.csv ; \
		index=1 ; while [ $$index -le $(experiments_amount) ] ; do \
        	echo -n $$index"," >> data.csv ; \
			make $$key"-run" ; \
        	index=$$((index + 1)) ; \
    	done ; \
		echo >> data.csv ; \
    done
	.env/bin/python3.10 graphics.py $(experiments_amount)

clean:
	rm -rf main main0 main1 main2 main3 mains main_march_native main_mtune_native main_fast
