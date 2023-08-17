#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <string>

enum CardRank {
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace,
};

enum CardSuit {
    clubs,
    diamonds,
    hearts,
    spades,
};

struct Card{
    CardRank rank{};
    CardSuit suit{};
};

void printCard(Card& card) {

    if (card.rank < 8) {
        std::cout << "This card is " << card.rank + 2;
    }
    else {
        switch (card.rank) {
            case jack:
                std::cout << "This card is J";
                break;
            case queen:
                std::cout << "This card is Q" ;
                break;
            case king:
                std::cout << "This card is K";
                break;
            case ace:
                std::cout << "This card is A" ;
                break;

        }
    }

    switch (card.suit) {
        case hearts:
            std::cout << "H" << '\n';
            return;
        case clubs:
            std::cout << "C" << '\n';
            return;
        case diamonds:
            std::cout << "D" << '\n';
            return;
        case spades:
            std::cout << "S" << '\n';
            return;   
    }

}

void printCardOfDeck(Card& card) {

    if (card.rank <= 8) {
        std::cout << card.rank + 2;
    }
    else {
        switch (card.rank) {
            case jack:
                std::cout << "J";
                break;
            case queen:
                std::cout << "Q" ;
                break;
            case king:
                std::cout << "K";
                break;
            case ace:
                std::cout << "A" ;
                break;

        }
    }

    switch (card.suit) {
        case hearts:
            std::cout << "H";
            return;
        case clubs:
            std::cout << "C";
            return;
        case diamonds:
            std::cout << "D";
            return;
        case spades:
            std::cout << "S";
            return;   
    }

}

void ignoreLine() {
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::vector<Card> makeDeck() {
    std::vector<Card> returnDeck(52);

    int iteration{};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            returnDeck[iteration] = {static_cast<CardRank>(j), static_cast<CardSuit>(i)};
            iteration++;
        }
    }

    return returnDeck;
}

int getCardValue(const Card& card) {
    if (card.rank == 12) 
        return 11;
    else if (card.rank > 8)
        return 10;
    else 
        return card.rank + 2;
}

void printDeck(const std::vector<Card>& deck) {
    for (Card card : deck) {
        printCardOfDeck(card);
        std::cout << ':';
        
        std::cout << getCardValue(card) << ' ';
    }
}

int getDeckValue(const std::vector<Card>& deck) {
    int value{};

    for (Card card : deck) {
        value += getCardValue(card);
    }

    return value;
}

bool playBlackJack(const std::vector<Card>& shuffledDeck) {

    int topCard{};
    std::vector<Card> playerCards{};
    std::vector<Card> dealerCards{};

    playerCards.push_back(shuffledDeck[topCard]);
    topCard++;
    dealerCards.push_back(shuffledDeck[topCard]);
    topCard++;
    std::cout << "You and the dealer drew a card!\n";
    std::cout << "Your current cards are: ";
    for (Card card : playerCards) {
        printCardOfDeck(card);
        std::cout << " ";
    }
    std::cout << "; With a value of " << getDeckValue(playerCards) << '\n';

    std::string userInput{};

    while (true) {
        while (true) {
            if (userInput == "hit" || userInput == "stand") {
                break;
            }
            else {
                std::cout << "Would you like to hit or stand?: ";
                std::cin >> userInput;
                ignoreLine();
            }
        }

        if (userInput == "hit") {

            playerCards.push_back(shuffledDeck[topCard]);
            topCard++;
            std::cout << "You drew a card!\n";
            std::cout << "Your current cards are: ";
            for (Card card : playerCards) {
                printCardOfDeck(card);
                std::cout << " ";
            }
            std::cout << "; With a value of " << getDeckValue(playerCards) << '\n';

            if (getDeckValue(playerCards) > 21) {
                std::cout << "Shucks, looks you overdrew, which means...";
                return false;
            }
            userInput = "";
        }
        else {
            break;
        }
    }

    while (true) {
        dealerCards.push_back(shuffledDeck[topCard]);
        topCard++;
        int dealerValue{getDeckValue(dealerCards)};
        std::cout << "Dealer draws a card!\n";
        if (dealerValue > 21) {
            std::cout << "Dealer overdrew! Their score is " << dealerValue << ", which means...";
            return true;
        }
        else if (dealerValue > 16) {
            break;
        }
    }

    std::cout << "Your score is " << getDeckValue(playerCards) << " and the dealer's score is " << getDeckValue(dealerCards) << " meaning...";

    if (getDeckValue(dealerCards) > getDeckValue(playerCards)) {
        return false;
    }
    else 
        return true;
}

int main() {

    Card card = {jack , spades};

    std::vector<Card> deck {makeDeck()};

    std::random_device rd;
    std::mt19937 generator(rd());

    while (true) {
    // Shuffle the vector using std::shuffle
    std::shuffle(deck.begin(), deck.end(), generator);

        if (playBlackJack(deck)) {
            std::cout << " You Win!";
        }
        else {
            std::cout << " You lose!";
        }

        while (true) {
            std::cout << "\n\nReplay? (y/n)";
            std::string userInput{};
            std::cin >> userInput;
            ignoreLine();

            if (userInput == "y") {
                break;
            }
            else if (userInput == "n") {
                return 0;
            }
        }
    }
    
    
    return 0;
}
