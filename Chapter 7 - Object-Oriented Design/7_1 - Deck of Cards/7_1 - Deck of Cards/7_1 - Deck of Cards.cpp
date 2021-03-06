#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>


/*
Deck of Cards:  Design the data structures for a generic deck of cards.  Explain how you would subclass the data 
structures to implement blackjack.
*/

/*
I've got two mutually exclusive approaches to this sort of thing.  The first could be described as "top-down", and
the basic idea would be to start at the highest level (a blackjack game) and work down to the lowest level (definition
of what a card is, say).  

With this approach, we'd have:

class BlackJackGame
{
	std::list<Player> ourPlayers;		// Or a circular list if we plan on allowing the dealer to rotate,
		// or even if we want to allow people to enter/leave the game.
		// The Player class will keep track of the player's current hand, remaining chips, current bet

	Deck shuffledDeck;					// The Deck class will take care of shuffling and a pop() function

	void dealCards();					// Updates the Players' hands and the Deck.  May take a 'dealer' argument.

	void PlayerMove();					// Asks the current Player whether to hit or pass or split or double, and does so.
		
}


class Deck
{
	std::list<Card> playingCards;

	void shuffle();
	Card pop();
}

class Hand
{
	std::list<Card> myCards;

	bool hasNotLost();					// Returns false once the total value has gone above 21.  
										// Takes care of aces having two possible values.
}


class Player
{
	Hand myHand;
	bool hasNotLost();					// calls the myHand.hasNotLost().  Simply for convenience.  
	int totalChips;
	int currentBet;						// In another iteration, maybe have a 'Pot' to take care of the betting.

	void askToMove();					// Get the player's decision on whether to hit, pass, double, split, etc.

}

And so on.  Of course as we develop it, we see better choices we could have made, and so this process is really something 
we come back to over and over.  We want to modularize everything for easy maintanence and extension of functionality, but 
we don't want to overly do it so that we have a bjillion classes each with literally one responsibility.  (SRP is important 
but unrealistic to follow 100%).

*/


/*
For the bottom-up approach, we'd build the atoms with as much generality as possible in mind.  For example, our card class
would maybe look something like this:

class Card
{
	Suit m_suit;			// maybe we want to allow more than 4 suits.  Maybe we want suits to have more functionality
							// than simply being in place to tell cards apart.
	Value m_value;			// Maybe we want a flexible Value class, which for the time being will contain an unsigned 
							// integer, but eventually could be updated to have more functionality	
}

class Suit
{
	///etc
}


This way, it may take lots of work to implement Blackjack, BUT (!) all the pieces are in place so that we could, if we w
wanted to, quickly and cleanly implement Old Maid or UNO as well.
*/





/* 
Anyhow, here goes.  Let's implement Blackjack.  Lots of choices need to be made now, like: do we implement betting?
Do we implement many-player blackjack?  Do we give the dealer rules to follow regarding when to hit and when to stay?
Do we implement splitting and doubling, and do we worry about edge cases like where a player has two aces and decides
not to split?  (in which case the way things are programmed below, both will be treated as 1's even if that's not what
the player wants...)
Here's my answer:  Let's get this thing running with basic functionality, but do so in a modular way so that it will
be easy to add more features later.  
*/


/* Using an enum for SUIT is the flimsiest part of this whole thing.  Funny that my first line is my worst line :P */
/* And the next line is equally bad.  I'd like to wrap all this up so I don't need global variables, but I don't want
   an explosion of classes for every little thing.  So I'll leave this here.  */

enum SUIT {	clubs, spades , hearts, diamonds, SUITS_COUNT };		
std::string suitNames[4]{ "clubs", "spades", "hearts", "diamonds" };

class Card
{
	SUIT m_suit = spades;
	int m_facevalue = 1;
public:
	Card(SUIT suit, int value) : m_suit(suit), m_facevalue(value) {}
	Card(int suit, int value) : m_suit(static_cast<SUIT>(suit)), m_facevalue(value) {}
	Card() : m_suit(spades), m_facevalue(1) {}
	// So much refactoring needed - get rid of SUIT being an enum!!!

	SUIT getSuit() { return m_suit; }
	int getFacevalue() { return m_facevalue; }
	void saySomething() { std::cout << m_facevalue << " of " << suitNames[m_suit] << "\n"; }

	int getMinValue()
	{
		if (m_facevalue == 1) return 1;
		else if (m_facevalue >= 10) return 10;
		else return m_facevalue;
	}

	int getMaxValue()
	{
		if (m_facevalue == 1) return 11;
		else if (m_facevalue >= 10) return 10;
		else return m_facevalue;
	}
};


