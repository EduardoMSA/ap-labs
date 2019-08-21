import java.util.Scanner;

public class LongestSubstring {
	
	private String chain,maxSubStr;
	
	public LongestSubstring(String chain) {
		this.chain = chain;
		this.maxSubStr = this.getLongestSubstring();
	}
	
	public String getMaxSubStr() {
		return this.maxSubStr;
	}
	
	public int getMaxSubStrLen() {
		return getMaxSubStr().length();
	}
	
	private String getLongestSubstring() {
		String	actual = "",
				max = "";
		char c;
		int index = 0;
		for(int i=0; i<this.chain.length();i++) {
			c = this.chain.charAt(i);
			index = isIn(c,actual);
			if(index>=0) {
				actual = actual.substring(index+1,actual.length());
			}
			actual += c;
			if(actual.length() > max.length()){
				max = actual;
			}
			
		}
		
		return max;
	}
	
	private int isIn(char letter, String subStr) {
		for(int i = 0; i<subStr.length();i++) {
			if(letter == subStr.charAt(i)) {
				return i;
			}
		}
		return -1;
	}
	

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scan = new Scanner(System.in);
		String s = scan.nextLine();
		LongestSubstring ls = new LongestSubstring(s);
		System.out.println("Longest substring = " + ls.getLongestSubstring());
		System.out.println("Length of the longest substring = "+ls.getMaxSubStrLen());
	}

}
