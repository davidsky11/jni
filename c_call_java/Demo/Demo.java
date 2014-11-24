public class Demo {

	public static int COUNT = 8;
	
	private String msg;
	private int[] counts;

	public Demo() {
		this("demo");
	}

	public Demo(String msg) {
		this.msg = msg;
		this.counts = null;
	}

	public String getMessage() {
		return msg;
	}

	public static String getHelloWorld() {
		return "Hello world!";
	}

	public String append(String str, int i) {
		return str + i;
	}

	public int[] getCounts() {
		return counts;
	}

	public void setCounts(int[] counts) {
		this.counts = counts;
	}

	public void throwExcp() throws IllegalAccessException {
		throw new IllegalAccessException("exception occur.");
	}
}
