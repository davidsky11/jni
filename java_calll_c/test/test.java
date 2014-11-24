public class test {

	static {
		System.loadLibrary("test");
	}

	public static native String nativeFunc(String msg);

	public static void main(String[] args)
	{
		System.out.println(nativeFunc("Hello Native"));
	}
}
