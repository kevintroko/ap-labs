public class CodeChallengeMain {
    public static void main(String[] args) {

        CodeChallenge01 ch = new CodeChallenge01();
        //		String[] g = {"b","b","b"}; 
        //		String[] g = {"p","w","w","k","e","w"};
        System.out.println(ch.lengthOfLongestSubstring("abcdabec"));
        System.out.println(ch.lengthOfLongestSubstring("bbb"));
        System.out.println(ch.lengthOfLongestSubstring("pwwkew"));
    }
}