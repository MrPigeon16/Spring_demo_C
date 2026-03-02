build:
	gcc spring.c -o spring -lraylib -lm -lpthread -ldl -lrt -lX11 && ./spring 800 2
