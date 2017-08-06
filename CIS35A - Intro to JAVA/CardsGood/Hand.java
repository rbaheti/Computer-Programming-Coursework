
public class Hand 
{
	int ncards;
	Deck deck;
	Card[] hand;
	public Hand(int n)
	{
		ncards = n;
		deck = new Deck();
		hand = new Card[n];
	}
	void Deal()
	{
		for (int c=0; c<ncards; c++)
		{
			hand[c] = deck.getCard();
		}
	}
	void Show()
	{
		for (int c=0; c<ncards; c++)
		{
			System.out.println(hand[c].toString());
		}
	}
	public static void main(String[] args) 
	{
		Hand hand = new Hand(5);
		hand.Deal();
		hand.Show();
	}
}
