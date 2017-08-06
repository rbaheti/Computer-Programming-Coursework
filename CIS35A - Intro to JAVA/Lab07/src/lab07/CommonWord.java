package lab07;

public class CommonWord implements Comparable<CommonWord> {
    String word;
    
    public CommonWord(String word) {
        this.word = word;
    }
    
    public int compareTo(CommonWord cword) {
        return this.word.compareTo(cword.word);
    }
    
    public String toString() {
        return word;
    }
}