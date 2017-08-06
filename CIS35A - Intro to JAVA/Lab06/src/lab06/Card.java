package lab06;

public class Card 
{
	char value;
	char suit;
	public Card(char v, char s)
	{
		value = v;
		suit = s;
	}
	public char getValue() { return value; }
	public char getSuit() { return suit; }
	public String toString() 
	{ 
		return "suit = " + suit + "\tvalue =" + value;
	}
}