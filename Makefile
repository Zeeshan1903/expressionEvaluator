build:
	gcc dsa_tasks.c stack.c token.c -o output
run: build
	./output
clean:
	rm -rf ./output