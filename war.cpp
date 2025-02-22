// Author: Nadhirah Michael-Ho
// CECS 325-02 Prog 2
// Due 02/25/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>

using namespace std;

// Card class definition
class Card {
private:
    char rank;
    char suit;
public:
    Card(char r, char s) : rank(r), suit(s) {}
    
    // Display the card in the format: AC, 10S, KD, etc.
    void displayCard() const {
        if (rank == 'T') {
            cout << "10" << suit;  // Special case: print "10" for 'T'
        } else {
            cout << rank << suit;
        }    
    }
    
    // Compare two cards (1: win, 0: tie, -1: lose)
    int compareCard(const Card& other) const {
        string values = "A23456789TJQK"; // Ace to King
        
        int rank1 = values.find(rank);
        int rank2 = values.find(other.rank);
        
        if (rank1 > rank2) return 1;
        else if (rank1 < rank2) return -1;
        else return 0;
    }
};

// Deck class definition
class Deck {
private:
    vector<Card> cards;
    int currentCardIndex;

public:
    Deck() : currentCardIndex(0) {
        // Generate all 52 cards (4 suits, 13 ranks)
        char suits[] = {'C', 'D', 'H', 'S'};  // Clubs, Diamonds, Hearts, Spades
        char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
        
        for (char suit : suits) {
            for (char rank : ranks) {
                cards.push_back(Card(rank, suit));
            }
        }
    }
    
    // Deal a single card, throws exception if deck is empty
    Card deal() {
        if (currentCardIndex >= cards.size()) {
            throw runtime_error("Deck is empty");
        }
        return cards[currentCardIndex++];
    }
    
    // Display all cards in the deck
   void displayDeck() {
        for (size_t i = 0; i < cards.size(); i++) {
            cards[i].displayCard();
            cout << ((i + 1) % 13 == 0 ? "\n" : ", ");
        }
        cout << endl;
    }
    // Shuffle the deck using rand()
    void shuffle() {
        srand(time(0)); // Seed the random number generator
        for (int i = 0; i < cards.size(); ++i) {
            int randIndex = rand() % cards.size();
            swap(cards[i], cards[randIndex]);
        }
    }

    // Check if the deck is empty
    bool isEmpty() const {
        return currentCardIndex >= cards.size();
    }
};

int main() {
    string player1, player2;
    int numGames;
    int player1Wins = 0, player2Wins = 0, ties = 0;

    // Ask for player names and number of games
    cout << "Enter the name of the first player: ";
    getline(cin, player1);
    cout << "Enter the name of the second player: ";
    getline(cin, player2);
    
    cout << "How many games will they play? ";
    cin >> numGames;
    
    // Create deck and display original deck
    Deck deck;
    cout << "Original Deck" << endl;
    deck.displayDeck();
    
    // Shuffle the deck
    deck.shuffle();
    cout << "Shuffled Deck" << endl;
    deck.displayDeck();
    
    try {
        // Play the games
        for (int i = 1; i <= numGames; ++i) {
            cout << "Game " << i << endl;
            cout << "--------" << endl;

            // Deal cards
            Card card1 = deck.deal();
            Card card2 = deck.deal();
            
            // Display cards
            cout << player1 << " => ";
            card1.displayCard();
            cout << endl;
            cout << player2 << " => ";
            card2.displayCard();
            cout << endl;
            
            // Determine winner
            int result = card1.compareCard(card2);
            if (result == 1) {
                cout << player1 << " => Winner" << endl;
                player1Wins++;
            } else if (result == -1) {
                cout << player2 << " => Winner" << endl;
                player2Wins++;
            } else {
                cout << "Tie game" << endl;
                ties++;
            }

            cout << endl;
            
            // Check if deck is empty
            if (deck.isEmpty()) {
                throw runtime_error("Deck is empty");
            }
        }
    } catch (const runtime_error& e) {
        cout << "Error - " << e.what() << endl;
    }
    
    // Print statistics
    cout << "\n------Final Stats-------" << endl;
    cout << "   " << player1 << " vs. " << player2 << endl;
    cout << "Wins   " << player1Wins << "      " << player2Wins << endl;
    cout << "Losses " << player2Wins << "      " << player1Wins << endl;
    cout << "Ties   " << ties << "       " << ties << endl;

    return 0;
}

