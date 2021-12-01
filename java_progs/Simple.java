public class Simple{
	public static void main(String args[]){
		System.out.println("Hello Java");
		Foo foo = new Foo();
		for (int i = 0; i < 1000; i++){
			foo = new Foo();
			foo.a = new Bar();
			Bar b = new Bar();
			foo.a = b;
			foo.a.a = 12;
			System.out.println("Hellu");
		}

	}  
}

class Foo{
	Bar a;		
}

class Bar{
	int a;
}
