package lab06;

import java.util.Random;
import java.util.*;

public class Deck {

    char[] values = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};
    char[] suits = {'C', 'D', 'H', 'S'};
    List<Card> deck_list;

    public Deck() {
        deck_list = new ArrayList<Card>(52);
        Initialize();
    }

    void Initialize() {
        int index = 0;
        for (int i = 0; i < suits.length; i++) {
            for (int j = 0; j < values.length; j++) {
                Card card = new Card(suits[i], values[j]);
                deck_list.add(index, card);
                index++;
            }
        }
    }

    Card getCard() {
        Random rand = new Random();
        int rindex = rand.nextInt(52);
        return deck_list.get(rindex);
    }
}