class Deck
{
	std::vector<Card> m_cards;

public:
	Deck()
	{
		for (int currentSuit = 0; currentSuit < SUITS_COUNT; currentSuit++)
			for (int cardValue = 1; cardValue <= 13; cardValue++)
				m_cards.push_back(Card(currentSuit, cardValue));
	}

	void resetDeck()
	{
		m_cards.resize(0);
		for (int currentSuit = 0; currentSuit < SUITS_COUNT; currentSuit++)
			for (int cardValue = 1; cardValue <= 13; cardValue++)
				m_cards.push_back(Card(currentSuit, cardValue));
	}

	void shuffle()
	{
		std::random_shuffle(m_cards.begin(), m_cards.end());
	}

	Card removeTopCard()
	{
		Card result = m_cards.back();
		m_cards.pop_back();
		return result;
	}

	void displayDeck()
	{
		while (!m_cards.empty())
			removeTopCard().saySomething();
		std::cout << "The deck is empty now.\n";
	}

	void debug()
	{
		displayDeck();
		resetDeck();
		std::cout << "We've just reset the deck.\n";
		displayDeck();
	}

};


class BlackjackHand
{
	std::list<Card> m_cards;
public:
	BlackjackHand() {}

	void addCard(Card someCard) { m_cards.push_back(someCard); }
	
	int getMinValue()
	{
		int answer = 0;
		for (auto it = m_cards.begin(); it != m_cards.end(); it++)
			answer += (*it).getMinValue();
		return answer;
	}

	int getMaxValue()
	{
		int answer = 0;
		for (auto it = m_cards.begin(); it != m_cards.end(); it++)
			answer += (*it).getMaxValue();
		return answer;
	}

	bool isBusted() { return (getMinValue() > 21); }
	bool hasBlackjack() { return ((getMinValue() == 21) or (getMaxValue() == 21)); }

	void resetHand() { m_cards.resize(0); }
	void display()
	{
		std::cout << "Current player hand consists of: \n";
		for (auto it = m_cards.begin(); it != m_cards.end(); it++)
			(*it).saySomething();
	}

};


class Player
{
	BlackjackHand m_hand;

public:

	void receiveCard(Card someCard) { m_hand.addCard(someCard); someCard.saySomething(); }

	void displayHand()
	{
		m_hand.display();
		std::cout << "Current hand min/max value: " << m_hand.getMinValue() << " points / "
			<< m_hand.getMaxValue() << " points.\n";
	}

	void resetHand()
	{
		m_hand.resetHand();
	}

	int minHandValue() { return m_hand.getMinValue(); }
	int maxHandValue() { return m_hand.getMaxValue(); }
	// Refactor opportunity:  Have Player inherit from BlackjackHand.

	bool isBusted() { return m_hand.isBusted(); }
	bool hasBlackjack() { return m_hand.hasBlackjack(); }
};


class BlackjackGame			// Single game.  Needs to take care of resetting the player and deck once done.
{
	Player m_player;
	Deck m_deck;

public:

	void dealCardToPlayer(Player &player)	
	{
		player.receiveCard(m_deck.removeTopCard());		
	}

	void startGame()
	{
		m_deck.resetDeck();
		m_deck.shuffle();
		m_player.resetHand();
		dealCardToPlayer(m_player);		// Deal cards in this manner so it's easy to extend to more players
		dealCardToPlayer(m_player);		// Although in honesty we'd probably just rewrite this
	}	

	bool askHitOrStay()
	{
		if (m_player.isBusted())
			return false;
		m_player.displayHand();
	
		char choice = ' ';
		while ((choice != 'H') and (choice != 'S'))
		{
			std::cout << "(H)it  or  (S)tay ?\n";			
			std::cin >> choice;
		}
		if (choice == 'H')
		{
			dealCardToPlayer(m_player);
			return true;
		}
		else
		{
			std::cout << "Staying with " << m_player.minHandValue() << " / " << m_player.maxHandValue() << ".\n";
			return false;
		}
	}

	void game()
	{
		startGame();
		while (askHitOrStay())
		{
			if (m_player.isBusted())
			{
				std::cout << "Busted!  Total hand value is " << m_player.minHandValue() << ".\n";
				//std::cout << "Play again?\n";
			}

			else if (m_player.hasBlackjack())
			{
				std::cout << "Blackjack! You win!\n";
				//std::cout << "Play again ? \n";
			}
		}
		std::cout << "Play again?\n";
	}


	void gameLoop()
	{
		game();
		char playAgain = ' ';
		while (playAgain != 'N')
		{
			std::cin >> playAgain;
			if (playAgain == 'Y')
				game();
		}
		std::cout << "Thanks for playing!\n";
	}
};


int main()
{
	BlackjackGame ourGame;
	ourGame.gameLoop();

    return 0;
}

