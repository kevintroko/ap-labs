package codechallenges;

public class codechallenge01 {
	public static void main(String[] args){
		
		String[] g = {"a", "b", "c","a","b","c","b","b"}; 
//		String[] g = {"b","b","b"}; 
//		String[] g = {"p","w","w","k","e","w"};

		
		String curr, next, prev;
		String longest = "";
		String chain = "";

		
		
		for (int i = 0; i < g.length; i++) {
			
			curr = g[i];
			
			// check previous
			if(i-1<0)
				prev = "Z";
			else 
				prev = g[i-1];
			
			// check next
			if(i+1<g.length)
			next = g[i+1];
			else next = "Z";
			
			// set longest and reset if needed
			if(prev==curr || curr==next){
				if(chain.length()>longest.length())
				longest=chain;
				
				chain="";
			} 
			
			chain+=curr;
			
		}
		
		
		if(longest.length()==0) longest = g[g.length-1];
		
		System.out.println("longest: "+longest.length());
		
	}
}

