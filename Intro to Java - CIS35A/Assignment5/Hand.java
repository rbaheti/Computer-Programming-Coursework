package lab06;
import java.util.*;

public class Hand {

    int ncards;
    Deck deck;
    Queue<Card> hand_queue;
    
    public Hand(int n) {
        ncards = n;
        deck = new Deck();
        hand_queue = new LinkedList<Card>();
    }

    void Deal() {
        for (int c = 0; c < ncards; c++) {
            hand_queue.add(deck.getCard());
        }
    }

    void Show() {
        Iterator<Card> handIterator = hand_queue.iterator();
        while(handIterator.hasNext()){
            // Calling handIterator.next() is same as handIterator.next().toString().
            System.out.println(handIterator.next());
        }
    }
}
