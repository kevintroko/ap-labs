import java.util.HashSet;
import java.util.*;
import java.util.stream.*;

public class CodeChallenge01 {
    public int lengthOfLongestSubstring(String input) {
        
        int n = input.length();
        int result = 0;
        int x = 0;
        int y = 0;

        //		String[] g = {"b","b","b"}; 
        //		String[] g = {"p","w","w","k","e","w"};

        Set<Character> s = new HashSet<>();
        while ((y<n)&&(x<n) ) {
            if (!s.contains(input.charAt(y))){
                s.add(input.charAt(y++));
                result = Math.max(result, y-x);
            }
            else {
                s.remove(input.charAt(x++));
            }
        }
        return result;
    }
}