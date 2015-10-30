package kassako;

public class Customer {
	int bornTime;
	int groceries;
	
	public boolean isDone(int groceries) {
		
		if (groceries > 0) {
		return true;
	}
	return false;
	}
	public int serve(int goceries) {
		
		return groceries = groceries - 1;
	}
}

