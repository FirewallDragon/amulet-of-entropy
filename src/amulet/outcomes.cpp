#include "outcomes.h"


/*
----------------------------------------------------------------------
    If you want to add your own modes, this is one place you need to
    add them. Search on one of these items to find the other places.

    This maps the list of possible outcomes, 1 through N (not skipping
    any values). Each outcome has a name (which currently is only
    printed to the log) and the JPEG image representing each outcome.

    The text strings and colors aren't currently used.

    Note that all Outcomes maps use 1-based numbering. It was a
    conscious design choice. See docs/Contrib.md for more info.
----------------------------------------------------------------------
*/

OutcomeMap coinFlipOutcomes = {
    {1, Outcome("Heads", "coin/1-heads.jpg")},
    {2, Outcome("Tails", "coin/2-tails.jpg")}
};

OutcomeMap d6Outcomes = {
    {1, Outcome("One", "d6/01_d6.jpg")},
    {2, Outcome("Two", "d6/02_d6.jpg")},
    {3, Outcome("Three", "d6/03_d6.jpg")},
    {4, Outcome("Four", "d6/04_d6.jpg")},
    {5, Outcome("Five", "d6/05_d6.jpg")},
    {6, Outcome("Six", "d6/06_d6.jpg")}
};

OutcomeMap eightBallOutcomes = {
    {1, Outcome("It is certain", "8ball/01-It-is-certain.jpg", 2, WHITE, PURPLE, PURPLE)},
    {2, Outcome("It is decidedly so", "8ball/02-It-is-decidely-so.jpg", 2, WHITE, PURPLE, PURPLE)},
    {3, Outcome("Without a doubt", "8ball/03-Without-a-doubt.jpg", 2, WHITE, PURPLE, PURPLE)},
    {4, Outcome("Yes definitely", "8ball/04-Yes-definitely.jpg", 2, WHITE, PURPLE, PURPLE)},
    {5, Outcome("You may reply on it", "8ball/05-You-may-reply-on-it.jpg", 2, WHITE, PURPLE, PURPLE)},
    {6, Outcome("As I see it yes", "8ball/06-As-I-see-it-yes.jpg", 2, WHITE, PURPLE, PURPLE)},
    {7, Outcome("Most likely", "8ball/07-Most-likely.jpg", 2, WHITE, PURPLE, PURPLE)},
    {8, Outcome("Outlook good", "8ball/08-Outlook-good.jpg", 2, WHITE, PURPLE, PURPLE)},
    {9, Outcome("Yes", "8ball/09-Yes.jpg", 2, WHITE, PURPLE, PURPLE)},
    {10, Outcome("Signs point to yes", "8ball/10-Signs-point-to-yes.jpg", 2, WHITE, PURPLE, PURPLE)},
    {11, Outcome("Reply hazy try again", "8ball/11-Reply-hazy-try-again.jpg", 2, WHITE, PURPLE, PURPLE)},
    {12, Outcome("Ask again later", "8ball/12-Ask-again-later.jpg", 2, WHITE, PURPLE, PURPLE)},
    {13, Outcome("Better not tell you now", "8ball/13-Better-not-tell-you-now.jpg", 2, WHITE, PURPLE, PURPLE)},
    {14, Outcome("Cannot predict now", "8ball/14-Cannot-predict-now.jpg", 2, WHITE, PURPLE, PURPLE)},
    {15, Outcome("Concentrate and ask again", "8ball/15-Concentrate-and-ask-again.jpg", 2, WHITE, PURPLE, PURPLE)},
    {16, Outcome("Don't count on it", "8ball/16-Dont-count-on-it.jpg", 2, WHITE, PURPLE, PURPLE)},
    {17, Outcome("My reply is no", "8ball/17-My-reply-is-no.jpg", 2, WHITE, PURPLE, PURPLE)},
    {18, Outcome("My sources say no", "8ball/18-My-sources-say-no.jpg", 2, WHITE, PURPLE, PURPLE)},
    {19, Outcome("Outlook not so good", "8ball/19-Outlook-not-so-good.jpg", 2, WHITE, PURPLE, PURPLE)},
    {20, Outcome("Very doubtful", "8ball/20-Very-doubtful.jpg", 2, WHITE, PURPLE, PURPLE)},
};

