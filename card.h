#ifndef _CARD_H
#define _CARD_H

enum staff_effect_id; 

enum action_effect;

/*
 *@brief general card type definition, for action and staff cards. Includes card's name, cost, and two pointers (one of which will be NULL) : if action card, points toward the effect of the card (as enumeration), else if staff card, points towards a couple (effect, value), representing the effect of the card, as well as its "effectiveness"
 */
struct card {
    char* name;
    int cost;
    struct staff_effect* staff_effect;
    enum action_effect* action_effect;
};


/*---------------------------- Staff card -----------------------------------*/
struct staff_effect {
    enum staff_effect_id id;
    int value;
};

enum staff_effect_id {AE1, AE2, AA1, AA2, RE1, RE2, RA1, RA2, ADD, RDD, DR, E};


/*---------------------------- Action card ----------------------------------*/
enum action_effect {WinOneDD, DrawOneCard, PlayOneFISE, PlayOneFISA, Win6EP, RemoveOneFISEFISA, DiscardOneStaff, ShuffleDiscardDraw, IncreaseDevelopment, IncreaseDurability, RemoveAllFISEFISA};



#endif