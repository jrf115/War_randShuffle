#include "war_functions.h"

/****************
*** Functions ***
****************/

/** Generates deck of 52 cards **/
void populuateDeck(Deck& aDeck)
{
    int iterate = 0; // Our card counter in our deck.
    fillSuit(aDeck, iterate);
}

/** This function will define the Suit for the fillRank to fill up with. **/
/** There are four suits that need filled.                               **/
void fillSuit(Deck& aDeck, int iter)
{
    fillRank(aDeck, iter, Spades);
    iter = iter + 13;
    fillRank(aDeck, iter, Clubs);
    iter = iter + 13;
    fillRank(aDeck, iter, Diamonds);
    iter = iter + 13;
    fillRank(aDeck, iter, Hearts);
}

/** This function will fill up the suit it is called to fill up **/
void fillRank(Deck& aDeck, int iter, int cardSuit)
{
    if (cardSuit != Hearts && cardSuit != Clubs && cardSuit != Diamonds && cardSuit != Spades)
        std::cout << "Error: 'cardSuit' is invalid.\n";

    int rankCounter = 1; // Used for the enum's property of ints to help us define the rank of each card in the following loop.
    int temp = iter;
    for (;iter < temp + 13; iter++)   // Each suit has 13 cards. Once you reach the 13th card, focus on the next suit
    {
        aDeck[iter].suit = static_cast<Suit>(cardSuit);
        aDeck[iter].rank = static_cast<Rank>(rankCounter);
        rankCounter++;
    }
}

/** Splits cards evenly for each player. Each player will have 26 cards **/
void split(Deck& deckA, Deck& deckB, Deck& deckGame)
{
    for (int i = 51; i >= 26; i--)
    {
        deckA.push_front(deckGame[i]); // The vector parameter is always zero since we are erasing the first element afterwards, and erase pushes values left one.
        deckGame.pop_back();
    }
    for (int i = 25; i >= 0 ; i--)
    {
        deckB.push_front(deckGame[i]);
        deckGame.pop_back();;
    }
    deckGame.clear();
}

/** This function will compare the rank of the cards passed in,  **/
/** and will return true if there is a difference, false if not  **/
bool compareDifference(Standard_card& aCard, Standard_card& bCard)
{
    if (aCard.rank != bCard.rank)
        return true;     // give card to one of the players
    else
        return false;    // and will initiate a call to war
}

/** Gives a single card to specified player **/
/** This implementation randomizes card pickup **/
void giveCardToPlayer(Standard_card& playersCard, Standard_card& otherPlayersCard, Deck& playerDeck)
{
    srand(time(0));
    int random = (rand() % 2) + 1;
    if (random == 1)
    {
        playerDeck.push_front(otherPlayersCard);
        playerDeck.push_front(playersCard);
    }
    else
    {
        playerDeck.push_front(playersCard);
        playerDeck.push_front(otherPlayersCard);
    }
}

/** Implements the war mode in the game "War" **/
void war(Deck& playerA_Deck, Deck& playerB_Deck)
{
    Deck playerA_PlayCards;
    Deck playerB_PlayCards;
    Deck::iterator playerA_LastCard;
    Deck::iterator playerB_LastCard;
    while (!playerA_Deck.empty() && !playerB_Deck.empty())
    {    // Each player needs to place down three cards vvv
        for (int i = 0; !playerA_Deck.empty() && !playerB_Deck.empty() && i < 4; i++)
        {
            playerA_PlayCards.push_front(playerA_Deck[playerA_Deck.size() - 1]);
            playerB_PlayCards.push_front(playerB_Deck[playerB_Deck.size() - 1]);
            playerA_Deck.pop_back();
            playerB_Deck.pop_back();
        }
        playerA_LastCard = playerA_PlayCards.begin();
        playerB_LastCard = playerB_PlayCards.begin();
        cout << "Player A's third card is a " << playerA_LastCard->rank << " of " << playerA_LastCard->suit << endl;
        cout << "Player B's third card is a " << playerB_LastCard->rank << " of " << playerB_LastCard->suit << endl;
        cout << endl;
        if (playerA_LastCard->suit > playerB_LastCard->suit)
        {
            cout << "Player A wins B's cards " << endl;
            giveCardsToPlayer(playerA_Deck, playerB_PlayCards);
            return;
        }
        else if (playerB_LastCard->suit > playerA_LastCard->suit)
        {
            cout << "Player B wins A's cards " << endl;
            giveCardsToPlayer(playerB_Deck, playerA_PlayCards);
            return;
        }
        else
            cout << "Both players have the same card again! Engage war once more!" << endl;
            // Loop continues if both players have cards
    }
}

/** This function will give cards to a player's hand from war **/
/** Though this function is altered from the original         **/
/** version to accomodate shuffle                             **/
void giveCardsToPlayer(Deck& playerCards, Deck& temp)
{   //Deck temp are the cards to "push back"
    random_shuffle(temp.begin(), temp.end());
    while (!temp.empty())
    {
        playerCards.push_front(temp[temp.size()]);
        temp.pop_back();
    }
    temp.clear();
}