OutcomeMap pickCardOutcomes = {
    {1,  Outcome("Ace Hearts", "cards/01_ace-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {2,  Outcome("2 Hearts", "cards/02_2-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {3,  Outcome("3 Hearts", "cards/03_3-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {4,  Outcome("4 Hearts", "cards/04_4-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {5,  Outcome("5 Hearts", "cards/05_5-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {6,  Outcome("6 Hearts", "cards/06_6-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {7,  Outcome("7 Hearts", "cards/07_7-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {8,  Outcome("8 Hearts", "cards/08_8-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {9,  Outcome("9 Hearts", "cards/09_9-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {10, Outcome("10 Hearts", "cards/10_10-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {11, Outcome("Jack Hearts", "cards/11_jack-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {12, Outcome("Queen Hearts", "cards/12_queen-of-hearts.jpeg", 3, RED, WHITE, GREEN)},
    {13, Outcome("King Hearts", "cards/13_king-of-hearts.jpeg", 3, RED, WHITE, GREEN)},

    {14, Outcome("Ace Diamonds", "cards/14_ace-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {15, Outcome("2 Diamonds", "cards/15_2-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {16, Outcome("3 Diamonds", "cards/16_3-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {17, Outcome("4 Diamonds", "cards/17_4-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {18, Outcome("5 Diamonds", "cards/18_5-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {19, Outcome("6 Diamonds", "cards/19_6-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {20, Outcome("7 Diamonds", "cards/20_7-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {21, Outcome("8 Diamonds", "cards/21_8-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {22, Outcome("9 Diamonds", "cards/22_9-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {23, Outcome("10 Diamonds", "cards/23_10-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {24, Outcome("Jack Diamonds", "cards/24_jack-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {25, Outcome("Queen Diamonds", "cards/25_queen-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},
    {26, Outcome("King Diamonds", "cards/26_king-of-diamonds.jpeg", 3, RED, WHITE, GREEN)},

    {27, Outcome("Ace Spades", "cards/27_ace-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {28, Outcome("2 Spades", "cards/28_2-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {29, Outcome("3 Spades", "cards/29_3-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {30, Outcome("4 Spades", "cards/30_4-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {31, Outcome("5 Spades", "cards/31_5-of-spadess.jpeg", 3, BLACK, WHITE, GREEN)},
    {32, Outcome("6 Spades", "cards/32_6-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {33, Outcome("7 Spades", "cards/33_7-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {34, Outcome("8 Spades", "cards/34_8-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {35, Outcome("9 Spades", "cards/35_9-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {36, Outcome("10 Spades", "cards/36_10-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {37, Outcome("Jack Spades", "cards/37_jack-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {38, Outcome("Queen Spades", "cards/38_queen-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},
    {39, Outcome("King Spades", "cards/39_king-of-spades.jpeg", 3, BLACK, WHITE, GREEN)},

    {40, Outcome("Ace Clubs", "cards/40_ace-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {41, Outcome("2 Clubs", "cards/41_2-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {42, Outcome("3 Clubs", "cards/42_3-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {43, Outcome("4 Clubs", "cards/43_4-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {44, Outcome("5 Clubs", "cards/44_5-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {45, Outcome("6 Clubs", "cards/45_6-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {46, Outcome("7 Clubs", "cards/46_7-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {47, Outcome("8 Clubs", "cards/47_8-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {48, Outcome("9 Clubs", "cards/48_9-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {49, Outcome("10 Clubs", "cards/49_10-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {50, Outcome("Jack Clubs", "cards/50_jack-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {51, Outcome("Queen Clubs", "cards/51_queen-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)},
    {52, Outcome("King Clubs", "cards/52_king-of-clubs.jpeg", 3, BLACK, WHITE, GREEN)}
};

OutcomeMap tarotOutcomes = {
    {1, Outcome("TheFool", "tarot/01_TheFool.jpg", 3, BLACK, WHITE, WHITE)},
    {2, Outcome("TheMagician", "tarot/02_TheMagician.jpg", 3, BLACK, WHITE, WHITE)},
    {3, Outcome("TheHighPriestess", "tarot/03_TheHighPriestess.jpg", 3, BLACK, WHITE, WHITE)},
    {4, Outcome("TheEmpress", "tarot/04_TheEmpress.jpg", 3, BLACK, WHITE, WHITE)},
    {5, Outcome("TheEmperor", "tarot/05_TheEmperor.jpg", 3, BLACK, WHITE, WHITE)},
    {6, Outcome("TheHierophant", "tarot/06_TheHierophant.jpg", 3, BLACK, WHITE, WHITE)},
    {7, Outcome("TheLovers", "tarot/07_TheLovers.jpg", 3, BLACK, WHITE, WHITE)},
    {8, Outcome("TheChariot", "tarot/08_TheChariot.jpg", 3, BLACK, WHITE, WHITE)},
    {9, Outcome("Strength", "tarot/09_Strength.jpg", 3, BLACK, WHITE, WHITE)},
    {10, Outcome("TheHermit", "tarot/10_TheHermit.jpg", 3, BLACK, WHITE, WHITE)},
    {11, Outcome("WheelOfFortune", "tarot/11_WheelOfFortune.jpg", 3, BLACK, WHITE, WHITE)},
    {12, Outcome("Justice", "tarot/12_Justice.jpg", 3, BLACK, WHITE, WHITE)},
    {13, Outcome("TheHangedMan", "tarot/13_TheHangedMan.jpg", 3, BLACK, WHITE, WHITE)},
    {14, Outcome("Death", "tarot/14_Death.jpg", 3, BLACK, WHITE, WHITE)},
    {15, Outcome("Temperance", "tarot/15_Temperance.jpg", 3, BLACK, WHITE, WHITE)},
    {16, Outcome("TheDevil", "tarot/16_TheDevil.jpg", 3, BLACK, WHITE, WHITE)},
    {17, Outcome("TheTower", "tarot/17_TheTower.jpg", 3, BLACK, WHITE, WHITE)},
    {18, Outcome("TheStar", "tarot/18_TheStar.jpg", 3, BLACK, WHITE, WHITE)},
    {19, Outcome("TheMoon", "tarot/19_TheMoon.jpg", 3, BLACK, WHITE, WHITE)},
    {20, Outcome("TheSun", "tarot/20_TheSun.jpg", 3, BLACK, WHITE, WHITE)},
    {21, Outcome("Judgement", "tarot/21_Judgement.jpg", 3, BLACK, WHITE, WHITE)},
    {22, Outcome("TheWorld", "tarot/22_TheWorld.jpg", 3, BLACK, WHITE, WHITE)},

    {23, Outcome("Cups01", "tarot/23_Cups01.jpg", 3, BLACK, WHITE, WHITE)},
    {24, Outcome("Cups02", "tarot/24_Cups02.jpg", 3, BLACK, WHITE, WHITE)},
    {25, Outcome("Cups03", "tarot/25_Cups03.jpg", 3, BLACK, WHITE, WHITE)},
    {26, Outcome("Cups04", "tarot/26_Cups04.jpg", 3, BLACK, WHITE, WHITE)},
    {27, Outcome("Cups05", "tarot/27_Cups05.jpg", 3, BLACK, WHITE, WHITE)},
    {28, Outcome("Cups06", "tarot/28_Cups06.jpg", 3, BLACK, WHITE, WHITE)},
    {29, Outcome("Cups07", "tarot/29_Cups07.jpg", 3, BLACK, WHITE, WHITE)},
    {30, Outcome("Cups08", "tarot/30_Cups08.jpg", 3, BLACK, WHITE, WHITE)},
    {31, Outcome("Cups09", "tarot/31_Cups09.jpg", 3, BLACK, WHITE, WHITE)},
    {32, Outcome("Cups10", "tarot/32_Cups10.jpg", 3, BLACK, WHITE, WHITE)},
    {33, Outcome("Cups11", "tarot/33_Cups11.jpg", 3, BLACK, WHITE, WHITE)},
    {34, Outcome("Cups12", "tarot/34_Cups12.jpg", 3, BLACK, WHITE, WHITE)},
    {35, Outcome("Cups13", "tarot/35_Cups13.jpg", 3, BLACK, WHITE, WHITE)},
    {36, Outcome("Cups14", "tarot/36_Cups14.jpg", 3, BLACK, WHITE, WHITE)},

    {37, Outcome("Pentacles01", "tarot/37_Pentacles01.jpg", 3, BLACK, WHITE, WHITE)},
    {38, Outcome("Pentacles02", "tarot/38_Pentacles02.jpg", 3, BLACK, WHITE, WHITE)},
    {39, Outcome("Pentacles03", "tarot/39_Pentacles03.jpg", 3, BLACK, WHITE, WHITE)},
    {40, Outcome("Pentacles04", "tarot/40_Pentacles04.jpg", 3, BLACK, WHITE, WHITE)},
    {41, Outcome("Pentacles05", "tarot/41_Pentacles05.jpg", 3, BLACK, WHITE, WHITE)},
    {42, Outcome("Pentacles06", "tarot/42_Pentacles06.jpg", 3, BLACK, WHITE, WHITE)},
    {43, Outcome("Pentacles07", "tarot/43_Pentacles07.jpg", 3, BLACK, WHITE, WHITE)},
    {44, Outcome("Pentacles08", "tarot/44_Pentacles08.jpg", 3, BLACK, WHITE, WHITE)},
    {45, Outcome("Pentacles09", "tarot/45_Pentacles09.jpg", 3, BLACK, WHITE, WHITE)},
    {46, Outcome("Pentacles10", "tarot/46_Pentacles10.jpg", 3, BLACK, WHITE, WHITE)},
    {47, Outcome("Pentacles11", "tarot/47_Pentacles11.jpg", 3, BLACK, WHITE, WHITE)},
    {48, Outcome("Pentacles12", "tarot/48_Pentacles12.jpg", 3, BLACK, WHITE, WHITE)},
    {49, Outcome("Pentacles13", "tarot/49_Pentacles13.jpg", 3, BLACK, WHITE, WHITE)},
    {50, Outcome("Pentacles14", "tarot/50_Pentacles14.jpg", 3, BLACK, WHITE, WHITE)},

    {51, Outcome("Swords01", "tarot/51_Swords01.jpg", 3, BLACK, WHITE, WHITE)},
    {52, Outcome("Swords02", "tarot/52_Swords02.jpg", 3, BLACK, WHITE, WHITE)},
    {53, Outcome("Swords03", "tarot/53_Swords03.jpg", 3, BLACK, WHITE, WHITE)},
    {54, Outcome("Swords04", "tarot/54_Swords04.jpg", 3, BLACK, WHITE, WHITE)},
    {55, Outcome("Swords05", "tarot/55_Swords05.jpg", 3, BLACK, WHITE, WHITE)},
    {56, Outcome("Swords06", "tarot/56_Swords06.jpg", 3, BLACK, WHITE, WHITE)},
    {57, Outcome("Swords07", "tarot/57_Swords07.jpg", 3, BLACK, WHITE, WHITE)},
    {58, Outcome("Swords08", "tarot/58_Swords08.jpg", 3, BLACK, WHITE, WHITE)},
    {59, Outcome("Swords09", "tarot/59_Swords09.jpg", 3, BLACK, WHITE, WHITE)},
    {60, Outcome("Swords10", "tarot/60_Swords10.jpg", 3, BLACK, WHITE, WHITE)},
    {61, Outcome("Swords11", "tarot/61_Swords11.jpg", 3, BLACK, WHITE, WHITE)},
    {62, Outcome("Swords12", "tarot/62_Swords12.jpg", 3, BLACK, WHITE, WHITE)},
    {63, Outcome("Swords13", "tarot/63_Swords13.jpg", 3, BLACK, WHITE, WHITE)},
    {64, Outcome("Swords14", "tarot/64_Swords14.jpg", 3, BLACK, WHITE, WHITE)},

    {65, Outcome("Wands01", "tarot/65_Wands01.jpg", 3, BLACK, WHITE, WHITE)},
    {66, Outcome("Wands02", "tarot/66_Wands02.jpg", 3, BLACK, WHITE, WHITE)},
    {67, Outcome("Wands03", "tarot/67_Wands03.jpg", 3, BLACK, WHITE, WHITE)},
    {68, Outcome("Wands04", "tarot/68_Wands04.jpg", 3, BLACK, WHITE, WHITE)},
    {69, Outcome("Wands05", "tarot/69_Wands05.jpg", 3, BLACK, WHITE, WHITE)},
    {70, Outcome("Wands06", "tarot/70_Wands06.jpg", 3, BLACK, WHITE, WHITE)},
    {71, Outcome("Wands07", "tarot/71_Wands07.jpg", 3, BLACK, WHITE, WHITE)},
    {72, Outcome("Wands08", "tarot/72_Wands08.jpg", 3, BLACK, WHITE, WHITE)},
    {73, Outcome("Wands09", "tarot/73_Wands09.jpg", 3, BLACK, WHITE, WHITE)},
    {74, Outcome("Wands10", "tarot/74_Wands10.jpg", 3, BLACK, WHITE, WHITE)},
    {75, Outcome("Wands11", "tarot/75_Wands11.jpg", 3, BLACK, WHITE, WHITE)},
    {76, Outcome("Wands12", "tarot/76_Wands12.jpg", 3, BLACK, WHITE, WHITE)},
    {77, Outcome("Wands13", "tarot/77_Wands13.jpg", 3, BLACK, WHITE, WHITE)},
    {78, Outcome("Wands14", "tarot/78_Wands14.jpg", 3, BLACK, WHITE, WHITE)},
};