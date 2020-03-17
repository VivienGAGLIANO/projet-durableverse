struct card {
    char* name;
    int cost;
    struct staff_effect* staff_effect;
    struct action_effect* action_effect;
}

enum staff_effect {
    int value;
    staff_effect_id id;
}

enum staff_effect_id {AE1, AE2, AA1, AA2, RE1, RE2, RA1, RA2, ADD, RDD, DR, E};


enum action_effect {Win1DD, PickOneCard, Play1FISE, Play1FISA, Win6EP, RemoveFISEFISA};