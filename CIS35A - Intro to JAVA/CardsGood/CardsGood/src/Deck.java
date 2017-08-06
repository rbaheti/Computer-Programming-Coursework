import java.util.Random;


import java.util.Random;


public class Deck 
{
	char[] values = { '2','3','4','5','6','7','8','9','X','J','Q','K','A' };
	char[] suits = {'C','D','H','S'};
	char used = 'U';
	Card[] deck;
	public Deck()
	{
		deck = new Card[52];
		Initialize();
	}
	void Initialize()
	{
		int index = 0;
		for (char s=0; s<suits.length; s++)
		{
			for (char v=0; v<values.length; v++)
			{
				deck[index] = new Card(s,v);
				deck[index].value = values[v];
				deck[index].suit = suits[s];
				index++;
			}
		}
	}
	Card getCard()
	{
		Random rand = new Random();
		int rindex = rand.nextInt(52);
		return deck[rindex];
	}
}
