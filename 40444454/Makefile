compile_a: 
	g++ -std=c++17 symbol_table.cpp -o symbol_table
run_a: 
	./symbol_table $(file)

compile_run_a: compile_a run_a
	
compile_b:
	g++ -std=c++17 symbol_table_B.cpp -o symbol_table_B
	ar rcs symbol_table_BST.a symbol_table_B
	link symbol_table_B symbol_table_BST

run_b:
	./symbol_table_B $(file)

compile_run_b: compile_b run_b

clean:
	rm -f *.o symbol_table
	rm -f *.o symbol_table_B
	rm -f *.txt identifiers
	rm -f *.a symbol_table_BST