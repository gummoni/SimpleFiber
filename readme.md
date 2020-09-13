# co-routine library


## example

```c
void hello_world(void* arg) {
	printf("hello \n");
	yield;
	printf("world\n");
}

void main() {
	//setup
	fiber* f1 = new fiber();
	sc->attach(f1);

	//async execution
	func* f = f1->invoke(hello_world, NULL);
	f->wait();

	//scheduler mainloop
	sc->start();
}
```
