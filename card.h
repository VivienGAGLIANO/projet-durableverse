#ifndef _CARD_H
#define _CARD_H


/*---------------------------- Staff card -----------------------------------*/
/*
 *@brief enumeration for staff card effects
 */
enum staff_effect_id {AE1, AE2, AA1, AA2, RE1, RE2, RA1, RA2, ASD, RSD, DR, E}; 

/*
 *@brief staff card struct : composed of the effect of the card, as well as its "effectiveness"
 */
struct staff_effect {
    enum staff_effect_id id;
    int value;
};



/*---------------------------- Action card ----------------------------------*/
/*
 *@brief enumeration for action card effects
 */
enum action_effect {WinOneSD, DrawOneCard, PlayOneFISE, PlayOneFISA, Win6EP, RemoveOneFISEFISA, DiscardOneStaff, ShuffleDiscardDraw, IncreaseDevelopment, IncreaseDurability, RemoveAllFISEFISA};



enum action_effect;

/*
 *@brief general card type definition, for action and staff cards. Includes card's name, cost, and two pointers (one of which will be NULL) poiting towards the effect of the card, being action or staff
 */
struct card {
    char* name;
    int cost;
    struct staff_effect* staff_effect;
    enum action_effect* action_effect;
};



#endif