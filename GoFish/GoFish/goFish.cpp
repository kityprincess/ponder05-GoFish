/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;

const int DEFAULT_LOOP_COUNT = 5;
const int INIT_MATCH_COUNT = 0;
const string INTRO_MESSAGE = "We will play 5 rounds of Go Fish.  Guess the card in the hand";
const string CARD_PROMPT_MESSAGE_HEAD = "round ";
const string CARD_PROMPT_MESSAGE_TAIL = ": ";
const string FOUND_MESSAGE = "\tYou got a match!";
const string NOT_FOUND_MESSAGE = "\tGo Fish!";
const string MATCH_MESSAGE_HEAD = "You have ";
const string MATCH_MESSAGE_TAIL = " matches!";
const string DISPLAY_HAND_MESSAGE_HEAD = "The remaining cards: ";
const string DISPLAY_HAND_MESSAGE_SPACER = ", ";
const string HAND_FILE_SERVER_PATH = "/home/cs235/week05/hand.txt";
const string HAND_FILE_LOCAL_PATH = "hand.txt";

void loadHand(const string & in_fileName, Set<Card> & in_hand);
Card promptForCard(int in_round);
void displayHand(const Set<Card> & in_hand);

/***********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   // Display intro
   cout << INTRO_MESSAGE << endl;
   // Load file
   Set<Card> hand;
#ifdef DEBUG
   loadHand(HAND_FILE_LOCAL_PATH, hand);
#else
   loadHand(HAND_FILE_SERVER_PATH, hand);
#endif

   // Loop
   int loopCount = DEFAULT_LOOP_COUNT;
   int matchCount = INIT_MATCH_COUNT;
   int roundNumber = 1;

   while (roundNumber <= loopCount)
   {
      // Prompt for card
      Card card = promptForCard(roundNumber);

      // Check if in hand
      SetIterator<Card> cardFromHand = hand.find(card);

      // If in hand
      if (cardFromHand != hand.end())
      {
         hand.erase(cardFromHand);
         cout << FOUND_MESSAGE << endl;
         matchCount++;
      }
      else
      {
         cout << NOT_FOUND_MESSAGE << endl;
      }
      
      roundNumber++;
   }
   
   // Display matches
   cout << MATCH_MESSAGE_HEAD << matchCount << MATCH_MESSAGE_TAIL << endl;
   
   // Display remaining cards
   displayHand(hand);
   return ;
}

/*********************************************************************
 * LOAD HAND
 * Loads a hand from a file
 *********************************************************************/
void loadHand(const string & in_fileName, Set<Card> & in_hand)
{
   ifstream fin(in_fileName.c_str());

   if (fin.fail())
      throw "ERROR: Unable to open file.";

   Card cardFromFile;

   while (fin >> cardFromFile)
   {
      in_hand.insert(cardFromFile);
   }

   fin.close();

   return;
}

/*********************************************************************
* PROMPT FOR CARD
* Prompts a user for a card for a given round
*********************************************************************/
Card promptForCard(int in_round)
{
   cout << CARD_PROMPT_MESSAGE_HEAD << in_round << CARD_PROMPT_MESSAGE_TAIL;
   Card card;
   cin >> card;

   return card;
}

void displayHand(const Set<Card>& in_hand)
{
   cout << DISPLAY_HAND_MESSAGE_HEAD;

   SetIterator<Card> itHand = in_hand.begin();

   while (itHand != in_hand.end())
   {
      cout << *itHand;
      ++itHand;

      if (itHand != in_hand.end())
         cout << DISPLAY_HAND_MESSAGE_SPACER;
   }

   cout << endl;
}
